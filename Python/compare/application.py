import cs50
import re
from flask import Flask, abort, redirect, render_template, request
from html import escape
from werkzeug.exceptions import default_exceptions, HTTPException
from helpers import lines, sentences, substrings

# Web app
app = Flask(__name__)
