#include <stdio.h>
#include <stdlib.h>
#include <dbus/dbus-glib.h>

static GMainLoop *main_loop;

/* callback function */
static void my_callback_func(DBusGProxy *proxy, DBusGProxyCall *call_id, void *user_data)
{
    GError *error = NULL;
    gchar *string = NULL;

    /* IMPORTANT */
    dbus_g_proxy_end_call(proxy, call_id, &error, G_TYPE_STRING, &string, G_TYPE_INVALID);
    if (error != NULL) {
        g_print("Error in method call: %s\n", error->message);
        g_error_free(error);
        error = NULL;
    } else {
        g_print("SUCCESS, it is now %s\n", string);
    }
    
    g_main_loop_quit(main_loop);
}

int main(int argc, char *argv[])
{
    GError *error = NULL;
    DBusGConnection *connection;
    DBusGProxy *proxy;

    g_type_init();
    main_loop = g_main_loop_new(NULL, TRUE);

    connection = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
    if (connection == NULL) {
        g_printerr("Failed to open connection to bus: %s\n", error->message);
        g_error_free(error);
        error = NULL;
        exit(1);
    }

    proxy = dbus_g_proxy_new_for_name(connection, "org.freedesktop.Notifications",
                                      "/",
                                      DBUS_INTERFACE_INTROSPECTABLE);

    dbus_g_proxy_begin_call(proxy, "Introspect", my_callback_func, NULL, NULL,
                            G_TYPE_INVALID);
    g_main_loop_run(main_loop);

    return 0;
}
