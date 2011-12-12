#ifndef GSM_SMS_H
#define GSM_SMS_H

typedef struct GsmSms GsmSms;
typedef struct GsmSmsClass GsmSmsClass;

struct GsmSms
{
  GObject parent;
};

struct GsmSmsClass
{
  GObjectClass parent;
};

#define GSM_SMS_TYPE                  (gsm_sms_get_type ())

GType gsm_sms_get_type (void);
gboolean gsm_sms_send_message (GsmSms *obj, const char *number, const char *contents, GHashTable *featuremap, int *ret, GError **error);
void gsm_sms_emit_incoming_message(GsmSms *obj, const char * address, const char * contents, GHashTable *hash);

#endif
