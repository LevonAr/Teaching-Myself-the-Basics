import cs50
import re
from flask import Flask, abort, redirect, render_template, request
from html import escape
from werkzeug.exceptions import default_exceptions, HTTPException
from helpers import lines, sentences, substrings

# Web app
app = Flask(__name__)

@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
def index():
    """Handle requests for / via GET (and POST)"""
    return render_template("index.html")


@app.route("/compare", methods=["POST"])
def compare():
    """Handle requests for /compare via POST"""

    # Read files
    if not request.files["file1"] or not request.files["file2"]:
        abort(400, "missing file")
    try:
        file1 = request.files["file1"].read().decode("utf-8")
        file2 = request.files["file2"].read().decode("utf-8")
    except Exception:
        abort(400, "invalid file")
    
    
    #compare files
    if not request.form.get("algorithm"):
        abort(400, "missing algorithm")
    elif request.form.get("algorithm") == "lines":
        regexes = [f"^{re.escape(match)}$" for match in lines(file1, file2)]
    elif request.form.get("algorithm") == "sentences":
        regexes = [re.escape(match) for match in sentences(file1, file2)]
    elif request.form.get("algorithm") == "substrings":        
        if not request.form.get("length"):
            abort(400, "missing length")
        elif not int(request.form.get("length")) > 0:
            abort(400, "invalid length")
        regexes = [re.escape(match) for match in substrings(
            file1, file2, int(request.form.get("length")))]
    else:
        abort(400, "invalid algorithm")
    # Highlight files
    highlights1 = highlight(file1, regexes)
    highlights2 = highlight(file2, regexes)
    
    # Output comparison
    return render_template("compare.html", file1=highlights1, file2=highlights2)

def highlight(s, regexes):
    """Highlight all instances of regexes in s."""
    
    # Get intervals for which strings match
    intervals = []
    for regex in regexes:    
        if not regex:
            continue
        matches = re.finditer(regex, s, re.MULTILINE)
        for match in matches:
            intervals.append((match.start(), match.end()))
    intervals.sort(key=lambda x: x[0])
    
    # Combine intervals to get highlighted areas
    highlights = []
    for interval in intervals:
        if not highlights:
            highlights.append(interval)
            continue
        last = highlights[-1]
