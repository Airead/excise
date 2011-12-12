#ifndef SMS_FEATURES_H
#define SMS_FEATURES_H

#include <glib-object.h>

GHashTable *sms_create_features(const char *alphabet, int csm_num, int csm_seq);

GType sms_get_features_type(void);
void sms_release_features(GHashTable *features);
void sms_show_features(GHashTable *features);

#endif
