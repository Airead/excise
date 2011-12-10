gboolean
__client_request_cb (ServerObject *server_object, const gint IN_action_id, const gint IN_input_int, const GArray* IN_input_garray, gint* OUT_output_int, GArray** OUT_output_garray, gint* OUT_result, GError **error)
{
    *OUT_output_garray = g_array_new(FALSE, FALSE, sizeof(guint8));//在client侧没有分配内存，server这里一定要分配
 
    //卸下client侧传递过来的数据
    your_strcut_t ×p_data= (your_strcut_t *)&g_array_index(input_garray,your_strcut_t, 0);
 
    //对卸下的数据进行处理，看你的程序做什么功能了:)
 
    //如果要传回数据到client侧，假设处理过的数据为：your_strcut_t dealed_with_data
    g_array_append_vals(*output_garray, &dealed_with_data, sizeof(your_strcut_t));
 
 
    return TRUE;//一定要返回TRUE,否则client侧收不到数据的；
 
}

