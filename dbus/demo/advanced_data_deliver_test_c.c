/**
 * @file advanced_data_deliver_test_c.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/03/23 11:28:29
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus-glib.h>

#define METHOD_STRLEN 128

int send_recv_dict(DBusGProxy *proxy)
{
    char *method;
    GHashTable *table, *ret;
    GHashTableIter iter;
    gpointer key, value;
    GError *error = NULL;
    char *str[3];

    table = g_hash_table_new(NULL, NULL);

    str[0] = "apple";
    str[1] = "banana";
    str[2] = "cherry";

    g_hash_table_insert(table, "a", str[0]);
    g_hash_table_insert(table, "b", str[1]);
    g_hash_table_insert(table, "c", str[2]);

    method = "DictPrint";
    if (!dbus_g_proxy_call(proxy, method, &error,
                           DBUS_TYPE_G_STRING_STRING_HASHTABLE, table,
                           G_TYPE_INVALID,
                           DBUS_TYPE_G_STRING_STRING_HASHTABLE, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }

    g_print("receive: dictionary\n");
    g_hash_table_iter_init(&iter, ret);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_print("key: %s, %s\n", (char *)key, (char *)value);
    }
    g_print("=================================\n\n");

    g_hash_table_unref(table);
    g_hash_table_unref(ret);

    return 0;
}

int send_recv_int_array(DBusGProxy *proxy)
{
    char *method;
    GError *error;
    GArray *garray, *ret;
    gint i, j;
    
    garray = g_array_new (FALSE, FALSE, sizeof (gint));
    for (i = 0; i < 6; i++) {
        j = i + 1;
        g_array_append_val(garray, j);
    }

    method = "IntArrayPrint";
    if (!dbus_g_proxy_call(proxy, method, &error,
                           DBUS_TYPE_G_INT_ARRAY, garray,
                           G_TYPE_INVALID,
                           DBUS_TYPE_G_INT_ARRAY, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }

    g_print("receive int array:\n");
    for (i = 0; i < ret->len; i++) {
        g_print("%d ", g_array_index(ret, gint, i));
    }
    g_print("\n=================================\n\n");
    
    return 0;
}

#define DBUS_STRUCT_STRING_INT_DOUBLE_BOOLEAN (                         \
        dbus_g_type_get_struct ( "GValueArray", G_TYPE_STRING, G_TYPE_INT, \
                                 G_TYPE_DOUBLE, G_TYPE_BOOLEAN, G_TYPE_INVALID))

int send_recv_struct(DBusGProxy *proxy)
{
    char *method;
    GError *error = NULL;
    GValueArray *ret, *send_array;
    GValue *gval;
    GValue send_gval[4] = {{0}};
    int i;
    
    g_value_init (&send_gval[0], G_TYPE_STRING);
    g_value_set_string(&send_gval[0], "fan");
    g_value_init (&send_gval[1], G_TYPE_INT);
    g_value_set_int(&send_gval[1], 24);
    g_value_init (&send_gval[2], G_TYPE_DOUBLE);
    g_value_set_double(&send_gval[2], 70.2);
    g_value_init (&send_gval[3], G_TYPE_BOOLEAN);
    g_value_set_boolean(&send_gval[3], FALSE);
    
    send_array = g_value_array_new(0);
    for (i = 0; i < 4; i++) {
        send_array = g_value_array_append(send_array, &send_gval[i]);
    }

    method = "StructPrint";
    if (!dbus_g_proxy_call(proxy, method, &error,
                           DBUS_STRUCT_STRING_INT_DOUBLE_BOOLEAN, send_array,
                           G_TYPE_INVALID,
                           DBUS_STRUCT_STRING_INT_DOUBLE_BOOLEAN, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }

    g_print("receive struct:\n");
    for (i = 0; i < ret->n_values; i++) {
        gval = g_value_array_get_nth(ret, i);
        if (G_VALUE_TYPE(gval) == G_TYPE_STRING) {
            g_print("%s\n", g_value_get_string(gval));
        } else if (G_VALUE_TYPE(gval) == G_TYPE_DOUBLE) {
            g_print("%f\n", g_value_get_double(gval));
        } else if (G_VALUE_TYPE(gval) == G_TYPE_INT) {
            g_print("%d\n", g_value_get_int(gval));
        } else if (G_VALUE_TYPE(gval) == G_TYPE_BOOLEAN) {
            g_print("%d\n", g_value_get_boolean(gval));
        }
    }

    g_print("\n=================================\n\n");
    
    return 0;
}

int send_recv_variant_int_array(DBusGProxy *proxy, char *method)
{
    GError *error = NULL;
    GValue gval = G_VALUE_INIT;
    GValue ret = G_VALUE_INIT;
    GHashTable *table;
    GHashTableIter iter;
    gpointer key, value;
    GArray *garray;
    gint i, j;
    
    g_value_init(&gval, DBUS_TYPE_G_INT_ARRAY);
    g_value_take_boxed(&gval, dbus_g_type_specialized_construct(DBUS_TYPE_G_INT_ARRAY));
    garray = g_value_get_boxed(&gval);
    for (i = 0; i < 6; i++) {
        j = i + 1;
        g_array_append_val(garray, j);
    }

    if (!dbus_g_proxy_call(proxy, method, &error,
                           G_TYPE_VALUE, &gval,
                           G_TYPE_INVALID,
                           G_TYPE_VALUE, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }

    g_print("receive variant:\n");
    table = g_value_get_boxed(&ret);
    
    g_hash_table_iter_init(&iter, table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_print("key: %s, %s\n", (char *)key, (char *)value);
    }
   
    g_print("\n=================================\n\n");

    return 0;
}

int send_recv_variant_struct(DBusGProxy *proxy, char *method)
{
    GError *error = NULL;
    GValue gval = G_VALUE_INIT;
    GValue ret = G_VALUE_INIT;
    GHashTable *table;
    GHashTableIter iter;
    gpointer key, value;
    
    g_value_init(&gval, DBUS_STRUCT_STRING_INT_DOUBLE_BOOLEAN);
    g_value_take_boxed(&gval, dbus_g_type_specialized_construct(DBUS_STRUCT_STRING_INT_DOUBLE_BOOLEAN));
    
    dbus_g_type_struct_set(&gval, 0, "fan",
                           1, 24,
                           2, 70.1,
                           3, FALSE, G_MAXUINT);

    if (!dbus_g_proxy_call(proxy, method, &error,
                           G_TYPE_VALUE, &gval,
                           G_TYPE_INVALID,
                           G_TYPE_VALUE, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }

    g_print("receive variant:\n");
    table = g_value_get_boxed(&ret);
    
    g_hash_table_iter_init(&iter, table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_print("key: %s, %s\n", (char *)key, (char *)value);
    }
   
    g_print("\n=================================\n\n");

    return 0;
}

int send_recv_variant(DBusGProxy *proxy)
{
    char *method;
  
    method = "VariantPrint";
    
    send_recv_variant_int_array(proxy, method);
    send_recv_variant_struct(proxy, method);

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
                                      "airead.fan.AdvancedDataType",
                                      "/airead/fan/AdvancedDataType",
                                      "airead.fan.AdvancedDataType");
    
    send_recv_dict(proxy);
    send_recv_int_array(proxy);
    send_recv_struct(proxy);
    send_recv_variant(proxy);

    return 0;
}
