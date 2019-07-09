from flask import Flask, render_template
from itertools import cycle

pp = Flask(__name__)

@app.route("/")
def index():
    
