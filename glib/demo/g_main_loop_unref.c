#include <glib.h>

int main(int argc, char *argv[])
{
    GMainLoop *loop;

    loop = g_main_loop_new(NULL, FALSE);

    g_main_loop_unref(loop);
    return 0;
}

