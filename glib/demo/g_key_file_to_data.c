/**
 * @file g_key_file_to_data.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012  2月 29 14:42:52 CST
 *
 * This function outputs key_file as a string.
 *
 * Note that this function never reports an error, so it is safe to pass NULL as
 * error.
 */

#include <glib.h>

int main(int argc, char *argv[])
{
    GError *error = NULL;
    GKeyFile *keyfile;
    gchar *filepath;
    gchar *data;
    gsize length;

    filepath = "not_exist";

    keyfile = g_key_file_new();

    g_key_file_load_from_file(keyfile, filepath, G_KEY_FILE_NONE, &error);
    if (error != NULL) {
        g_printerr("load file failed: %s\n", error->message);
        g_error_free(error);
        error = NULL;
    } else {
        g_print("load file successful\n");
    }

    filepath = "key_file_example.ini";
    g_key_file_load_from_file(keyfile, filepath, G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS, &error);
    if (error != NULL) {
        g_printerr("load file failed: %s\n", error->message);
        g_error_free(error);
        error = NULL;
    } else {
        g_print("load file successful\n");
    }

    data = g_key_file_to_data(keyfile, &length, &error);
    if (error != NULL) {
        g_printerr("keyfile to data failed: %s\n", error->message);
        g_error_free(error);
        error = NULL;
    } else {
        g_print("keyfile to data successful\n");
    }

    g_print("data:\n%s\n", data);

    g_key_file_free(keyfile);

    return 0;
}
