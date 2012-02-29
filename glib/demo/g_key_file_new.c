/**
 * @file g_key_file_new.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012  2月 29 13:53:27 CST
 *
 * Creates a new empty GKeyFile object. Use g_key_file_load_from_file(),
 * g_key_file_load_from_data(), g_key_file_load_from_dirs() or
 * g_key_file_load_from_data_dirs() to read an existing key file.
 */

#include <glib.h>

int main(int argc, char *argv[])
{
    GKeyFile *keyfile;

    keyfile = g_key_file_new();

    return 0;
}
