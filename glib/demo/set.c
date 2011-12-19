#include <glib.h>

GHashTable *
set_new (GHashFunc      hash_func,
         GEqualFunc     equal_func,
         GDestroyNotify destroy)
{
  return g_hash_table_new_full (hash_func, equal_func, destroy, NULL);
}

void
set_insert (GHashTable *set,
            gpointer    element)
{
  g_hash_table_insert (set, element, element);
}

gboolean
set_contains (GHashTable *set,
              gpointer    element)
{
  return g_hash_table_lookup_extended (set, element, NULL, NULL);
}

gboolean
set_remove (GHashTable *set,
            gpointer    element)
{
  return g_hash_table_remove (set, element);
}

/* just for compile */
int main(int argc, char *argv[])
{

    return 0;
}
