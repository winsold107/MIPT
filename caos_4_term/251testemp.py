from flask import Flask
from flask import request

app = Flask(__name__)

@app.route('/hello/world')
def hello_world():
    print(request.data)
