from flask import Flask, render_template

app = Flask(__name__)

@app.context_processor

@app.route("/")
def index():
    return render_template("index.html")
