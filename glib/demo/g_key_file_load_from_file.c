/**
 * @file g_key_file_load_from_file.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012  2月 29 14:04:32 CST
 *
 * Loads a key file into an empty GKeyFile structure. If the file could not be
 * loaded then error is set to either a GFileError or GKeyFileError.
 */

#include <glib.h>

#if 0
key_file :

an empty GKeyFile struct
file :

the path of a filename to load, in the GLib filename encoding
flags :

flags from GKeyFileFlags
error :

return location for a GError, or NULL
Returns :

TRUE if a key file could be loaded, FALSE otherwise
#endif

int main(int argc, char *argv[])
{
    GError *error = NULL;
    GKeyFile *keyfile;
    gchar *filepath;

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
    g_key_file_load_from_file(keyfile, filepath, G_KEY_FILE_NONE, &error);
    if (error != NULL) {
        g_printerr("load file failed: %s\n", error->message);
        g_error_free(error);
        error = NULL;
    } else {
        g_print("load file successful\n");
    }

    g_key_file_free(keyfile);

    return 0;
}
