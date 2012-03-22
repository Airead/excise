/**
 * @file basic_data.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/03/22 14:18:52
 */

#include <stdio.h>

#include "basic_data.h"
#include "all_basic_data_deliver_server.h"

G_DEFINE_TYPE(BasicData, basic_data, G_TYPE_OBJECT)

void basic_data_init(BasicData *obj)
{
}

void basic_data_class_init(BasicDataClass *obj)
{
    dbus_g_object_type_install_info(basic_data_get_type(), &dbus_glib_airead_fan_object_info);
}

gboolean airead_fan_signature_print(BasicData *obj, DBusGSignature *in_signature, DBusGSignature **out_signature, GError **error)
{
    printf("receive signature: %s\n", in_signature);

    *out_signature = g_strdup("ii");

	return TRUE;
}

gboolean airead_fan_objectpath_print(BasicData *obj, DBusGObjectPath *in_objectpath, DBusGObjectPath **out_objectpath, GError **error)
{
    printf("into objectpath print\n");
    printf("receive objectpath: %s\n", in_objectpath);
    *out_objectpath = g_strdup("/ojbect/retrun");

    return TRUE;
}
gboolean airead_fan_int32_print(BasicData *obj, gint32 in_int32, gint32 *out_int32, GError **error)
{
    printf("recevie int32: %d\n", in_int32);
    *out_int32 = in_int32 + 1;

	return TRUE;
}
gboolean airead_fan_byte_print(BasicData *obj, guchar in_byte, guchar *out_byte, GError **error)
{
    printf("receive byte: %c\n", in_byte);
    *out_byte = in_byte + 1;
	return TRUE;
}
gboolean airead_fan_string_print(BasicData *obj, gchar *in_str, gchar **out_str, GError **error)
{
    printf("receive string: %s\n", in_str);
    *out_str = g_strdup("stringstring");
	return TRUE;
}
gboolean airead_fan_uint16_print(BasicData *obj, guint16 in_uint16, guint16 *out_uint16, GError **error)
{
    printf("receive int16: %u\n", in_uint16);
    *out_uint16 = in_uint16 + 1;
	return TRUE;
}
gboolean airead_fan_double_print(BasicData *obj, gdouble in_double, gdouble *out_double, GError **error)
{
    printf("receive double: %f\n", in_double);
    *out_double = in_double + 1.5;
	return TRUE;
}
gboolean airead_fan_int64_print(BasicData *obj, gint64 in_int64, gint64 *out_int64, GError **error)
{
    printf("receive int64: %ld\n", (long int)in_int64);
    *out_int64 = in_int64 + 1;
	return TRUE;
}
gboolean airead_fan_int16_print(BasicData *obj, gint16 in_int16, gint16 *out_int16, GError **error)
{
    printf("receive int16: %d\n", in_int16);
    *out_int16 = in_int16 + 1;
	return TRUE;
}


#if 0
gboolean airead_fan_objectpath_print(BasicData *obj, DBusGObjectPath **out_objectpath, GError **error)
{
    const gchar *path;
    
    printf("into objectpath print\n");
//    path = g_variant_get_string(in_objectpath, NULL);
//    printf("receive objectpath: %s\n", path);
//    *out_objectpath = g_variant_new_object_path("/ojbect/retrun");
    *out_objectpath = g_strdup("/hello");
	return TRUE;
}
#endif

#if 0
gboolean airead_fan_objectpath_print(BasicData *obj, DBusGObjectPath *in_objectpath, GError **error)
{
    const gchar *path;
    
    printf("into objectpath print\n");
    printf("object path: %s\n", in_objectpath);
//    path = g_variant_get_string(in_objectpath, NULL);
//    printf("receive objectpath: %s\n", path);
//    *out_objectpath = g_variant_new_object_path("/ojbect/retrun");
    
	return TRUE;
}
#endif

gboolean airead_fan_boolean_print(BasicData *obj, gboolean in_bool, gboolean *out_bool, GError **error)
{
    printf("receive boolean: %d\n", in_bool);
    *out_bool = !in_bool;
	return TRUE;
}
gboolean airead_fan_uint64_print(BasicData *obj, guint64 in_uint64, guint64 *out_uint64, GError **error)
{
    printf("receive uint64: %lu\n", (unsigned long)in_uint64);
    *out_uint64 = in_uint64 + 1;
	return TRUE;
}
gboolean airead_fan_uint32_print(BasicData *obj, guint32 in_int32, guint32 *out_int32, GError **error)
{
    printf("receive uint32: %u\n", in_int32);
    *out_int32 = in_int32 + 1;
    
	return TRUE;
}

