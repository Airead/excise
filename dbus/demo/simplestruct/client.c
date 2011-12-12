/********************************************************
 * @author  Airead Fan <fgh1987168@gmail.com>
 * @date    2011 12月 12 10:23:43 CST
 ********************************************************/

#include <dbus/dbus-glib.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

int main(int argc, char *argv[])
{
    DBusGConnection *bus;
    GError *error;
    DBusGProxy *proxy;
    GArray *in_array, *out_array;
    guint in_len, out_len;
    struct ifs srcstruct, *retstruct;

    g_type_init();
    error = NULL;

    srcstruct.i = 123;
    srcstruct.f = 1.23;
    strncpy(srcstruct.s, "123", 4);

    in_array = g_array_new(FALSE, FALSE, 1);
    in_len = sizeof(struct ifs);
    g_array_append_vals(in_array, &srcstruct, in_len);

    /* connect bus  */
    bus = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
    if (!bus) {
        g_printerr("get bus failed: %s", error->message);
        g_error_free(error);
        error = NULL;
        exit(1);
    } else {
        g_print("get bus connection success\n");
    }

    /* create proxy and call method SendStream*/
    proxy = dbus_g_proxy_new_for_name(bus, "com.ijimu.webpad",
                                      "/com/ijimu/webpad/send_recv",
                                      "com.ijimu.webpad.stream");
    if (!dbus_g_proxy_call(proxy, "SendStream", &error,
                           DBUS_TYPE_G_UCHAR_ARRAY, in_array,
                           G_TYPE_UINT, in_len,
                           G_TYPE_INVALID,
                           DBUS_TYPE_G_UCHAR_ARRAY, &out_array,
                           G_TYPE_UINT, &out_len,
                           G_TYPE_INVALID)) {
        g_printerr("proxy call failed: %s", error->message);
        g_error_free(error);
        error = NULL;
        exit(1);
    }
                
    retstruct = &g_array_index(out_array, struct ifs, 0);
    g_print("receive struct:\n");
    g_print("i = %d, f = %f, s = %s\n", retstruct->i, retstruct->f, retstruct->s);

    return 0;
}
