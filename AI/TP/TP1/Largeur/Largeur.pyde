from Classes import Map, Largeur
import json
file = open("World.json", "r")
World = json.load(file)

h = len(World)
w = len(World[0])


def setup():
    global largeur
    size(20*w, 20*h)
    frameRate(5)
    largeur = Largeur(Map(World))
    found = largeur.setup()
    if(found[0]):
        noLoop()
        print(frameCount)


def draw():
    found = largeur.draw()
    if found[0]:
        noLoop()
        print(frameCount)
