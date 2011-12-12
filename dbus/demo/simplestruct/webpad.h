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
gboolean webpad_send_stream(Webpad *obj, GArray *input_stream, guint input_len, GArray **output_stream, guint *output_len, GError **error);

#endif
