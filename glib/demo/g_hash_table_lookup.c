/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>
 * @date    2011 12月 19 15:46:17 CST
 ********************************************************/

/**
   hash_table :
   a GHashTable.

   key :
   the key to look up.

   Returns :
   the associated value, or NULL if the key is not found.
*/
    
#include <glib.h>
    

int look_up_num(GHashTable *table, gchar *key)
{
    gint *value;

    if ((value = g_hash_table_lookup(table, key))) {
        g_print("%s exist: %d\n", key, *value);
    } else {
        g_print("%s not exist\n", key);
    }

    return 0;
}

int look_up_str(GHashTable *table, gchar *key)
{
    gchar *str;

    if ((str = g_hash_table_lookup(table, key))) {
        g_print("%s exist: %s\n", key, str);
    } else {
        g_print("%s not exist\n", key);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    GHashTable *table;
    int num, num2;

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
    
    g_hash_table_insert(table, "three", NULL);
    g_print("table size: %u\n", g_hash_table_size(table));

    g_hash_table_insert(table, "four", "fourth");
    g_print("table size: %u\n", g_hash_table_size(table));

    look_up_num(table, "one");
    look_up_num(table, "two");
    look_up_num(table, "three");
    look_up_str(table, "four");
    look_up_num(table, "five");

    g_hash_table_destroy(table);

    return 0;
}

