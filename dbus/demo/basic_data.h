/**
 * @file basic_data.h
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/03/22 14:02:31
 */

#ifndef _BASIC_DATA_H_
#define _BASIC_DATA_H_

#include <dbus/dbus-glib.h>

typedef struct BasicData BasicData;
typedef struct BasicDataClass BasicDataClass;

struct BasicData {
    GObject parent;
};

struct BasicDataClass {
    GObjectClass parent;
};

GType basic_data_get_type(void);
gboolean airead_fan_signature_print(BasicData *obj, DBusGSignature *in_signature, DBusGSignature **out_signature, GError **error);
gboolean airead_fan_objectpath_print(BasicData *obj, DBusGObjectPath *in_objectpath, DBusGObjectPath **out_objectpath, GError **error);
gboolean airead_fan_int32_print(BasicData *obj, gint32 in_int32, gint32 *out_int32, GError **error);
gboolean airead_fan_byte_print(BasicData *obj, guchar in_byte, guchar *out_byte, GError **error);
gboolean airead_fan_string_print(BasicData *obj, gchar *in_str, gchar **out_str, GError **error);
gboolean airead_fan_uint16_print(BasicData *obj, guint16 in_int16, guint16 *out_int16, GError **error);
gboolean airead_fan_double_print(BasicData *obj, gdouble in_double, gdouble *out_double, GError **error);
gboolean airead_fan_int64_print(BasicData *obj, gint64 in_int64, gint64 *out_int64, GError **error);
gboolean airead_fan_int16_print(BasicData *obj, gint16 in_int16, gint16 *out_int16, GError **error);
gboolean airead_fan_boolean_print(BasicData *obj, gboolean in_bool, gboolean *out_bool, GError **error);
gboolean airead_fan_uint64_print(BasicData *obj, guint64 in_int64, guint64 *out_int64, GError **error);
gboolean airead_fan_uint32_print(BasicData *obj, guint32 in_int32, guint32 *out_int32, GError **error);

#endif /* _BASIC_DATA_H_ */
