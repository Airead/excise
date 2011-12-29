#include <gio/gio.h>

int main(int argc, char *argv[])
{
    GDBusConnection *connection;
    GError *error = NULL;
    GDBusProxy *proxy;
    gchar *name;
    gchar *object_path;
    gchar *interface_name;

    g_type_init();

    connection = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
    if (connection == NULL) {
        if (error != NULL) {
            g_printerr("get connection error: %s\n", error->message);
            g_error_free(error);
            
        } else {
            g_printerr("get connection error: unknown error\n");
        }
        return -1;

    } else {
        g_print("get connection success\n");
    }

    name = "net.connman";
    object_path = "/";
    interface_name = "net.connman.Manager";

#if 0
    GDBusProxy *g_dbus_proxy_new_sync (GDBusConnection *connection,
                                       GDBusProxyFlags flags,
                                       GDBusInterfaceInfo *info,
                                       const gchar *name,
                                       const gchar *object_path,
                                       const gchar *interface_name,
                                       GCancellable *cancellable,
                                       GError **error);
#endif

    proxy = g_dbus_proxy_new_sync(connection,
                             G_DBUS_PROXY_FLAGS_NONE,
                             NULL,
                             name,
                             object_path,
                             interface_name,
                             NULL,
                             &error);
    if (proxy == NULL) {
        if (error != NULL) {
            g_printerr("get proxy failed: %s\n", error->message);
        } else {
            g_printerr("get proxy failed: %s\n", "unknown error");
        }
    }
    g_print("get proxy success\n");

    return 0;
}
