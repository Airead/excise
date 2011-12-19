/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>
 * @date    2011 12月 19 15:29:42 CST
 ********************************************************/

#if 0
hash_table :
a GHashTable.

key :
a key to insert.

value :
the value to associate with the key.
#endif

#include <glib.h>

int main(int argc, char *argv[])
{
    GHashTable *table;
    int num, num2;

    table = g_hash_table_new(NULL, NULL);

    num = 1;
    g_hash_table_insert(table, "one", &num);
    
    /* key not exist */
    num2 = 2;
    g_hash_table_replace(table, "two", &num2);

    /* key exist */
    num = 3;
    g_hash_table_replace(table, "one", &num);

    g_hash_table_destroy(table);

    return 0;
}
