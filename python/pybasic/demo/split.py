#!/usr/bin/env python
# -*- coding: utf-8 -*-  

def demo_split(str):
    h1_list = str.split(',')
    h2_list = []
    print '========h1_list'
    for l in h1_list:
        print l
        h2_list.append(l.split('|'))

    print '========h2_list'
    for l in h2_list:
        print l, l[1]
    return h2_list


if __name__ == '__main__':
    infos = '01|北京,02|上海,03|天津,04|重庆,05|黑龙江,06|吉林,07|辽宁,08|内蒙古,09|河北,10|山西,11|陕西,12|山东,13|新疆,14|西藏,15|青海,16|甘肃,17|宁夏,18|河南,19|江苏,20|湖北,21|浙江,22|安徽,23|福建,24|江西,25|湖南,26|贵州,27|四川,28|广东,29|云南,30|广西,31|海南,32|香港,33|澳门,34|台湾'
    print "infos:", infos
    demo_split(infos)