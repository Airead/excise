/**
 * @file g_key_file_load_from_data_dirs.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012  2月 29 14:18:02 CST
 *
 * This function looks for a key file named file in the paths returned from
 * g_get_user_data_dir() and g_get_system_data_dirs(), loads the file into
 * key_file and returns the file's full path in full_path. If the file could not
 * be loaded then an error is set to either a GFileError or GKeyFileError.
 */

#include <glib.h>

#if 0
key_file :

an empty GKeyFile struct
file :

a relative path to a filename to open and parse
full_path :

return location for a string containing the full path of the file, or NULL
flags :

flags from GKeyFileFlags
error :

return location for a GError, or NULL
Returns :

TRUE if a key file could be loaded, FALSE othewise
#endif

int main(int argc, char *argv[])
{


    return 0;
}
