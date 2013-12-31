__author__ = 'airead'

import flask
import json
from flask import request

app = flask.Flask(__name__)


@app.route('/')
def index():
    return 'server ok!'


@app.route('/post_dump', methods=['POST'])
def post_dump():
    post_data = request.form
    json_str = json.dumps(post_data, indent=4)

    print json_str
    return json_str


@app.route('/sdkcom/auth/getToken.lg', methods=['POST'])
def get_token():
    return post_dump()


def main():
    host = '127.0.0.1'
    port = 5000

    print 'listening on %s:%s' % (host, port)
    app.run(host, port, debug=True)


if __name__ == '__main__':
    main()