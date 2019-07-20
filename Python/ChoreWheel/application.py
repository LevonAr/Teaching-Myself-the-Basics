from flask import Flask, render_template
from itertools import cycle
from apscheduler.scheduler import Scheduler


app = Flask(__name__)

@app.route("/")
def index():
    people_of_mansion = ["Ried", "Salvador", "Mo", "Madison", "Vaughn", "Mario", "Kat", "Mejan", "Liv", "Gabe", "Frosty","Drake"]

    n=0

    people_of_mansion_looped = cycle(people_of_mansion)
    
    def skip_days(days):
        for i in range(days):
            next(people_of_mansion_looped)

    skip_days(n)

    fridge = []
    trash = []
    living_room = []
    bathroom = [] 

    for i in range(3):
        fridge.append(next(people_of_mansion_looped))

    for i in range(3):
        trash.append(next(people_of_mansion_looped))

    for i in range(3):
        living_room.append(next(people_of_mansion_looped))

    for i in range(3):
        bathroom.append(next(people_of_mansion_looped))

              
    
    return render_template("index.html", fridge = fridge, trash = trash, living_room = living_room, bathroom = bathroom,)
