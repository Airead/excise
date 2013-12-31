# coding:utf8

from firefly.server.globalobject import netserviceHandle
import json
from firefly.server.globalobject import GlobalObject
from app.echo_datapack import EchoDataPackProtoc


dataprotocl = EchoDataPackProtoc(11, 11, 12)
GlobalObject().netfactory.setDataProtocl(dataprotocl)


@netserviceHandle
def echo_1(_conn, data):
    print "client data:", data
    return data


@netserviceHandle
def sum_2(_conn, data):
    print data
    a = json.loads(data)  # 解析json
    s = sum(a)
    return json.dumps(s)  # josn格式化数据
