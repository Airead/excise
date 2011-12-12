#include <dbus/dbus-glib.h>
#include <stdlib.h>
#include "server.h"
#include "webpad.h"

int main(int argc, char *argv[])
{
    DBusGConnection *bus;
    DBusGProxy *proxy;
    GError *error = NULL;
    Webpad *obj;
    GMainLoop *mainloop;
    guint ret;

    g_type_init();

    mainloop = g_main_loop_new(NULL, FALSE);

    /* connect to session bus */
    bus = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
    if (bus == NULL) {
        g_printerr("get bus failed: %s", error->message);
        g_error_free(error);
        error = NULL;
        exit(1);
    } else {
        g_print("get bus success\n");
    }

    /* get proxy */
    proxy = dbus_g_proxy_new_for_name(bus, "org.freedesktop.DBus", 
                                      "/", "org.freedesktop.DBus");

    if (!dbus_g_proxy_call(proxy, "RequestName", &error,
                           G_TYPE_STRING, "com.ijimu.webpad",
                           G_TYPE_UINT, 0,
                           G_TYPE_INVALID,
                           G_TYPE_UINT, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("proxy call Request failed: %s", error->message);
        g_error_free(error);
        error = NULL;
        exit(1);
    } else {
        g_print("register wellkonwn bus success\n");
    }

    /* create a Webpad object */
    obj = g_object_new(webpad_get_type(), NULL);
    dbus_g_connection_register_g_object(bus, "/com/ijimu/webpad/send_recv", (GObject *)obj);

    g_main_loop_run(mainloop);

    return 0;
}
