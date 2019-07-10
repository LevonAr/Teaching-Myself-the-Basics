from flask import Flask, render_template
from itertools import cycle

app = Flask(__name__)

@app.route("/")
def index():
    people_of_mansion = ["Ried", "Salvador", "Mo", "Madison", "Vaughn", "Mario", "Kat", "Mejan", "Liv", "Gabe", "Frosty","Drake"]

    n=11

    people_of_mansion_looped = cycle(people_of_mansion)

    def skip_days(n):
        for i in range(n):
            next(people_of_mansion_looped)

    fridge = []
    living_room = []
    bathroom = [] 
    trash = []

    for i in range(4)
        fridge.append(next(people_of_mansion_looped))

              
    
    return render_template("index.html", fridge = fridge )

