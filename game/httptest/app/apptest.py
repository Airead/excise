# coding:utf8

from firefly.server.globalobject import webserviceHandle
from twisted.web import resource


@webserviceHandle('he')
class hello(resource.Resource):

    '''stop service'''

    def render(self, request):
        '''
        '''
        return "hello"
