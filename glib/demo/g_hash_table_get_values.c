/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>
 * @date    2011 12月 19 16:14:29 CST
 ********************************************************/

#if 0
hash_table :
a GHashTable

Returns :
a GList containing all the keys inside the hash table. The content of the list is owned by the hash table and should not be modified or freed. Use g_list_free() when done using the list.
#endif

#include <glib.h>

int main(int argc, char *argv[])
{
    GHashTable *table;
    int num, num2, num3;
    GList *value_list = NULL;

    table = g_hash_table_new(NULL, NULL);
    g_print("table size: %u\n", g_hash_table_size(table));

    num = 1;
    g_hash_table_insert(table, "one", &num);
    g_print("table size: %u\n", g_hash_table_size(table));
    
    /* key not exist */
    num2 = 2;
    g_hash_table_replace(table, "two", &num2);
    g_print("table size: %u\n", g_hash_table_size(table));

    /* key exist */
    num = 3;
    g_hash_table_replace(table, "one", &num);
    g_print("table size: %u\n", g_hash_table_size(table));
    
    num3 = 4;
    g_hash_table_insert(table, "three", &num3);
    g_print("table size: %u\n", g_hash_table_size(table));

    value_list = g_hash_table_get_values(table);

    while (value_list != NULL) {
        g_print("%d\n", *(gint *)value_list->data);
        value_list = g_list_next(value_list);
    }

    g_list_free(value_list);
    g_hash_table_destroy(table);

    return 0;
}
