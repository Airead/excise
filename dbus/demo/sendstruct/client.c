#include <stdio.h>
#include <glib.h>
//#include <dbus/dbus.h>
#include "datastruct.h"
#include "general_proxy.h"

gboolean proxy_func1 (void)
{
    int api_id = 0;      //这个在不同的proxy_func里面可以有不同的值，主要是区分函数作用
    GArray* in_array = NULL;
    GArray* out_array = NULL; //在这里不用分配内存，放在server侧做内存分配
 
    in_array = g_array_new(FALSE, FALSE, sizeof(guint8));
    if (!in_array)
        return FALSE;
  
    //把你自己的数据封装到in_array中，假设你的数据结构是your_strcut_t
 
    struct datastruct my_own_data;
 
    //fill my_own_data
    my_own_data.i = 123;
    my_own_data.f = 1.23;
    my_own_data.s = "ijimu";
 
    //放到in_array中，这很关键
    g_array_append_vals(in_array, (gconstpointer)&my_own_data, sizeof(struct datastruct));  
 
    //调用general_proxy.h中的dbus接口
    client_request(dbus_proxy, api_id, in_array, &out_array); //通过dbus把数据从到server侧,server侧如何处理，看第四步；
 
    //当sever返回数据后，从out_array中取出来就可以了
    struct datastruct* g_array_data = (struct datastruct*)out_array->data;

    printf("%d, %f, %s\n", g_array_data->i, g_array_data->f, g_array_data->s);

    //free
    if (in_array)
        g_free (in_array);
 
    if (out_array)
        g_free (out_array);
  
} 
