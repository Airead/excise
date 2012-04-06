/**
 * @file more_advanced_data_deliver_test_c.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/03/23 17:55:41
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus-glib.h>

#define METHOD_STRLEN 128

/*
 * a{sv} 
 * dic = {}
 * dic['fanrenhao'] = {'name':'renhao', 'age':'24', 'gender': 'male'}
 * dic['liwenfeng'] = {'name':'wenfeng', 'age':'22', 'gender': 'female'} 
 */

#define DBUS_TYPE_G_STRING_VALUE_HASHTABLE                             \
    dbus_g_type_get_map ( "GHashTable", G_TYPE_STRING, G_TYPE_VALUE)

int send_recv_dictdict(DBusGProxy *proxy)
{
    int i;
    char *method;
    GHashTable *table, *ret, *subtable;
    GHashTableIter iter, subiter;
    gpointer key, value, subkey, subvalue;
    GError *error = NULL;
    GValue gval[2] = {{0}};
    gchar *table_value[2][3] = {{"renhao", "24", "male"},
                                {"wenfeng", "22", "female"}};

    table = g_hash_table_new(NULL, NULL);

    for (i = 0; i < 2; i++) {
        g_value_init(&gval[i], DBUS_TYPE_G_STRING_STRING_HASHTABLE);
        g_value_take_boxed(&gval[i], 
                           dbus_g_type_specialized_construct(
                               DBUS_TYPE_G_STRING_STRING_HASHTABLE));
        subtable = g_value_get_boxed(&gval[i]);
        g_hash_table_insert(subtable, "name", table_value[i][0]);
        g_hash_table_insert(subtable, "age", table_value[i][1]);
        g_hash_table_insert(subtable, "gender", table_value[i][2]);
    }

    g_hash_table_insert(table, "fanrenhao", &gval[0]);
    g_hash_table_insert(table, "liwenfeng", &gval[1]);

    method = "DictDictPrint";
    if (!dbus_g_proxy_call(proxy, method, &error,
                           DBUS_TYPE_G_STRING_VALUE_HASHTABLE, table,
                           G_TYPE_INVALID,
                           DBUS_TYPE_G_STRING_VALUE_HASHTABLE, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }

    g_print("receive: dictionary\n");
    g_hash_table_iter_init(&iter, ret);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
            g_print("%s:\n", (char *)key);
            subtable = g_value_get_boxed(value);
            g_hash_table_iter_init(&subiter, subtable);
            while (g_hash_table_iter_next(&subiter, &subkey, &subvalue)) {
                g_print("%s, %s\n", (char *)subkey, (char *)subvalue);
            }
            g_print("---------------------------------\n");
        }
    g_print("=================================\n\n");

    return 0;
}

/*
 * a(si)
 * astruct = [('apple', 1), ('banana', 2), ('cherry', 5)]
 */

#define DBUS_STRUCT_STRING_INT (                         \
        dbus_g_type_get_struct ( "GValueArray", G_TYPE_STRING,  \
                                 G_TYPE_INT, G_TYPE_INVALID))
#define DBUS_ARRAY_STRUCT_STRING_INT ( \
        dbus_g_type_get_collection("GPtrArray", DBUS_STRUCT_STRING_INT) )

int send_recv_struct_array(DBusGProxy *proxy)
{
    gchar *method;
    GError *error = NULL;
    GPtrArray *gparray, *ret;
    GValueArray *garray[3], *tmp_garray;
    GValue gval[3][2] = {{{0}}};
    GValue *tmp_gval;
    gchar *str[3] = {"apple", "banana", "cherry"};
    gint num[3] = {1, 2, 5};
    int i, j;

    for (i = 0; i < 3; i++) {
        g_value_init (&gval[i][0], G_TYPE_STRING);
        g_value_set_string(&gval[i][0], str[i]);
        g_value_init (&gval[i][1], G_TYPE_INT);
        g_value_set_int(&gval[i][1], num[i]);
    }
    
    gparray = g_ptr_array_new();
    for (i = 0; i < 3; i++) {
        garray[i] = g_value_array_new(0);
        for (j = 0; j < 2 ; j++) {
            g_value_array_append(garray[i], &gval[i][j]);
        }
        g_ptr_array_add(gparray, garray[i]);
    }

    method = "StructArrayPrint";
    if (!dbus_g_proxy_call(proxy, method, &error,
                           DBUS_ARRAY_STRUCT_STRING_INT, gparray,
                           G_TYPE_INVALID,
                           DBUS_ARRAY_STRUCT_STRING_INT, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }

    for (i = 0; i < ret->len; i++) {
        tmp_garray = g_ptr_array_index(ret, i);
        tmp_gval = g_value_array_get_nth(tmp_garray, 0);
        g_print("%s: ", g_value_get_string(tmp_gval));
        tmp_gval = g_value_array_get_nth(tmp_garray, 1);
        g_print("%d\n", g_value_get_int(tmp_gval));
    }
    g_print("=================================\n\n");

    return 0;
}

int send_recv_objectpath_dict_struct_array(DBusGProxy *proxy)
{

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
    
    /* get proxy */
    proxy = dbus_g_proxy_new_for_name(connection, 
                                      "airead.fan.MoreAdvancedDataType",
                                      "/airead/fan/MoreAdvancedDataType",
                                      "airead.fan.MoreAdvancedDataType");
    
    send_recv_dictdict(proxy);
    send_recv_struct_array(proxy);
    send_recv_objectpath_dict_struct_array(proxy);

    return 0;
}
