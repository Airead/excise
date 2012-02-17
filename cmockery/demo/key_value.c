#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValue {
    unsigned int key;
    const char *value;
} KeyValue;

static KeyValue *key_values = NULL;
static unsigned int number_of_key_values = 0;

void set_key_values(KeyValue * const new_key_values,
                    const unsigned int new_number_of_key_values)
{
    key_values = new_key_values;
    number_of_key_values = new_number_of_key_values;
}

/* Compare two key members of KeyValue structures. */
int key_value_compare_keys(const void *a, const void *b)
{
    return (int)((KeyValue *)a)->key - (int)((KeyValue *)b)->key;
}

/* Search an array of key value pairs for the item with the specified value. */
KeyValue *find_item_by_value(const char * const value)
{
    unsigned int i;

    for (i = 0; i < number_of_key_values; i++) {
        if (strcmp(key_values[i].value, value) == 0) {
            return &key_values[i];
        }
    }

    return NULL;
}

/* Sort an array of key value pairs by key */
void sort_items_by_key()
{
    qsort(key_values, number_of_key_values, sizeof(*key_values),
          key_value_compare_keys);
}
