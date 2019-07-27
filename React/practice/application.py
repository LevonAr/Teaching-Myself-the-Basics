import csv
import os
import urllib.request

from flask import Flask, jsonify, render_template, request
from flask.exthook import ExtDeprecationWarning
from warnings import simplefilter
simplefilter("ignore", ExtDeprecationWarning)
from flask_autoindex import AutoIndex
