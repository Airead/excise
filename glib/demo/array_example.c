/**
 * @file array_example.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/03/23 13:34:49
 */

#include <glib.h>

int main(int argc, char *argv[])
{
    GArray *garray;
    gint i, j;

    /* We create a new array to store gint values.
       We don't want it zero-terminated or cleared to 0's. */

    garray = g_array_new (FALSE, FALSE, sizeof (gint));
    for (i = 0; i < 10; i++)
        g_array_append_val (garray, i);

    for (i = 0; i < 10; i++) {
        j = g_array_index (garray, gint, i);
        if (j != i) {
            g_print ("ERROR: got %d instead of %d\n",
                     g_array_index (garray, gint, i), j);
        }
        g_print("%d\n", j);
    }
    
    g_array_free (garray, TRUE);
    
    return 0;
}
