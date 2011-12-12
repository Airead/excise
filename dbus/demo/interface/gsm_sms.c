#include <dbus/dbus-glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gsm_sms.h"
#include "sms-marshal.h"
#include "sms_features.h"

enum 
{
    INCOMING_MESSAGE,
    LAST_SIGNAL
};

static guint signals[LAST_SIGNAL];

G_DEFINE_TYPE(GsmSms, gsm_sms, G_TYPE_OBJECT)

static void gsm_sms_init(GsmSms *obj)
{
}

static void gsm_sms_class_init(GsmSmsClass *class)
{
    /* Creates a new signal.(This is usually done in the class initializer.) */
#if 0 
    guint g_signal_new (const gchar *signal_name, //the name for the signal

                        GType itype, //the type this signal pertains to. it will also pertain to type which are derived from this type.

                        GSignalFlags signal_flags, //You should at least specify G_SIGNAL_RUN_FIRST/LAST

                        guint class_offset, //The offset of the function pointer in the class structure for this type. Pass 0 to not associate a class method slot with this signal.

                        GSignalAccumulator accumulator, // hte accumulator for the signal; may be NULL.

                        gpointer accu_data, //user data for the accumulator

                        GSignalCMarshaller c_marshaller, //the function to translate arrays of parameter values to signal emissions into C language callback invocations or NULL.[allow-none]

                        GType return_type, //the type of return value, or G_TYPE_NONE for a signal without a return value.

                        guint n_params, //the number of parameter types to follow.

                        ...); //a list of type, one for each parameter
#endif
   
    signals[INCOMING_MESSAGE] = g_signal_new (
        "incoming_message",
        G_OBJECT_CLASS_TYPE(class), /* return class id */
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
        0,
        NULL, NULL,
        sms_marshal_VOID__STRING_STRING_BOXED,
        G_TYPE_NONE, 3, G_TYPE_STRING, G_TYPE_STRING,
        sms_get_features_type()); /* call function */

}

gboolean gsm_sms_send_message(GsmSms *obj, const char *number, const char *contents,
                              GHashTable *featuremap, int *ret, GError **error)
{
    printf("number = %s\n", number);
    printf("contents = %s\n", contents);
    sms_show_features(featuremap);
    *ret = strlen(contents);
    return TRUE;
}

void gsm_sms_emit_incoming_message(GsmSms *obj, const char * address, 
    const char * contents, GHashTable *hash)
{
    g_signal_emit (obj, signals[INCOMING_MESSAGE], 0, address, contents, hash);
}
