/**
 * @file all_basic_data_deliver_client.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/03/22 10:51:21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus-glib.h>

#define METHOD_STRLEN 128

int send_recv_boolean(DBusGProxy *proxy, char *method, char *value)
{
    gboolean bool, ret;
    GError *error = NULL;

    if (!strcmp(value, "False")) {
        bool = FALSE;
    } else {
        bool = TRUE;
    }
    if (!dbus_g_proxy_call(proxy, method, &error,
                           G_TYPE_BOOLEAN, bool,
                           G_TYPE_INVALID,
                           G_TYPE_BOOLEAN, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }
    printf("receive %d\n", ret);

    return 0;
}

int send_recv_byte(DBusGProxy *proxy, char *method, char *value)
{
    guchar byte, ret;
    GError *error = NULL;

    byte = value[0];

    if (!dbus_g_proxy_call(proxy, method, &error,
                           G_TYPE_UCHAR, byte,
                           G_TYPE_INVALID,
                           G_TYPE_UCHAR, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }
    printf("receive %c\n", ret);
    
    return 0;
}

int send_recv_double(DBusGProxy *proxy, char *method, char *value)
{
    gdouble d, ret;
    GError *error = NULL;

    //double strtod(const char *nptr, char **endptr);
    d = strtod(value, NULL);

    if (!dbus_g_proxy_call(proxy, method, &error,
                           G_TYPE_DOUBLE, d,
                           G_TYPE_INVALID,
                           G_TYPE_DOUBLE, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }
    printf("receive %f\n", ret);
    
    return 0;
}

int send_recv_int16(DBusGProxy *proxy, char *method, char *value)
{
    gint16 int16, ret;
    GError *error = NULL;

    int16 = strtol(value, NULL, 10);

    if (!dbus_g_proxy_call(proxy, method, &error,
                           G_TYPE_INT, int16,
                           G_TYPE_INVALID,
                           G_TYPE_INT, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }
    printf("receive %d\n", ret);
    
    return 0;
}

int send_recv_int32(DBusGProxy *proxy, char *method, char *value)
{
    gint32 int32, ret;
    GError *error = NULL;

    int32 = strtol(value, NULL, 10);

    if (!dbus_g_proxy_call(proxy, method, &error,
                           G_TYPE_INT, int32,
                           G_TYPE_INVALID,
                           G_TYPE_INT, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }
    printf("receive %d\n", ret);
    
    return 0;
}

int send_recv_int64(DBusGProxy *proxy, char *method, char *value)
{
    gint64 int64, ret;
    GError *error = NULL;

    int64 = strtol(value, NULL, 10);

    if (!dbus_g_proxy_call(proxy, method, &error,
                           G_TYPE_INT64, int64,
                           G_TYPE_INVALID,
                           G_TYPE_INT64, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }
    printf("receive %ld\n", (long)ret);
    
    return 0;
}

int send_recv_objectpath(DBusGProxy *proxy, char *method, char *value)
{
    //typedef gchar DBusGObjectPath;
    const DBusGObjectPath *path, *ret;
    GError *error = NULL;

    path = value;

    if (!dbus_g_proxy_call(proxy, method, &error,
                           DBUS_TYPE_G_OBJECT_PATH, path,
                           G_TYPE_INVALID,
                           DBUS_TYPE_G_OBJECT_PATH, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }

    printf("receive %s\n", ret);
    
    return 0;
}

#if 0
int send_recv_objectpath(DBusGProxy *proxy, char *method, char *value)
{
    //typedef gchar DBusGObjectPath;
    const DBusGObjectPath *path;
    GVariant *gva, *ret;
    GError *error = NULL;

    if (!g_variant_is_object_path(value)) {
        fprintf(stderr, "is not vaild path!\n");
        return -1;
    } else {
        printf("is object path\n");
    }

    gva = g_variant_new_object_path(value);

    if (!dbus_g_proxy_call(proxy, method, &error,
                           G_TYPE_INVALID,
                           DBUS_TYPE_G_OBJECT_PATH, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }
    printf("receive %s\n", ret);
    
    return 0;
}
#endif

#if 0
int send_recv_objectpath(DBusGProxy *proxy, char *method, char *value)
{
    //typedef gchar DBusGObjectPath;
    const DBusGObjectPath *path;
    GVariant *gva, *ret;
    GError *error = NULL;

    if (!g_variant_is_object_path(value)) {
        fprintf(stderr, "is not vaild path!\n");
        return -1;
    } else {
        printf("is object path\n");
    }

    gva = g_variant_new_object_path(value);

    if (!dbus_g_proxy_call(proxy, method, &error,
                           DBUS_TYPE_G_OBJECT_PATH, value,
                           G_TYPE_INVALID,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }
//    printf("receive %s\n", ret);
    
    return 0;
}
#endif

int send_recv_signature(DBusGProxy *proxy, char *method, char *value)
{
    //typedef gchar DBusGSignature;
    DBusGSignature *signature, *ret;
    GError *error = NULL;

    signature = value;

    if (!dbus_g_proxy_call(proxy, method, &error,
                           DBUS_TYPE_G_SIGNATURE, signature,
                           G_TYPE_INVALID,
                           DBUS_TYPE_G_SIGNATURE, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }
    printf("receive %s\n", ret);
    
    return 0;
}

int send_recv_string(DBusGProxy *proxy, char *method, char *value)
{
    gchar *str, *ret;
    GError *error = NULL;

    str = value;

    if (!dbus_g_proxy_call(proxy, method, &error,
                           G_TYPE_STRING, str,
                           G_TYPE_INVALID,
                           G_TYPE_STRING, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }
    printf("receive %s\n", ret);
    
    return 0;
}

int send_recv_uint32(DBusGProxy *proxy, char *method, char *value)
{
    guint32 uint32, ret;
    GError *error = NULL;

    uint32 = strtoul(value, NULL, 10);

    if (!dbus_g_proxy_call(proxy, method, &error,
                           G_TYPE_UINT, uint32,
                           G_TYPE_INVALID,
                           G_TYPE_UINT, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }
    printf("receive %u\n", ret);
    
    return 0;
}

int send_recv_uint64(DBusGProxy *proxy, char *method, char *value)
{
    guint64 uint64, ret;
    GError *error = NULL;

    uint64 = strtoul(value, NULL, 10);

    if (!dbus_g_proxy_call(proxy, method, &error,
                           G_TYPE_UINT64, uint64,
                           G_TYPE_INVALID,
                           G_TYPE_UINT64, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }
    printf("receive %lu\n", (unsigned long)ret);
    
    return 0;
}

int send_recv_uint16(DBusGProxy *proxy, char *method, char *value)
{
    guint16 uint16, ret;
    GError *error = NULL;

    uint16 = strtoul(value, NULL, 10);

    if (!dbus_g_proxy_call(proxy, method, &error,
                           G_TYPE_UINT, uint16,
                           G_TYPE_INVALID,
                           G_TYPE_UINT, &ret,
                           G_TYPE_INVALID)) {
        g_printerr("call %s failed: %s\n", method, error->message);
        g_error_free(error);
        error = NULL;
        return -1;
    }
    printf("receive %u\n", ret);
    
    return 0;
}

int main(int argc, char *argv[])
{
    DBusGConnection *connection;
    GError *error = NULL;
    DBusGProxy *proxy;
    char *type, *value;
    char method[METHOD_STRLEN];

    if (argc < 3) {
        fprintf(stderr, "usage: %s <data_type> <data_value>\n", argv[0]);
        exit(1);
    }

    g_type_init();

    type = argv[1];
    value = argv[2];

    /* conect system connection and get proxy */
    connection = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
    if (connection == NULL) {
        g_printerr("get system bus failed: %s\n", error->message);
        g_error_free(error);
        return -1;
    }
    
    /* get proxy */
    proxy = dbus_g_proxy_new_for_name(connection, 
                                      "airead.fan.BasicDataType",
                                      "/airead/fan/BasicDataType",
                                      "airead.fan.BasicDataType");
    
    snprintf(method, METHOD_STRLEN, "%sPrint", type);

    if (!strcmp(type, "Boolean")) { /* gboolean */
        send_recv_boolean(proxy, method, value);
    }else if (!strcmp(type, "Byte")) { /* guchar */
        send_recv_byte(proxy, method, value);
    }else if (!strcmp(type, "Double")) {
        send_recv_double(proxy, method, value);
    }else if (!strcmp(type, "Int16")) {
        send_recv_int16(proxy, method, value);
    }else if (!strcmp(type, "Int32")) {
        send_recv_int32(proxy, method, value);
    }else if (!strcmp(type, "Int64")) {
        send_recv_int64(proxy, method, value);
    }else if (!strcmp(type, "Objectpath")) {
        send_recv_objectpath(proxy, method, value);
    }else if (!strcmp(type, "Signature")) {
        send_recv_signature(proxy, method, value);
    }else if (!strcmp(type, "String")) {
        send_recv_string(proxy, method, value);
    }else if (!strcmp(type, "Uint32")) {
        send_recv_uint32(proxy, method, value);
    }else if (!strcmp(type, "Uint64")) {
        send_recv_uint64(proxy, method, value);
    }else if (!strcmp(type, "Uint16")) {
        send_recv_uint16(proxy, method, value);
    }

    return 0;
}
