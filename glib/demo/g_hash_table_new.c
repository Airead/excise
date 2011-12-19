/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>
 * @date    2011 12月 19 14:55:34 CST
 ********************************************************/


#if 0
Creates a new GHashTable with a reference count of 1.

hash_func :
a function to create a hash value from a key. Hash values are used to determine where keys are stored within the GHashTable data structure. The g_direct_hash(), g_int_hash(), g_int64_hash(), g_double_hash() and g_str_hash() functions are provided for some common types of keys. If hash_func is NULL, g_direct_hash() is used.
key_equal_func :

a function to check two keys for equality. This is used when looking up keys in the GHashTable. The g_direct_equal(), g_int_equal(), g_int64_equal(), g_double_equal() and g_str_equal() functions are provided for the most common types of keys. If key_equal_func is NULL, keys are compared directly in a similar fashion to g_direct_equal(), but without the overhead of a function call.
Returns :
a new GHashTable.
#endif

#include <glib.h>

int main(int argc, char *argv[])
{
    GHashTable *hashtable;

    hashtable = g_hash_table_new(NULL, NULL);
    if (hashtable == NULL) {
        g_printerr("create hash table failed\n");
        return -1;
    }

    g_print("create hash table success\n");

    g_hash_table_destroy(hashtable);

    return 0;
}
