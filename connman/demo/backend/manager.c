/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>
 * @date    2011 12月 19 13:00:45 CST
 ********************************************************/
#if 0

#include <dbus/dbus-glib.h>
#include "manager.h"
#include "error.h"
#include "global.h"

int manager_init(struct manager *self, gchar *bus, gchar *object, gchar *interface)
{
    DBusGConnection *connection;
    DBusGProxy *proxy;
    GError *error;

    /* init Gtype */
    g_type_init();
    error = NULL;
    
    /* conect system connection and get proxy */
    connection = dbus_g_bus_get(DBUS_BUS_SYSTEM, &error);
    if (connection == NULL) {
        PRINTERR("get system bus failed: %s\n", error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }
    DEBUG("get system bus success\n");

    proxy = dbus_g_proxy_new_for_name(connection, bus, object, interface);


    self->state = OFFLINE;
    self->proxy = proxy;
    g_strlcpy(self->bus, bus, BUF_NAME);
    g_strlcpy(self->object, object, BUF_NAME);
    g_strlcpy(self->interface, interface, BUF_NAME);
    
    return 0;
}

int manager_info(struct manager *self)
{
    g_print("=================================\n");
    g_print("bus name: %s\n", self->bus);
    g_print("object path: %s\n", self->object);
    g_print("interface: %s\n", self->interface);
    g_print("manager state: %d\n", self->state);
    g_print("=================================\n");

    return 0;
}

int manager_get_state(struct manager *self, gint *state)
{
    GError *error;
    gchar *state_tmp;
    gchar *cmd = "GetState";
    
    g_type_init();

    if (!dbus_g_proxy_call(self->proxy, cmd, &error,
                           G_TYPE_INVALID,
                           G_TYPE_STRING, &state_tmp,
                           G_TYPE_INVALID)) {
        PRINTERR("call %s failed: %s\n", cmd, error->message);
        g_error_free(error);
        error = NULL;
        manager_info(self);
        return -1;
    }
    
    g_print("manager state: %s\n\n", state_tmp);

    return 0;
}

int manager_get_properties(struct manager *self, GHashTable **properties_table)
{
    GError *error;
    GHashTable *table_tmp;        /* temporary GHashTable*/
    gchar *cmd = "GetProperties";

    g_type_init();

    if (!dbus_g_proxy_call(self->proxy, cmd, &error,
                           G_TYPE_INVALID,
                           DBUS_TYPE_G_STRING_VARIANT_HASHTABLE, &table_tmp,
                           G_TYPE_INVALID)) {
        PRINTERR("call %s failed: %s\n", cmd, error->message);
        g_error_free(error);
        error = NULL;
        manager_info(self);
        return -1;
    }
    DEBUG("%s call success\n", cmd);

    *properties_table = table_tmp;

    return 0;
}

#endif
