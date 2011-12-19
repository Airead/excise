/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>
 * @date    2011 12月 19 16:51:24 CST
 ********************************************************/


#if 0
hash_table :
a GHashTable.
#endif

#include <glib.h>

void table_info(gpointer key, gpointer value, gpointer user_data)
{
    g_print("%s: %d\n", (gchar *)key, *(gint *)value);
}


int main(int argc, char *argv[])
{
    GHashTable *table;
    int num, num2, num3;

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
    g_hash_table_remove_all(table);

    g_print("====g_hash_table_foreach=1===\n");
    g_hash_table_foreach(table, table_info, NULL);


    g_hash_table_destroy(table);

    return 0;
}
