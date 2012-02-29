/**
 * @file g_key_file_set_list_separator.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012  2月 29 14:01:45 CST
 *
 * Sets the character which is used to separate values in lists. Typically ';'
 * or ',' are used as separators. The default list separator is ';'.
 */

#include <glib.h>

int main(int argc, char *argv[])
{
    GKeyFile *keyfile;

    keyfile = g_key_file_new();

    g_key_file_set_list_separator(keyfile, ';');

    g_key_file_free(keyfile);

    return 0;
}
