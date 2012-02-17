
#ifndef ___common_marshal_MARSHAL_H__
#define ___common_marshal_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

/* VOID:STRING,BOXED (common_marshaler.list:1) */
extern void _common_marshal_VOID__STRING_BOXED (GClosure     *closure,
                                                GValue       *return_value,
                                                guint         n_param_values,
                                                const GValue *param_values,
                                                gpointer      invocation_hint,
                                                gpointer      marshal_data);

G_END_DECLS

#endif /* ___common_marshal_MARSHAL_H__ */

