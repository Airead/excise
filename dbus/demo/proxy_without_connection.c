#include <dbus/dbus-glib.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    DBusGConnection *connection;
    DBusGProxy *proxy;
    gchar *state;
    gchar *cmd;
    GError *error = NULL;

    g_type_init();

    /* conect system connection and get proxy */
    connection = dbus_g_bus_get(DBUS_BUS_SYSTEM, &error);
    if (connection == NULL) {
        g_printerr("get system bus failed: %s\n", error->message);
        g_error_free(error);
    }

    proxy = dbus_g_proxy_new_for_name(connection, 
                                      "net.connman",
                                      "/",
                                      "net.connman.Manager");

    cmd = "GetState";
    if (!dbus_g_proxy_call(proxy, cmd, &error,
                      G_TYPE_INVALID,
                      G_TYPE_STRING, &state,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", cmd, error->message);
        g_error_free(error);
    }

    g_print("before unref connection\n");
    g_print("state: %s\n", state);
    
    g_free(state);
    dbus_g_connection_unref(connection);

    dbus_g_proxy_call(proxy, "GetState", &error,
                      G_TYPE_INVALID,
                      G_TYPE_STRING, &state,
                      G_TYPE_INVALID);


    g_print("after unref connection\n");
    g_print("state: %s\n", state);

    g_object_unref(proxy);

    return 0;
}
