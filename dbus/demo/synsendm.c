#include <stdio.h>
#include <stdlib.h>
#include <dbus/dbus-glib.h>

int main(int argc, char *argv[])
{
    GError *error;
    DBusGConnection *connection;
    DBusGProxy *proxy;
    char *string;

/*
 * Prior to any use of the type system, g_type_init() has to be called to initialize the type system and assorted other code portions (such as the various fundamental type implementations or the signal system).

 Since version 2.24 this also initializes the thread system
*/
    g_type_init();
    error = NULL;
    
    connection = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
    if (connection == NULL) {
        g_printerr("Failed to open connection to bus: %s\n", error->message);
        g_error_free(error);
        exit(1);
        error = NULL;
    }

    proxy = dbus_g_proxy_new_for_name(connection,
                                      "org.freedesktop.Notifications", 
                                      "/",
                                      "org.freedesktop.DBus.Introspectable");

    if (!dbus_g_proxy_call(proxy, "Introspect", &error, G_TYPE_INVALID, G_TYPE_STRING, &string, G_TYPE_INVALID)) {
        if (error->domain == DBUS_GERROR && error->code == DBUS_GERROR_REMOTE_EXCEPTION) {
            g_printerr("Caught remote method exception %s:%s", dbus_g_error_get_name(error), error->message);
        } else {
            g_printerr("Error: %s\n", error->message);
        }
        g_error_free(error);
        error = NULL;
        exit(1);
    }

    g_print("Message Method return from bus:\n%s\n", string);
    
    g_free(string);
    g_object_unref(proxy);

    return 0;
}
