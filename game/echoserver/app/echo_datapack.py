# coding:utf8
'''
Created on 2013-9-29

@author: Administrator
'''
from firefly.netconnect.datapack import DataPackProtoc, DataPackError
import struct


class EchoDataPackProtoc(DataPackProtoc):

    def __init__(self, HEAD_0=0, HEAD_1=0, HEAD_2=0):
        self.HEAD_0 = HEAD_0
        self.HEAD_1 = HEAD_1
        self.HEAD_2 = HEAD_2

    def getHeadLenght(self):
        """协议头的总的长度
        """
        return 11

    def unpack(self, dpack):
        '''解析数据
        '''
        try:
            ud = struct.unpack('!sss2I', dpack)
        except DataPackError, de:
            return {'result': False, 'command': 0, 'lenght': 0}
        HEAD_0 = ord(ud[0])
        HEAD_1 = ord(ud[1])
        HEAD_2 = ord(ud[2])
        lenght = ud[3] - 4
        command = ud[4]
        if HEAD_0 <> self.HEAD_0 or HEAD_1 <> self.HEAD_1 or\
                HEAD_2 <> self.HEAD_2:
            return {'result': False, 'command': 0, 'lenght': 0}
        return {'result': True, 'command': command, 'lenght': lenght}

    def pack(self, response, command):
        '''打包数据
        '''
        HEAD_0 = chr(self.HEAD_0)
        HEAD_1 = chr(self.HEAD_1)
        HEAD_2 = chr(self.HEAD_2)
        lenght = response.__len__() + 4
        commandID = command
        data = struct.pack('!sss2I', HEAD_0, HEAD_1, HEAD_2, lenght, commandID)
        data = data + response
        return data
