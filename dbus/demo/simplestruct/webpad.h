#ifndef WEBPAD_H
#define WEBPAD_H

#include <dbus/dbus-glib.h>

typedef struct Webpad Webpad;
typedef struct WebpadClass WebpadClass;

struct Webpad {
    GObject parent;
};

struct WebpadClass {
    GObjectClass parent;
};

GType webpad_get_type(void);
airead_fan_signature_print
airead_fan_int
airead_fan_byte_print
airead_fan_string_print
airead_fan_uint
airead_fan_double_print
airead_fan_int
airead_fan_int
airead_fan_objectpath_print
airead_fan_boolean_print
airead_fan_uint
airead_fan_uint

gboolean webpad_send_stream(Webpad *obj, GArray *input_stream, guint input_len, GArray **output_stream, guint *output_len, GError **error);

#endif
