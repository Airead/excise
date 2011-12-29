/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>
 * @date    2011 12月 20 16:07:05 CST
 ********************************************************/

#include <dbus/dbus-glib.h>
#include "manager.h"
#include "common.h"

gint cb_compare_str(gconstpointer a, gconstpointer b)
{
    return g_strcmp0((gchar *)a, (gchar *)b);
}

gint hashtable_show_keys(GHashTable *table)
{
    GList *list;
    gchar *key;
    
    list = NULL;

    list = g_hash_table_get_keys(table);
    list = g_list_sort(list, cb_compare_str);

    while (list != NULL) {
        key = list->data;
        g_print("key: %s\n", key);
        list = g_list_next(list);
    }

    return 0;
}

gint hashtable_show_value_type(GHashTable *table)
{
    GList *list;
    gchar *key;
    GValue *val;

    list = NULL;

    list = g_hash_table_get_keys(table);
    list = g_list_sort(list, cb_compare_str);

    g_print("%-30s%-20s\n", "key", "value type");
    while (list != NULL) {
        key = list->data;
        val = g_hash_table_lookup(table, key);
        g_print("%-30s", key);
        type_print((gpointer)val);
        g_print("\n");
        list = g_list_next(list);
    }

    return 0;
}

gint type_print(gpointer gtype)
{
    gint num;

    switch (num = G_VALUE_TYPE(gtype)) {
    case G_TYPE_INVALID:
        g_print("INVALID: %d", num);
        break;
    case G_TYPE_NONE:
        g_print("NONE: %d", num);
        break;
    case G_TYPE_INTERFACE:
        g_print("INTERFACE: %d", num);
        break;
    case G_TYPE_CHAR:
        g_print("CHAR: %d", num);
        break;
    case G_TYPE_UCHAR:
        g_print("UCHAR: %d", num);
        break;
    case G_TYPE_BOOLEAN:
        g_print("BOOLEAN: %d", num);
        break;
    case G_TYPE_INT:
        g_print("INT: %d", num);
        break;
    case G_TYPE_UINT:
        g_print("UINT: %d", num);
        break;
    case G_TYPE_LONG:
        g_print("LONG: %d", num);
        break;
    case G_TYPE_ULONG:
        g_print("ULONG: %d", num);
        break;
    case G_TYPE_INT64:
        g_print("INT: %d", num);
        break;
    case G_TYPE_UINT64:
        g_print("UINT: %d", num);
        break;
    case G_TYPE_ENUM:
        g_print("ENUM: %d", num);
        break;
    case G_TYPE_FLAGS:
        g_print("FLAGS: %d", num);
        break;
    case G_TYPE_FLOAT:
        g_print("FLOAT: %d", num);
        break;
    case G_TYPE_DOUBLE:
        g_print("DOUBLE: %d", num);
        break;
    case G_TYPE_STRING:
        g_print("STRING: %d", num);
        break;
    case G_TYPE_POINTER:
        g_print("POINTER: %d", num);
        break;
    case G_TYPE_BOXED:
        g_print("BOXED: %d", num);
        break;
    case G_TYPE_PARAM:
        g_print("PARAM: %d", num);
        break;
    case G_TYPE_OBJECT:
        g_print("OBJECT: %d", num);
        break;
    case  G_TYPE_VARIANT:
        g_print("VARIANT: %d", num);
        break;
/*    case DBUS_TYPE_G_STRING_ARRAY:
        g_print("STRING_ARRAY");
        break;*/
    default:
        g_print("UNKNOWN: %d", num);
        break;
    }

    return 0;
}
