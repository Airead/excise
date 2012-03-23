/**
 * @file g_hash_table_iter_init.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/03/23 12:19:22
 */

#include <glib.h>


int main(int argc, char *argv[])
{
    GHashTable *table;
    GHashTableIter iter;

    table = g_hash_table_new(NULL, NULL);
    g_print("table size: %u\n", g_hash_table_size(table));

    g_hash_table_iter_init (&iter, table);

    g_hash_table_destroy(table);

    return 0;
}
