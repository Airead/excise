#!/usr/bin/env python
# -*- coding: utf-8 -*-  

# get city id from weather.com.cn

# 1. 通过 http://m.weather.com.cn/data5/city.xml 获取省份列表；
# result: 01|北京,02|上海,03|天津,04|重庆,05|黑龙江,06|吉林,07|辽宁,08|内蒙古,09|河北,10|山西,11|陕西,12|山东,13|新疆,14|西藏,15|青海,16|甘肃,17|宁夏,18|河南,19|江苏,20|湖北,21|浙江,22|安徽,23|福建,24|江西,25|湖南,26|贵州,27|四川,28|广东,29|云南,30|广西,31|海南,32|香港,33|澳门,34|台湾

# 2. 通过 http://m.weather.com.cn/data5/city28.xml 获取该省份的城市列表，其中28为广东省代号，1中所返回的；
# result: 2801|广州,2802|韶关,2803|惠州,2804|梅州,2805|汕头,2806|深圳,2807|珠海,2808|佛山,2809|肇庆,2810|湛江,2811|江门,2812|河源,2813|清远,2814|云浮,2815|潮州,2816|东莞,2817|中山,2818|阳江,2819|揭阳,2820|茂名,2821|汕尾

# 3. 通过 http://m.weather.com.cn/data5/city2816.xml 获取该城市的区列表，其中2816为东莞市代号，2中所返回的；
# result: 281601|东莞

# 4. 通过 http://m.weather.com.cn/data5/city281601.xml 获取最后的城市码，其中281601为3中返回；
# result: 281601|101281601

# 该api获取天气的接口如下：
# http://www.weather.com.cn/data/sk/101281601.html 
# http://www.weather.com.cn/data/cityinfo/101281601.html 
# http://m.weather.com.cn/data/101281601.html  


# http://www.weather.com.cn/data/sk/101281601.html 
# {
#     "weatherinfo": {
#         "city": "哈尔滨", // 城市中文名
#         "city_en": "haerbin", // 城市英文名
#         "date_y": "2012年8月18日", // 发布日期
#         "date": "", // ?
#         "week": "星期六", // 周信息
#         "fchh": "18", // ？
#         "cityid": "101050101", // 城市ID
#         "temp1": "18℃~26℃", // 今日气温
#         "temp2": "17℃~29℃", // 明日气温
#         "temp3": "18℃~23℃", // 第三日气温
#         "temp4": "13℃~24℃", // 第四日气温
#         "temp5": "15℃~31℃", // 第五日气温
#         "temp6": "14℃~32℃", // 第六日气温
#         "tempF1": "64.4℉~78.8℉", // 今日气温（华氏）
#         "tempF2": "62.6℉~84.2℉", // 明日气温（华氏）
#         "tempF3": "64.4℉~73.4℉", // 第三日气温（华氏）
#         "tempF4": "55.4℉~75.2℉", // 第四日气温（华氏）
#         "tempF5": "59℉~87.8℉", // 第五日气温（华氏）
#         "tempF6": "57.2℉~89.6℉", // 第六日气温（华氏）
#         "weather1": "多云", // 今日天气
#         "weather2": "晴转多云", // 明日天气
#         "weather3": "雷阵雨转小雨", // 第三日天气
#         "weather4": "多云", // 第四日天气
#         "weather5": "晴", // 第五日天气
#         "weather6": "晴", // 第六日天气
#         "img1": "1", // ? 可能是天气图标编号
#         "img2": "99", // ? 可能是天气图标编号
#         "img3": "0", // ? 可能是天气图标编号
#         "img4": "1", // ? 可能是天气图标编号
#         "img5": "4", // ? 可能是天气图标编号
#         "img6": "7", // ? 可能是天气图标编号
#         "img7": "1", // ? 可能是天气图标编号
#         "img8": "99", // ? 可能是天气图标编号
#         "img9": "0", // ? 可能是天气图标编号
#         "img10": "99", // ? 可能是天气图标编号
#         "img11": "0", // ? 可能是天气图标编号
#         "img12": "99", // ? 可能是天气图标编号
#         "img_single": "1", // ? 可能是天气图标编号
#         "img_title1": "多云", // ? 可能是天气图标对应的 title
#         "img_title2": "多云", // ? 可能是天气图标对应的 title
#         "img_title3": "晴", // ? 可能是天气图标对应的 title
#         "img_title4": "多云", // ? 可能是天气图标对应的 title
#         "img_title5": "雷阵雨", // ? 可能是天气图标对应的 title
#         "img_title6": "小雨", // ? 可能是天气图标对应的 title
#         "img_title7": "多云", // ? 可能是天气图标对应的 title
#         "img_title8": "多云", // ? 可能是天气图标对应的 title
#         "img_title9": "晴", // ? 可能是天气图标对应的 title
#         "img_title10": "晴", // ? 可能是天气图标对应的 title
#         "img_title11": "晴", // ? 可能是天气图标对应的 title
#         "img_title12": "晴", // ? 可能是天气图标对应的 title
#         "img_title_single": "多云", // ? 可能是天气图标对应的 title
#         "wind1": "西南风小于3级转西风3-4级", // 今日风向风力信息
#         "wind2": "西风小于3级转西南风3-4级", // 明日风向风力信息
#         "wind3": "西南风小于3级转3-4级", // 第三日风向风力信息
#         "wind4": "西南风小于3级转3-4级", // 第四日风向风力信息
#         "wind5": "西南风小于3级转3-4级", // 第五日风向风力信息
#         "wind6": "西南风小于3级转3-4级", // 第六日风向风力信息
#         "fx1": "西南风", // ? 
#         "fx2": "西风", // ? 
#         "fl1": "小于3级转3-4级", // 今日风力信息
#         "fl2": "小于3级转3-4级", // 明日风力信息
#         "fl3": "小于3级转3-4级", // 第三日风力信息
#         "fl4": "小于3级转3-4级", // 第四日风力信息
#         "fl5": "小于3级转3-4级", // 第五日风力信息
#         "fl6": "小于3级转3-4级", // 第六日风力信息
#         "index": "热",
#         "index_d": "天气较热，建议着短裙、短裤、短套装、T恤等夏季服装。年老体弱者宜着长袖衬衫和单裤。",
#         "index48": "炎热",
#         "index48_d": "天气炎热，建议着短衫、短裙、短裤、薄型T恤衫、敞领短袖棉衫等清凉夏季服装。",
#         "index_uv": "中等", // 紫外线信息
#         "index48_uv": "弱", // ? 48 小时紫外线信息
#         "index_xc": "较适宜", // ? 
#         "index_tr": "适宜", // ? 旅游指数
#         "index_co": "舒适", // ? 舒适指数
#         "st1": "25",
#         "st2": "17",
#         "st3": "28",
#         "st4": "19",
#         "st5": "18",
#         "st6": "16",
#         "index_cl": "较适宜", // ? 晨练指数
#         "index_ls": "适宜", // ? 晾晒指数
#         "index_ag": "极易发"
#     }
# }


