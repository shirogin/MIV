from Draw import drawTable
import math


class Map:
    def __init__(self, world):
        i = 0
        j = 0
        self.h = len(world)
        self.w = len(world[0])
        self.init = None
        self.world = world
        self.Noeds = [[0 for x in range(self.w)] for y in range(self.h)]
        for i in range(self.h):
            for j in range(self.w):
                self.Noeds[i][j] = Noed(world[i][j], i, j)
                if(world[i][j] == 2):
                    self.init = self.Noeds[i][j]
                if(world[i][j] == 3):
                    self.objective = self.Noeds[i][j]
        self.setTree()

    def adj(self, i, j):
        myList = []
        if(((i + 1) < len(self.Noeds))):
            myList.append(self.Noeds[i+1][j])
        if((j+1) < len(self.Noeds[0])):
            myList.append(self.Noeds[i][j+1])
        if(((i - 1) >= 0)):
            myList.append(self.Noeds[i-1][j])
        if(((j - 1) >= 0)):
            myList.append(self.Noeds[i][j-1])
        return myList

    def setTree(self):
        for i in range(self.h):
            for j in range(self.w):
                self.Noeds[i][j].children = self.adj(i, j)


class Noed:
    def __init__(self, Type, i, j, parent=None, children=[]):
        self.Type = Type
        self.i = i
        self.j = j
        self.parent = None
        self.children = []

    def Coup(self, noed):
        return math.sqrt(((self.i-noed.i)**2)+((self.j-noed.j)**2))


class Informe:
    def __init__(self, map):
        self.noeds = map.Noeds
        self.init = map.init
        self.objective = map.objective
        self.finished = [False, None]

    def setup(self):
        if(self.init == self.objective):
            self.finished = [True, self.init]
        else:
            self.ouvert = [self.init]
            self.ferme = []
        drawTable(self.noeds)
        return self.finished


class Largeur(Informe):
    def draw(self):
        if (not self.finished[0]) and len(self.ouvert) > 0:
            current = self.ouvert.pop(0)
            for son in current.children:
                if(son == self.objective):
                    self.finished = [True, son]
                elif(son.Type == 0) and (son not in self.ferme):
                    son.Type = 5
                    self.ouvert.append(son)
            self.ferme.append(current)
            drawTable(self.noeds)
            return self.finished
        else:
            return [True, None] if self.finished[1] == None else self.finished


class Profound(Informe):
    def setup(self):
        if(self.init == self.objective):
            self.finished = [True, self.init]
        else:
            self.ouvert = []
            for elm in reversed(self.init.children):
                if elm.Type != 1:
                    self.ouvert.insert(0, elm)
            self.ferme = [self.init]
        drawTable(self.noeds)
        return self.finished

    def draw(self):
        if (not self.finished[0]) and len(self.ouvert) > 0:
            current = self.ouvert.pop(0)
            if(current == self.objective):
                self.finished = [True, current]
            elif len(current.children) > 0:
                for elm in reversed(current.children):
                    if elm.Type != 1 and (elm not in self.ferme) and (elm not in self.ouvert):
                        self.ouvert.insert(0, elm)
                current.Type = 5
            self.ferme.append(current)
            drawTable(self.noeds)
            return self.finished
        else:
            return [True, None] if self.finished[1] == None else self.finished


class Uniform(Informe):
    def draw(self):
        pass
