from contextlib import contextmanager
from flask import appcontext_pushed, g
from flask import json, jsonify, Flask


app = Flask(__name__)


@app.route('/users/me')
def users_me():
    return jsonify(username=g.user.username)


@contextmanager
def user_set(app, user):
    print 'ready handler'
    def handler(sender, **kwargs):
        g.user = user
        print 'run handler'
    with appcontext_pushed.connected_to(handler, app):
        yield


class User(object):
    def __init__(self, name):
        self.username = name

my_user = User('airead')

with user_set(app, my_user):
    with app.test_client() as c:
        resp = c.get('/users/me')
        data = json.loads(resp.data)
        print data

__author__ = 'airead'
