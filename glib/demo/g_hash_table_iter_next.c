/**
 * @file g_hash_table_iter_next.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/03/23 12:23:14
 */

#include <glib.h>

int main(int argc, char *argv[])
{
    GHashTable *table;
    GHashTableIter iter;
    gpointer key, value;
    int num[3];
    int i;

    table = g_hash_table_new(NULL, NULL);
    
    for (i = 0; i < 3; i++) {
        num[i] = i + 1;
    }

    g_hash_table_insert(table, "a", &num[0]);
    g_hash_table_insert(table, "b", &num[1]);
    g_hash_table_insert(table, "c", &num[2]);

    g_hash_table_iter_init (&iter, table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        /* do something with key and value */
        g_print("%s: %d\n", (char *)key, *(int *)value);
    }

    g_hash_table_destroy(table);

    return 0;
}
