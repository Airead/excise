#include <stdio.h>
#include <glib.h>
#include <dbus/dbus.h>

struct generic_data {
	unsigned int refcount;
	GSList *interfaces;
	char *introspect;
};


static DBusHandlerResult generic_message(DBusConnection *connection,
					DBusMessage *message, void *user_data)
{
	const char *interface;

    interface = dbus_message_get_interface(message);
    printf("interface: %s\n", interface);

    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}


static void generic_unregister(DBusConnection *connection, void *user_data)
{
}


static DBusObjectPathVTable generic_table = {
	.unregister_function	= generic_unregister,
	.message_function	= generic_message,
};

int main(int argc , char *argv[])
{
    DBusConnection *conn;
    DBusError error;
    int ret;
    GMainLoop *loop;

    dbus_error_init(&error);
    loop = g_main_loop_new(NULL, FALSE);
    
    /* get a connection */
    conn = dbus_bus_get(DBUS_BUS_SYSTEM, &error);
    if (dbus_error_is_set(&error) == TRUE){
        fprintf(stderr, "%s\n", error.message);
        dbus_error_free(&error);
    } 


    /* get a well-known name */
    ret = dbus_bus_request_name(conn, "net.connman",
                                DBUS_NAME_FLAG_DO_NOT_QUEUE, &error);

    if (dbus_error_is_set(&error) == TRUE){
        fprintf(stderr, "%s\n", error.message);
        dbus_error_free(&error);
    }


    if (ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {
        fprintf(stderr, "Name already in use\n");
    }

    /* register a path for well-known name*/
    if (!dbus_connection_register_object_path(conn, "/",
                                              &generic_table, NULL)) {
        fprintf(stderr, "can't get a path\n");
		return -1;
	}

    
    g_main_loop_run(loop);


    return 0;
}
