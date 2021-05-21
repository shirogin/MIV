from Classes import Map, Profound
import json

file = open("World.json", "r")
World = json.load(file)

h = len(World)
w = len(World[0])


def setup():
    global profound
    size(20*w, 20*h)
    frameRate(5)
    profound = Profound(Map(World))
    found = profound.setup()
    if(found[0]):
        noLoop()
        print(frameCount)


def draw():
    global profound
    found = profound.draw()
    if found[0]:
        noLoop()
        print(frameCount)
