/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>
 * @date    2011 12月 26 14:16:00 CST
 ********************************************************/

#include <gio/gio.h>
#include "connman-manager.h"
#include "error.h"

static void
on_properties_changed (GDBusProxy          *proxy,
                       GVariant            *changed_properties,
                       const gchar* const  *invalidated_properties,
                       gpointer             user_data)
{
    /* Note that we are guaranteed that changed_properties and
     * invalidated_properties are never NULL
     */

    if (g_variant_n_children (changed_properties) > 0)
    {
        GVariantIter *iter;
        const gchar *key;
        GVariant *value;

        g_print (" *** Properties Changed:\n");
        g_variant_get (changed_properties,
                       "a{sv}",
                       &iter);
        while (g_variant_iter_loop (iter, "{&sv}", &key, &value))
        {
            gchar *value_str;
            value_str = g_variant_print (value, TRUE);
            g_print ("      %s -> %s\n", key, value_str);
            g_free (value_str);
        }
        g_variant_iter_free (iter);
    }

    if (g_strv_length ((GStrv) invalidated_properties) > 0)
    {
        guint n;
        g_print (" *** Properties Invalidated:\n");
        for (n = 0; invalidated_properties[n] != NULL; n++)
        {
            const gchar *key = invalidated_properties[n];
            g_print ("      %s\n", key);
        }
    }
}

static void
on_signal (GDBusProxy *proxy,
           gchar      *sender_name,
           gchar      *signal_name,
           GVariant   *parameters,
           gpointer    user_data)
{
    gchar *parameters_str;

    parameters_str = g_variant_print (parameters, TRUE);
    g_print (" *** Received Signal: %s: %s\n",
             signal_name,
             parameters_str);
    g_free (parameters_str);
}

static void
print_proxy (GDBusProxy *proxy)
{
    g_print("owner changed\n");
}

static void
on_name_owner_notify (GObject    *object,
                      GParamSpec *pspec,
                      gpointer    user_data)
{
    GDBusProxy *proxy = G_DBUS_PROXY (object);
    print_proxy (proxy);
}

int conn_manager_init(struct connman_manager *self)
{
    self->loop = g_main_loop_new(NULL, FALSE);
    
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

    void (*GAsyncReadyCallback) (GObject *source_object,
                                 GAsyncResult *res,
                                 gpointer user_data);
#endif
    g_dbus_proxy_new_for_bus(G_BUS_TYPE_SYSTEM, 
                             G_DBUS_PROXY_FLAGS_NONE,
                             NULL, 
                             CONNMAN_SERVICE_NAME, 
                             CONNMAN_MANAGER_PATH,
                             CONNMAN_MANAGER_INTERFACE,
                             NULL,
                             create_proxy_cb, 
                             self);

    return 0;
}

int conn_manager_destroy(struct connman_manager *self)
{
    g_object_unref(self->proxy);

    return 0;
}

static void get_properties_cb(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
    struct connman_manager *self = (struct connman_manager *)user_data;
    GVariant *result, *variant, *dict;
    GError *error = NULL;
    GVariantIter iter, dict_iter;
    gchar *name;

    g_return_if_fail(self != NULL);

    result = g_dbus_proxy_call_finish(self->proxy, res, &error);
    if (error != NULL) {
        g_warning("Failed to get connman properties: %s", error->message);
        g_error_free(error);
        return ;
    }
    g_print("get result\n");

    g_variant_iter_init(&iter, result);
    
    /* get the dict */
    dict = g_variant_iter_next_value(&iter);

    /* go through the dict */
    g_variant_iter_init(&dict_iter, dict);

    while (g_variant_iter_next(&dict_iter, "{sv}", &name, &variant)) {
        g_print("key: %s,\t", name);
        g_print("%s\n",g_variant_print(variant, TRUE));

        g_free(name);
    }
    g_print("=================================\n");
 
    g_variant_unref(dict);
    g_variant_unref(result);
}

int conn_manager_get_properties(struct connman_manager * conn_manager)
{
    GDBusProxy *proxy;

    proxy = conn_manager->proxy;
    
#if 0
    void g_dbus_proxy_call (GDBusProxy *proxy,
                            const gchar *method_name,
                            GVariant *parameters,
                            GDBusCallFlags flags,
                            gint timeout_msec,
                            GCancellable *cancellable,
                            GAsyncReadyCallback callback,
                            gpointer user_data);
#endif
    g_dbus_proxy_call(proxy, "GetProperties", 
                      NULL,
                      G_DBUS_CALL_FLAGS_NONE, -1,
                      NULL,
                      get_properties_cb,
                      conn_manager);

    return 0;
} 

void create_proxy_cb(GObject *source_object, GAsyncResult *res, 
                     gpointer user_data)
{
    struct connman_manager *self = (struct connman_manager *)user_data;
    GError *error = NULL;
    GDBusProxy *proxy;

    g_print("step into create_proxy_cb\n");

    proxy = g_dbus_proxy_new_finish(res, &error);
    if (error != NULL) {
        PRINTERR("Failed to get connman proxy: %s", error->message);
        g_error_free(error);
        return;
    }

    if (proxy == NULL) {
        PRINTERR("Failed to get connman proxy, but no errors");
        return;
    }

    /* register signal */
    g_signal_connect (proxy,
                      "g-properties-changed",
                      G_CALLBACK (on_properties_changed),
                      NULL);
    g_signal_connect (proxy,
                      "g-signal",
                      G_CALLBACK (on_signal),
                      NULL);
    g_signal_connect (proxy,
                      "notify::g-name-owner",
                      G_CALLBACK (on_name_owner_notify),
                      NULL);

    self->proxy = proxy;
}
