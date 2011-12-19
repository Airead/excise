/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>
 * @date    2011 12月 19 16:34:13 CST
 ********************************************************/

#if 0
hash_table :
a GHashTable.

predicate :
function to test the key/value pairs for a certain property.

user_data :
user data to pass to the function.

Returns :
The value of the first key/value pair is returned, for which predicate evaluates to TRUE. If no pair with the requested property is found, NULL is returned.
#endif

#include <glib.h>

gboolean table_info(gpointer key, gpointer value, gpointer user_data)
{
    gint *num;
    
    num = value;
    g_print("%s: %d\n", (gchar *)key, *num);
    if (*num == 3) {
        return TRUE;
    }
    
    return FALSE;
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

    g_print("====g_hash_table_foreach====\n");
    g_hash_table_find(table, table_info, NULL);

    g_hash_table_destroy(table);

    return 0;
}
