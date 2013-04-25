#!/usr/bin/env python
# -*- coding: utf-8 -*-  

import json

def json_print(infos):
    print "infos:", infos
    j = json.loads(infos)
    print "json.loads(infos):", j
    str = json.dumps(j, indent = 4)
    print str

if __name__ == '__main__':
    infos = '{"weatherinfo":{"city":"东莞","cityid":"101281601","temp":"24","WD":"南风","WS":"1级","SD":"91%","WSE":"1","time":"07:00","isRadar":"0","Radar":""}}'
    json_print(infos)