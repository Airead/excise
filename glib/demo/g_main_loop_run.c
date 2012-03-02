#include <glib.h>

int main(int argc, char *argv[])
{
    GMainLoop *loop;
    gint count = 0;

    loop = g_main_loop_new(NULL, FALSE);
    
    g_print("%d\n", count++);

    g_main_loop_run(loop);
    
    g_print("loop over\n");

    g_main_loop_unref(loop);
    return 0;
}

