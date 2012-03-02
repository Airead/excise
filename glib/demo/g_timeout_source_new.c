#include <glib.h>

int main(int argc, char *argv[])
{
    GMainLoop *loop;
    GSource *source;
    gint count = 0;

    loop = g_main_loop_new(NULL, FALSE);

    source = g_timeout_source_new(1000);    
    g_print("%d\n", count++);
    g_main_loop_run(loop);
    
    g_print("loop over\n");

    g_main_loop_unref(loop);
    return 0;
}

