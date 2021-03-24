from Classes import Map, Uniform
import json

file = open("World.json", "r")
World = json.load(file)

h = len(World)
w = len(World[0])


def setup():
    global uniform
    size(20*w, 20*h)
    frameRate(5)
    uniform = Uniform(Map(World))
    found = uniform.setup()
    if(found[0]):
        noLoop()
        print(frameCount)


def draw():
    found = uniform.draw()
    if found[0]:
        noLoop()
        print(frameCount)
