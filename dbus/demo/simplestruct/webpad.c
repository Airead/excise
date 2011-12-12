#include <stdlib.h>
#include <string.h>
#include "webpad.h"
#include "server.h"
#include "sr_stream_server.h"

G_DEFINE_TYPE(Webpad, webpad, G_TYPE_OBJECT)

void webpad_init(Webpad *obj)
{
}

void webpad_class_init(WebpadClass *obj)
{

    dbus_g_object_type_install_info(webpad_get_type(), &dbus_glib_webpad_object_info);
}

gboolean webpad_send_stream(Webpad *obj, GArray *input_stream, guint input_len, GArray **output_stream, guint *output_len, GError **error)
{
    struct ifs *recv;
    GArray *out_array;
    guint out_len;
    struct ifs out;

    recv = &g_array_index(input_stream, struct ifs, 0);
    g_print("receive struct:\n");
    g_print("i = %d\n", recv->i);
    g_print("f = %f\n", recv->f);
    g_print("s = %s\n", recv->s);

    out.i = recv->i + 1;
    out.f = recv->f + 1;
    strncpy(out.s, "123456", 7);

    out_array = g_array_new(FALSE, FALSE, 1);
    out_len = sizeof(struct ifs);
    g_array_append_vals(out_array, &out, out_len);

    *output_stream = out_array;
   
    return TRUE;
}
