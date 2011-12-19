/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>
 * @date    2011 12月 19 15:22:01 CST
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
    int num;

    table = g_hash_table_new(NULL, NULL);

    num = 1;
    g_hash_table_insert(table, "one", &num);

    g_hash_table_destroy(table);

    return 0;
}
