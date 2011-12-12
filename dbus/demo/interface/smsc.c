#include <dbus/dbus-glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib/giochannel.h>
#include "sms-marshal.h"
#include "sms_features.h"

#define SMSC_DEBUG

static void lose (const char *str, ...)
{
    va_list args;
    va_start (args, str);
    vfprintf (stderr, str, args);
    fputc ('\n', stderr);
    va_end (args);
    exit (1);
}

static void lose_gerror (const char *prefix, GError *error) 
{
    if (error) {
        lose ("%s: %s", prefix, error->message);
    }
    else {
        lose ("%s", prefix);
    }
}

static void send_message(DBusGProxy *remote_object)
{
    GError *error = NULL;
    GHashTable *features;
    int ret;

    features = sms_create_features ("gsm", 8, 2);
    printf("SendMessage ");

    if (!dbus_g_proxy_call (remote_object, "SendMessage", &error,
        G_TYPE_STRING, "10987654321", G_TYPE_STRING, "hello world", 
        sms_get_features_type(), features, G_TYPE_INVALID,
        G_TYPE_INT, &ret, G_TYPE_INVALID))
        lose_gerror ("Failed to complete SendMessage", error);

    printf("return %d\n", ret);
    sms_release_features(features);
}

static void incoming_message_handler (DBusGProxy *proxy, const char *address, const char *contents, GHashTable *features, gpointer user_data)
{
    printf ("Received message with addree \"%s\" and it says: \n%s\n", address, contents);
    sms_show_features(features);
}


#define STDIN_BUF_SIZE    1024
static gboolean channel_cb(GIOChannel *source, GIOCondition condition, gpointer data)
{
    int rc;
    char buf[STDIN_BUF_SIZE+1];
    DBusGProxy *remote_object = (DBusGProxy *)data;

    if (condition != G_IO_IN) {
        return TRUE;
    }

    /* we've received something on stdin.    */
    printf("# ");
    rc = fscanf(stdin, "%s", buf);
    if (rc <= 0) {
        printf("NULL\n");
        return TRUE;
    }
    
    if (!strcmp(buf, "h")) {
        printf("shell_help\n");
    } else if (!strcmp(buf, "?")) {
        printf("shell_help\n");
    } else if (!strcmp(buf, "s")) {
        send_message(remote_object);
    } else if (!strcmp(buf, "q")) {
        exit(0);
    } else {
        printf("Unknown command `%s'\n", buf);
    }
    return TRUE;
}


int main(int argc, char *argv[])
{
    DBusGConnection *bus;
    DBusGProxy *remote_object;
    GError *error = NULL;
    GMainLoop *mainloop;
    GIOChannel *chan;
    guint source;
    GType features_type;

#ifdef SMSC_DEBUG
    g_slice_set_config(G_SLICE_CONFIG_ALWAYS_MALLOC, TRUE);
#endif

    g_type_init();
    mainloop = g_main_loop_new(NULL, FALSE);

    bus = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
    if (!bus) {
        lose_gerror("Couldn't connect to session bus", error);
    }

    remote_object = dbus_g_proxy_new_for_name(bus, "org.freesmartphone.ogsmd",
                                              "/org/freesmartphone/GSM/Device",
                                              "org.freesmartphone.GSM.SMS");
    if (!remote_object) {
        lose_gerror("Failed to get name owner", NULL);
    }

    features_type = sms_get_features_type();
    dbus_g_object_register_marshaller(sms_marshal_VOID__STRING_STRING_BOXED, G_TYPE_NONE, G_TYPE_STRING, G_TYPE_STRING, features_type, G_TYPE_INVALID);

    dbus_g_proxy_add_signal(remote_object, "IncomingMessage", G_TYPE_STRING, G_TYPE_STRING, features_type, G_TYPE_INVALID);

    dbus_g_proxy_connect_signal(remote_object, "IncomingMessage", G_CALLBACK(incoming_message_handler), NULL, NULL);

    chan = g_io_channel_unix_new(0);
    source = g_io_add_watch(chan, G_IO_IN, channel_cb, remote_object);
    g_main_loop_run(mainloop);
    
    return 0;
}
