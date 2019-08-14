from flask import Flask
from flask import request
from flask import make_response

app = Flask(__name__)

@app.route('/hello/world', methods=['POST'])
def hello_world():
	print(request.get_data())
	return make_response("[PIZDA]\n", 200)

app.run(host='127.0.0.1', port=80)
