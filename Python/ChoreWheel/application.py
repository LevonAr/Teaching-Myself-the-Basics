from flask import Flask, render_template

app = Flask(__name__)

@app.context_processor
def override_url_for():
    return dict(url_for=dated_url_for)

def dated_url_for(endpoint, **values):

@app.route("/")
def index():
    return render_template("index.html")
