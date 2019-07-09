from flask import Flask, render_template
from itertools import cycle

pp = Flask(__name__)

@app.route("/")
def index():
    people_of_mansion = ["Ried", "Salvador", "Mo", "Madison", "Vaughn", "Mario", "Kat", "Mejan", "Liv", "Gabe", "Frosty","Drake"]

    n=11

    people_of_mansion_looped = cycle(people_of_mansion)

    return render_template("index.html", peeps = people_of_mansion_looped, n=n)
    
