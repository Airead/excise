#include <gio/gio.h>

static const gchar connman_manager_xml[] = 
"<node name='/'>"
"	<interface name='net.connman.Manager'>"
"		<method name='GetProperties'>"
"			<arg type='a{sv}' direction='out'/>"
"		</method>"
"		<method name='SetProperty'>"
"			<arg type='s' direction='in'/>"
"			<arg type='v' direction='in'/>"
"		</method>"
"		<method name='GetState'>"
"			<arg type='s' direction='out'/>"
"		</method>"
"		<method name='CreateProfile'>"
"			<arg type='s' direction='in'/>"
"			<arg type='o' direction='out'/>"
"		</method>"
"		<method name='RemoveProfile'>"
"			<arg type='o' direction='in'/>"
"		</method>"
"		<method name='RemoveProvider'>"
"			<arg type='s' direction='in'/>"
"		</method>"
"		<method name='RequestScan'>"
"			<arg type='s' direction='in'/>"
"		</method>"
"		<method name='EnableTechnology'>"
"			<arg type='s' direction='in'/>"
"		</method>"
"		<method name='DisableTechnology'>"
"			<arg type='s' direction='in'/>"
"		</method>"
"		<method name='ConnectService'>"
"			<arg type='a{sv}' direction='in'/>"
"			<arg type='o' direction='out'/>"
"		</method>"
"		<method name='ConnectProvider'>"
"			<arg type='a{sv}' direction='in'/>"
"			<arg type='o' direction='out'/>"
"		</method>"
"		<method name='RegisterAgent'>"
"			<arg type='o' direction='in'/>"
"		</method>"
"		<method name='UnregisterAgent'>"
"			<arg type='o' direction='in'/>"
"		</method>"
"		<method name='RegisterCounter'>"
"			<arg type='o' direction='in'/>"
"			<arg type='u' direction='in'/>"
"		</method>"
"		<method name='UnregisterCounter'>"
"			<arg type='o' direction='in'/>"
"		</method>"
"                <method name='GetServices'>"
"                        <arg type='a(oa{sv})' direction='out'/>"
"                </method>"
"		<signal name='PropertyChanged'>"
"			<arg type='s'/>"
"			<arg type='v'/>"
"		</signal>"
"		<signal name='StateChanged'>"
"			<arg type='s'/>"
"		</signal>"
"	</interface>"
"	<node name='org'/>"
"	<node name='profile'/>"
"</node>"
;

#if 0
typedef enum
{
    G_DBUS_PROXY_FLAGS_NONE = 0,
    G_DBUS_PROXY_FLAGS_DO_NOT_LOAD_PROPERTIES = (1<<0),
    G_DBUS_PROXY_FLAGS_DO_NOT_CONNECT_SIGNALS = (1<<1),
    G_DBUS_PROXY_FLAGS_DO_NOT_AUTO_START = (1<<2)
} GDBusProxyFlags;
#endif

void proxy_flags_print(GDBusProxyFlags flags)
{
    if (flags & G_DBUS_PROXY_FLAGS_NONE) {
        g_print("none set\n");
    }
    if (flags & G_DBUS_PROXY_FLAGS_DO_NOT_AUTO_START) {
        g_print("not auto start set\n");
    }
    if (flags & G_DBUS_PROXY_FLAGS_DO_NOT_CONNECT_SIGNALS) {
        g_print("not connect signals set\n");
    }
    if (flags & G_DBUS_PROXY_FLAGS_DO_NOT_LOAD_PROPERTIES) {
        g_print("not load properties set\n");
    }
}

int main(int argc, char *argv[])
{
    GDBusConnection *connection;
    GError *error = NULL;
    GDBusProxy *proxy;
    gchar *name;
    gchar *object_path;
    gchar *interface_name;
    GDBusProxyFlags flags;

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
                                  G_DBUS_PROXY_FLAGS_DO_NOT_AUTO_START
                                  | G_DBUS_PROXY_FLAGS_DO_NOT_CONNECT_SIGNALS,
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

    flags = g_dbus_proxy_get_flags(proxy);
    g_print("flags: %d\n", (int)flags);
    proxy_flags_print(flags);

    /**
     * get cached property
     */
    GVariant *val;
#if 0
    GDBusNodeInfo *introspection_data;
    GDBusInterfaceInfo *info;

    introspection_data = g_dbus_node_info_new_for_xml(connman_manager_xml, NULL);
    if (introspection_data == NULL) {
        g_printerr("get introspection_data failed\n");
        return -1;
    }
    info = introspection_data->interfaces[0];
    g_dbus_proxy_set_interface_info(proxy, info);
#endif

    //GVariant *g_dbus_proxy_get_cached_property (GDBusProxy *proxy,
    //const gchar *property_name);
    val = g_dbus_proxy_get_cached_property(proxy, "ActiveProfile");
    if (val == NULL) {
        g_print("get val failed\n");
        return -1;
    }
    g_print("get val success\n");

    return 0;
}
