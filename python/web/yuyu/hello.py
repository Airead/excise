import flask

__author__ = 'airead'

app = flask.Flask('fff')

@app.route('/')
def index():
    return '''
    <h1 style="color: red;">this is index</h1>
    <button>button</button>
    '''

@app.route('/name')
def name():
    return 'this is name'

app.run(host='10.0.1.137', port=8888)