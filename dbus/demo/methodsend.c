#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus.h>
#include <unistd.h>
#include "datastruct.h"

DBusConnection *connect_dbus()
{
    DBusError err;
    DBusConnection *connection;
    int ret;

    //step 1. connection session bus
    dbus_error_init(&err);

    connection = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "Connection Err: %s\n", err.message);
        dbus_error_free(&err);
    }
    if (connection == NULL) {
        return NULL;
    }

    //step 2. Set Bus name
    ret = dbus_bus_request_name(connection, "test.wei.source", DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "Name Err: %s\n", err.message);
        dbus_error_free(&err);
    }
    if (ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {
        return NULL;
    }

    return connection;
}

void send_a_method_call(DBusConnection *connection, char *param)
{
    DBusError err;
    DBusMessage *msg;
    DBusMessageIter arg;
    DBusPendingCall *pending;
    dbus_bool_t *stat;
    dbus_uint32_t *level;
    struct ifs data; // = {123, 1.23, "ijimu"};

    dbus_error_init(&err);

    /* Construct a new message to invoke a method on a remote object */
    msg = dbus_message_new_method_call("test.wei.dest", "/test/method/Object", "test.method.Type", "Method");
    if (msg == NULL) {
        g_printerr("Message NULL");
        return ;
    }

    /* Append argument */
    dbus_message_iter_init_append(msg, &arg);
    if (!dbus_message_iter_append_basic(&arg, DBUS_TYPE_STRING, &param)) {
        g_printerr("Out of memory!");
        exit(1);
    }

    /* Queues a message to send, as with dubs_connection_send, bus also returns a DBusPendingCall used to receive a reply to the message. */
    if (!dbus_connection_send_with_reply(connection, msg, &pending, -1)) {
        g_printerr("out of memory!");
        exit(1);
    }

    if (pending == NULL) {
        g_printerr("Pending Call NULL: connection is disconnected");
        dbus_message_unref(msg);
        return ;
    }
    
    dbus_connection_flush(connection);
    dbus_message_unref(msg);

    /* waiting a reply, block until we recieve a reply and the pending call is completed */
    dbus_pending_call_block(pending);

    /* get the reply message, Gets the reply, or returns NULL if none has been received yet */
    msg = dbus_pending_call_steal_reply(pending);
    if (msg == NULL) {
        fprintf(stderr, "Reply Null\n");
        exit(1);
    }

    /* free the pending message handle */
    dbus_pending_call_unref(pending);

    /* read the parameters */
    if (!dbus_message_iter_init(msg, &arg)) {
        fprintf(stderr, "Message has no arguments!\n");
    } else if (dbus_message_iter_get_arg_type(&arg) != DBUS_TYPE_BOOLEAN) {
        fprintf(stderr, "Argument is not boolean!\n");
    } else {
        dbus_message_iter_get_basic(&arg, &stat);
    }

    if (!dbus_message_iter_next(&arg)) {
        fprintf(stderr, "Message has too few arguments!\n");
    } else if ( dbus_message_iter_get_arg_type (&arg) != DBUS_TYPE_UINT32 ) {
        fprintf(stderr, "Argument is not int!\n");
    } else {
        dbus_message_iter_get_basic (&arg, &level);
    }
    printf("Got Reply: %d, %d\n", (int)stat, (int)level);

#if 0
    /* receive struct */
    if (!dbus_message_iter_next(&arg)) {
        fprintf(stderr, "Message has too few arguments!\n");
    } else if ( dbus_message_iter_get_arg_type (&arg) != DBUS_TYPE_STRUCT ) {
        fprintf(stderr, "Argument is not struct!\n");
    } else {
        dbus_message_iter_get_basic (&arg, &data);
    }
    printf("Got struct: %d, %f, %s\n", data.i, data.f, data.s);
#endif

    dbus_message_unref(msg);
}


int main(int argc, char *argv[])
{
    DBusConnection *connection;

    connection = connect_dbus();
    if (connection == NULL) {
        exit(1);
    }

    send_a_method_call(connection, "Hello, D-Bus");

    return 0;
}
