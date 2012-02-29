/**
 * @file g_key_file_free.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012  2月 29 13:59:53 CST
 *
 * Frees a GKeyFile
 */

#include <glib.h>

int main(int argc, char *argv[])
{
    GKeyFile *keyfile;

    keyfile = g_key_file_new();

    g_key_file_free(keyfile);

    return 0;
}