# http://www.weather.com.cn/data/cityinfo/101281601.html 
# {
#     "weatherinfo": {
#         "city": "北京", // 城市中文名
#         "cityid": "101010100", // 城市 ID
#         "temp": "24", // 温度
#         "WD": "西南风", // 风向
#         "WS": "1级", // 风力
#         "SD": "92%", // 湿度
#         "WSE": "1", // ? 
#         "time": "19:15", // ? 发布时间
#         "isRadar": "1", // ? 
#         "Radar": "JC_RADAR_AZ9010_JB" // ?雷达编号
#     }
# }

# http://m.weather.com.cn/data/101281601.html  
# {
#     "weatherinfo": {
#         "city": "北京", // 城市中文名
#         "cityid": "101010100", // 城市 ID
#         "temp1": "22℃", // ? 
#         "temp2": "31℃", // ? 
#         "weather": "阴转晴", // 天气
#         "img1": "n2.gif", // ? 天气图标编号
#         "img2": "d0.gif", // ? 天气图标编号
#         "ptime": "18:00" // 发布时间
#     }
# }

import urllib
import time
import sys

def getHtml(url):
    if not url:
        return 'no url'

    ret = "again"
    while ret == "again":
        try:
            page = urllib.urlopen(url)
            ret = "ok"
        except Exception as e:
            print e
            time.sleep(15)
            ret = "again"

    html = page.read()
    page.close()
    return html

def getList(str):
    """
    change "01|北京,02|上海,03|天津,04|重庆" to [['01', 北京], ['02', '上海'], ...]
    """
    list = []
    tmplist = str.split(',')
    for l in tmplist:
        list.append(l.split('|'))
    return list

def getCityUrl(str):
    url = 'http://m.weather.com.cn/data5/city%s.xml' % str
    return url

def makeList(url):
    html = getHtml(url)
    list = getList(html)
    return list

def getProvinceList():
    plist = makeList(getCityUrl(''))
    file = open("provinceid.txt", "w")
    print "========provinces list:"
    for l in plist:
        msg = "%s %s\n" % (l[0], l[1])
        print msg
        file.write(msg)
    file.close()

    return plist

def getCityList():
    plist = getProvinceList()
    clist = []
    for l in plist:
        print getCityUrl(l[0])
        tmplist = makeList(getCityUrl(l[0]))
        for tl in tmplist:
            print 'append', tl, tl[1]
            clist.append(tl)

    file = open("cityid.txt", "w")
    for l in clist:
        msg = "%s %s\n" % (l[0], l[1])
        print msg
        file.write(msg)
    file.close()

    return clist

def getTownList(clist):
    if clist == []:
        clist = getCityList()
    tlist = []
    for l in clist:
        print getCityUrl(l[0])
        tmplist = makeList(getCityUrl(l[0]))
        for tl in tmplist:
            print 'append', tl, tl[1]
            tlist.append(tl)

    file = open("townid.txt", "w")
    for l in tlist:
        msg = "%s %s\n" % (l[0], l[1])
        print msg
        file.write(msg)
    file.close()

    return tlist

def getFinalList(tlist):
    if tlist == []:
        tlist = getTownList([])
        
    finallist = []
    for l in tlist:
        print getCityUrl(l[0])
        tmplist = makeList(getCityUrl(l[0]))
        for tl in tmplist:
            print 'append', tl, tl[1], l[1]
            finallist.append([tl[1], l[1]])

    file = open('cityinfos.txt', 'w')
    for l in finallist:
        msg = "%s %s\n" % (l[0], l[1])
        print msg
        file.write(msg)
    file.close()

def runFromCity(filename):
    input = open(filename, "r")
    contents = input.readlines()
    input.close()

    tlist = []
    for line in contents:
        l = line.split()
        tlist.append(l)
    print tlist
    getTownList(tlist)

def runFromTown(filename):
    input = open(filename, "r")
    contents = input.readlines()
    input.close()

    tlist = []
    for line in contents:
        l = line.split()
        tlist.append(l)
    print tlist
    getFinalList(tlist)

if __name__ == '__main__':
    if len(sys.argv) > 1:
        if sys.argv[1] == "town":
            runFromTown("townid.txt")
            sys.exit(0)
        if sys.argv[1] == "city":
            runFromCity("cityid.txt")
            sys.exit(0)
    getFinalList([])