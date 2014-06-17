__author__ = 'airead'



from contextlib import contextmanager
from flask import appcontext_pushed, g, request, request_started
from flask import json, jsonify, Flask


app = Flask(__name__)


@app.route('/users/me')
def users_me():
    print request.args
    print 'g.user', g.user


@contextmanager
def user_set(app, user):
    print 'ready handler'
    def handler(sender, **kwargs):
        print 'run handler'
        print 'request: ', request
        g.user = user
    with request_started.connected_to(handler, app):
        print 'with start'
        yield
        print 'with end'


class User(object):
    def __init__(self, name):
        self.username = name

my_user = User('airead')

#self.client = self.app.test_client()
#
#self._ctx = self.app.test_request_context()
#self._ctx.push()

c = app.test_client()
_ctx = app.test_request_context('?a=1')
_ctx.push()

with user_set(app, my_user):

    print 'user_set start'

    resp = c.get('/users/me')
    print 'user_set end'


