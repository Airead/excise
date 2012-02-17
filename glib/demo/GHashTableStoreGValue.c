#include <glib.h>
#include <glib-object.h>

gint cb_compare_str(gconstpointer a, gconstpointer b);
int hashtable_show_keys(GHashTable *table);
gint type_print(gpointer gtype);
gint hashtable_show_value_type(GHashTable *table);
int g_value_print(GValue *val);
gint g_list_free_all_node(GList *list, void (*free_func)(gpointer));

 gint cb_compare_str(gconstpointer a, gconstpointer b)
{
    return g_strcmp0((gchar *)a, (gchar *)b);
}

/*
 * void (*GFunc) (gpointer data, gpointer user_data);
 */
static void array_foreach_cb(gpointer data, gpointer user_data)
{
    gchar *str = (gchar *)data;

    g_print("  %s\n", str);
    
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


gint g_list_free_all_node(GList *list, void (*free_func)(gpointer))
{
    while (list != NULL) {
        free_func(list->data);
        list = g_list_next(list);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    GHashTable *table;
    GValue gval = G_VALUE_INIT;
    gchar *mode, *ssid;

    g_type_init();

    table = g_hash_table_new(NULL, NULL);
    g_value_init(&gval, G_TYPE_STRING);

    g_value_set_string(&gval, "wifi");
    g_print("%s\n", g_value_get_string(&gval));
    g_hash_table_insert(table, "type", &gval);
    g_value_reset(&gval);

    mode = "managed";
    ssid = "ijimu";
        
    g_value_set_string(&gval, mode);
    g_hash_table_insert(table, "Mode", &gval);
    g_value_reset(&gval);
    
    g_value_set_string(&gval, ssid);
    g_hash_table_insert(table, "SSID", &gval);
    g_value_reset(&gval);


    hashtable_show_value_type(table);

    return 0;
}
