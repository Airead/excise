/**
 * @file g_key_file_load_from_dirs.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012  2月 29 14:23:07 CST
 *
 * This function looks for a key file named file in the paths specified in
 * search_dirs, loads the file into key_file and returns the file's full path in
 * full_path. If the file could not be loaded then an error is set to either a
 * GFileError or GKeyFileError.
 */

#include <glib.h>

#if 0
key_file :

an empty GKeyFile struct
file :

a relative path to a filename to open and parse
search_dirs :

NULL-terminated array of directories to search
full_path :

return location for a string containing the full path of the file, or NULL
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
    gchar *file;
    gchar *full_path_1, *full_path_2;
    const gchar *search_dirs[] = {".",
                                  "/var/lib/connman",
                                  NULL
    };

    g_print("=================================\n");
    file = "key_file_example.ini";
    
    keyfile = g_key_file_new();

    g_key_file_load_from_dirs(keyfile, file, search_dirs,
                              &full_path_1, G_KEY_FILE_NONE, &error);
    if (error != NULL) {
        g_printerr("load file failed: %s\n", error->message);
        g_error_free(error);
        error = NULL;
    } else {
        g_print("load file successful\n");
    }
    g_print("full_path:\n%s\n", full_path_1);


    g_print("=================================\n");
    file = "settings";
    
    keyfile = g_key_file_new();

    g_key_file_load_from_dirs(keyfile, file, search_dirs,
                              &full_path_2, G_KEY_FILE_NONE, &error);
    if (error != NULL) {
        g_printerr("load file failed: %s\n", error->message);
        g_error_free(error);
        error = NULL;
    } else {
        g_print("load file successful\n");
    }
    g_print("full_path:\n%s\n", full_path_2);


    g_key_file_free(keyfile);

    return 0;
}
