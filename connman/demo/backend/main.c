/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>
 * @date    2011 12月 19 13:01:03 CST
 ********************************************************/

#include <stdio.h>
#include <gio/gio.h>
#include "connman-manager.h"




#define STDIN_BUF_SIZE    1024
static gboolean channel_cb(GIOChannel *source, GIOCondition condition, gpointer data)
{
    int rc;
    char buf[STDIN_BUF_SIZE + 1];
    struct connman_manager *conn_manager = (struct connman_manager *)data;

    if (condition != G_IO_IN) {
        return TRUE;
    }
    
    /* We've received something on stdin. */
    printf("# ");
    rc = fscanf(stdin, "%s", buf);
    if (rc <= 0) {
        printf("NULL\n");
        return TRUE;
    }

    conn_manager_get_properties(conn_manager);

    return TRUE;
}

int main(int argc, char *argv[])
{
    GIOChannel *chan;
    struct connman_manager conn_manager;
    
    g_type_init();

    conn_manager_init(&conn_manager);
    
  if (G_TYPE_CHECK_INSTANCE_TYPE(conn_manager.proxy, G_TYPE_DBUS_PROXY)) {
      g_printerr("proxy is a G_TYPE_DBUS_PROXY\n");
      //return -1;
  } else {
      g_printerr("proxy is a G_TYPE_DBUS_PROXY\n");
  }

    chan = g_io_channel_unix_new(0);
    g_io_add_watch(chan, G_IO_IN, channel_cb, &conn_manager);

    g_main_loop_run(conn_manager.loop);

    return 0;
}
