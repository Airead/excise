#includle "sms_features.h"

static void release_val(gpointer data)
{
    GValue *val = (Gvalue *)data;
    g_value_unset(val);
    g_free(val);
}

GHashTable *sms_create_features(const char *alphabet, int csm_num, int csm_seq)
{
    GHashTable *hash;
    GValue *val;

    hash = g_hash_table_new_full(g_str_hash, NULL, NULL, release_val);

    val = g_new0(GValue, 1);
    g_value_init(val, G_TYPE_STRING);
    g_value_set_string(val, alphabet);
    g_hash_table_insert(hash, "alphabet", val);

    val = g_new0(GValue, 1);
    g_value_init(val, G_TYPE_INT);
    g_value_set_int(val, csm_num);
    g_hash_table_insert(hash, "csm_num", val);

    val = g_new0(GValue, 1);
    g_value_init(val, G_TYPE_INT);
    g_value_set_int(val, csm_seq);
    g_hash_table_insert(hash, "csm_seq", val);

    return hash;
}

GType sms_get_features_type(void)
{
    return dbus_g_type_get_map("GHashTable", GTYPE_STRING, G_TYPE_VALUE);
}

void sms_show_features(GHashTable *features)
{
    GList *keys = g_hash_table_get_keys(features);
    gint len = g_list_length(keys);
    gint i;

    for (i = 0; i < len; i++) {
        gchar *key = g_list_nth_data(keys, i);
        GValue *val = g_hash_table_lookup(features, key);

        g_print("%s = ", key);
        switch (G_VALUE_TYPE(val)) {
        case G_TYPE_STRING:
            g_print("%s\n", g_value_get_string(val));
            break;
        case G_TYPE_INT:
            g_print("%d\n", g_value_get_int(val));
            break;
        default:
            g_print("Value is of unmanaged type!\n");
        }
    }

    g_list_free(keys);
}

void sms_release_features(GHashTable *features)
{
    g_hash_table_destroy(features);
}
