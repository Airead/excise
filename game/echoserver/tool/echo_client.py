#coding:utf8

from socket import AF_INET,SOCK_STREAM,socket
from thread import start_new
import struct,time

from app.echo_datapack import EchoDataPackProtoc

pack_proto = EchoDataPackProtoc(11,11,12)

def sendData(sendstr,commandId):
    '''定义协议头
    '''
    
    return pack_proto.pack(sendstr, commandId)

def resolveRecvdata(data):
    '''解析数据，根据定义的协议头解析服务器返回的数据
    '''
    proto_lenght = pack_proto.getHeadLenght()
    datalenght = pack_proto.unpack(data[:proto_lenght])['lenght']
    message = data[proto_lenght:proto_lenght+datalenght]
    return message

if __name__ == "__main__":
    import json
    HOST='localhost'
    PORT=11009
    ADDR=(HOST , PORT)
    client = socket(AF_INET,SOCK_STREAM)
    client.connect(ADDR)#建立socket连接
    client.sendall(sendData(json.dumps([1,2,3,4,5]),2))#向服务器发送消息
    message = client.recv(1024)#接收服务器返回的消息
    message = resolveRecvdata(message)#解析消息
    print 'server recv:',message
    time.sleep(5)
    client.close()

