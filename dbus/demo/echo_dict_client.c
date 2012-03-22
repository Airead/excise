/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>
 * @date    2012  2月 16 16:46:37 CST
 ********************************************************/

#include <dbus/dbus-glib.h>
#include "common_marshaler.h"

#define DBUS_TYPE_G_STRING_VALUE_HASHTABLE \
    (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE))

#define DBUS_TYPE_G_STRING_STRING_HASHTABLE \
    (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_STRING))

int g_value_print(GValue *val);

gint cb_compare_str(gconstpointer a, gconstpointer b)
{
    return g_strcmp0((gchar *)a, (gchar *)b);
}

gint hashtable_show_keys(GHashTable *table)
{
    GList *list;
    const gchar *type;
    gchar *key;
    gchar *orig_key;
    GValue *val;
    GHashTable *dict;

    list = NULL;

    list = g_hash_table_get_keys(table);
    list = g_list_sort(list, cb_compare_str);

    g_print("*******************************************************\n");
    g_print("%-30s%-20s\n", "key", "value type");
    while (list != NULL) {
        key = list->data;
        if (g_hash_table_lookup_extended(table, key, 
                                         (gpointer *)&orig_key, 
                                         (gpointer *)&val)) {
            g_print("%-30s", key);
            type = G_VALUE_TYPE_NAME(val);
            g_print("%s\n", type);
            if (!g_strcmp0(type, "GHashTable_gchararray+GValue_")) {
                dict = g_value_get_boxed(val);
                hashtable_show_keys(dict);
            }
        } else {
            g_print("%-30s NOT found\n", key);
        }
        
        list = g_list_next(list);
    }
    g_print("*******************************************************\n\n");

    return 0;
}

gint hashtable_show_value_type(GHashTable *table)
{
    GList *list;
    gchar *key;
    gchar *orig_key;
    GValue *val;

    list = NULL;

    list = g_hash_table_get_keys(table);
    list = g_list_sort(list, cb_compare_str);

    g_print("*******************************************************\n");
    g_print("%-30s%-20s\n", "key", "value type");
    while (list != NULL) {
        key = list->data;
        if (g_hash_table_lookup_extended(table, key, 
                                         (gpointer *)&orig_key, 
                                         (gpointer *)&val)) {
            g_print("%-30s", key);
            g_print("%s\n", G_VALUE_TYPE_NAME(val));
            g_value_print(val);
        } else {
            g_print("%-30s NOT found\n", key);
        }
        
        list = g_list_next(list);
    }
    g_print("*******************************************************\n\n");
    return 0;
}

/*
 * void (*GFunc) (gpointer data, gpointer user_data);
 */
static void array_foreach_cb(gpointer data, gpointer user_data)
{
    gchar *str = (gchar *)data;

    g_print("  %s\n", str);
    
}

int g_value_print(GValue *val)
{
    const gchar *type;
    gchar **gstrv;
    gboolean boolean;
    GPtrArray *gptr_array;
    guchar uch;
    GHashTable *table;

    type = G_VALUE_TYPE_NAME(val);

    if (!g_strcmp0(type, "DBusGObjectPath")) {
        g_print("  %s\n", (gchar *)g_value_get_boxed(val));

    } else if (!g_strcmp0(type, "GStrv")) {
        gstrv = (gchar **)g_value_get_boxed(val);
        while (gstrv != NULL && *gstrv != NULL) {
            g_print("  %s\n", *gstrv);
            gstrv++;
        }

    } else if(!g_strcmp0(type, "gchararray")) {
        g_print("  %s\n", (gchar *)g_value_get_string(val));
        
    } else if(!g_strcmp0(type, "gboolean")) {
        boolean = g_value_get_boolean(val);
        if (boolean) {
            g_print("  true\n");
        } else {
            g_print("  false\n");
        }

    } else if (!g_strcmp0(type, "GPtrArray_DBusGObjectPath_")) {
        gptr_array = g_value_get_boxed(val);
        g_ptr_array_foreach(gptr_array, array_foreach_cb, NULL);

    } else if (!g_strcmp0(type, "guchar")) {
        uch = g_value_get_uchar(val);
        g_print("  %d\n", uch);

    } else if (!g_strcmp0(type, "GHashTable_gchararray+GValue_")) {
        table = g_value_get_boxed(val);
        hashtable_show_value_type(table);

    }else {
        g_printerr("==============================unknown\n");
    }
    
    g_print("  null\n");

    return 0;
}

int send_dict_string_value(DBusGProxy *proxy)
{
    GError *error;

    GHashTable *table;
    GValue gval_type = G_VALUE_INIT;
    GValue gval_mode = G_VALUE_INIT;
    GValue gval_ssid = G_VALUE_INIT;

    gchar *cmd;

    table = g_hash_table_new(NULL, NULL);

    g_value_init(&gval_type, G_TYPE_STRING);
    g_value_set_string(&gval_type, g_strdup("wifi"));
    g_hash_table_insert(table, g_strdup("type"), &gval_type);

    g_value_init(&gval_mode, G_TYPE_STRING);
    g_value_set_string(&gval_mode, g_strdup("managed"));
    g_hash_table_insert(table, g_strdup("Mode"), &gval_mode);
    
    g_value_init(&gval_ssid, G_TYPE_STRING);
    g_value_set_string(&gval_ssid, g_strdup("ijimu"));
    g_hash_table_insert(table, g_strdup("SSID"), &gval_ssid);

    hashtable_show_value_type(table);

    cmd = "DictPrint";
    if (!dbus_g_proxy_call(proxy, cmd, &error,
                           DBUS_TYPE_G_STRING_VALUE_HASHTABLE, table,
                           G_TYPE_INVALID,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", cmd, error->message);
        g_error_free(error);
        return -1;
    }
    
    return 0;
}

int send_dict_string_string(DBusGProxy *proxy)
{
    GError *error;

    GHashTable *table;
    gchar *cmd;

    table = g_hash_table_new(NULL, NULL);

    g_hash_table_insert(table, g_strdup("type"), "wifi");

    g_hash_table_insert(table, g_strdup("Mode"), "managed");
    
    g_hash_table_insert(table, g_strdup("SSID"), "ijimu");

//    hashtable_show_value_type(table);

    cmd = "DictPrintStr";
    if (!dbus_g_proxy_call(proxy, cmd, &error,
                           DBUS_TYPE_G_STRING_STRING_HASHTABLE, table,
                           G_TYPE_INVALID,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", cmd, error->message);
        g_error_free(error);
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    DBusGConnection *connection;
    GError *error = NULL;
    DBusGProxy *proxy;

    g_type_init();


    /* conect system connection and get proxy */
    connection = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
    if (connection == NULL) {
        g_printerr("get system bus failed: %s\n", error->message);
        g_error_free(error);
        return -1;
    }
    
    proxy = dbus_g_proxy_new_for_name(connection, 
                                      "dict.sample",
                                      "/DictEcho",
                                      "dict.Sample");

    send_dict_string_value(proxy);

    send_dict_string_string(proxy);

    return 0;
}
