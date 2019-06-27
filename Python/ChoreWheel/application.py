from flask import Flask, render_template

app = Flask(__name__)

@app.context_processor
def override_url_for():

@app.route("/")
def index():
    return render_template("index.html")
