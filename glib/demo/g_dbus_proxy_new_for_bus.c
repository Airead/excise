#include <gio/gio.h>

static GMainLoop *loop;

static void new_cb(GObject *source_object, GAsyncResult *res,
                   gpointer user_data)
{
    GDBusProxy *proxy;
    GError *error;

    proxy = g_dbus_proxy_new_finish(res, &error);
    if (proxy == NULL) {
        if (error != NULL) {
            g_printerr("get proxy failed: %s\n", error->message);
        } else {
            g_printerr("get proxy failed: %s\n", "unknown error");
        }
    }
    g_print("get proxy success\n");
    g_print("step into new_cp...\n");

    g_main_loop_quit(loop);
}

int main(int argc, char *argv[])
{
    GDBusProxy *proxy;
    gchar *name;
    gchar *object_path;
    gchar *interface_name;

    g_type_init();

    name = "net.connman";
    object_path = "/";
    interface_name = "net.connman.Manager";

#if 0
    void g_dbus_proxy_new_for_bus (GBusType bus_type,
                                   GDBusProxyFlags flags,
                                   GDBusInterfaceInfo *info,
                                   const gchar *name,
                                   const gchar *object_path,
                                   const gchar *interface_name,
                                   GCancellable *cancellable,
                                   GAsyncReadyCallback callback,
                                   gpointer user_data);

#endif

    g_dbus_proxy_new_for_bus(G_BUS_TYPE_SYSTEM,
                             G_DBUS_PROXY_FLAGS_NONE,
                             NULL,
                             name,
                             object_path,
                             interface_name,
                             NULL,
                             new_cb,
                             &proxy);

    loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    return 0;
}
