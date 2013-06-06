from flask import Flask, request
import bjoern

app = Flask(__name__)

@app.route('/printenv')
def printenv():
    str = []
    print type(request.environ)
    for k, v in sorted(request.environ.iteritems()):
        str.append("<span style='color: red'>%s</span>: %s  " % (k, v))
    res = "<br/>\n".join(str)
    return res

if __name__ == '__main__':
    print "bjoern run ..."
    bjoern.run(app, "0.0.0.0", 8000)
