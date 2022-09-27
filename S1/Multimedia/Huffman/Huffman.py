
global raduis
paddingY = 30
paddingX = 10
raduis = 10


class Node:
    def __init__(self, car, number, left=None, right=None):
        self.car = car
        self.num = number
        self.left = left
        self.right = right
        self.code = ''

    def isLeaf(self):
        return (self.left is None) and (self.right is None)

    def __lt__(self, other):
        return self.num < other.num

    def printNodes(self):
        if(self.left):
            self.left.printNodes()
        if(self.right):
            self.right.printNodes()
        if(self.isLeaf()):
            print(self.car+" -> "+self.code +
                  " [ "+str(self.x)+" , "+str(self.y)+" ]")

    def getCode(self, car, val=''):
        newVal = val + str(self.code)
        code = None
        if(self.left):
            code = self.left.getCode(car, newVal)
        if(code is None and self.right):
            code = self.right.getCode(car, newVal)
        if(code is None and self.isLeaf() and self.car == car):
            code = newVal
        return code

    def draw(self):
        x = (width*self.x)+paddingX
        y = (raduis*2*self.y)+paddingY
        print(self.x, self.y, self.num)
        t = (str(self.car)+"("+str(self.num)+")" if(self.isLeaf()) else str(self.num))
        if(self.left):
            line(x, y, (width*self.left.x)+paddingX,
                 (raduis*2*self.left.y)+paddingY)
        if(self.right):
            line(x, y, (width*self.right.x)+paddingX,
                 (raduis*2*self.right.y)+paddingY)
        fill(255)
        circle(x, y, raduis*2)
        fill(0)
        textSize(raduis*0.8)
        text(t, x, y)

    def position(self, x, y):
        self.x = x
        self.y = y

    def percentOfLeaves(self):
        if(self.left):
            x = self.left.numOfLeaves()/self.numOfLeaves()
            if(x < 0.5):
                return x
            else:
                return 1-x
        else:
            return 0.5

    def numOfLeaves(self):
        if(self.isLeaf()):
            return 1.0
        num = 0.0
        if(self.left):
            num += self.left.numOfLeaves()
        if(self.right):
            num += self.right.numOfLeaves()
        return num

    def assignValue(self, val=''):
        newVal = val + str(self.code)
        if(self.left):
            self.left.assignValue(newVal)
        if(self.right):
            self.right.assignValue(newVal)
        if(self.isLeaf()):
            self.code = newVal


class Huffman:
    def __init__(self, text):
        self.text = text
        self.occurrences()
        self.TreeHuffman()

    def assignValues(self, head,  placeA, placeB, level=0):
        place = (placeA+placeB) * 0.5
        head.position(place, level)
        level += 1
        if(head.left):
            self.assignValues(head.left, placeA, place, level)
        if(head.right):
            self.assignValues(head.right, place, placeB, level)

    def occurrences(self):
        l = list(set([self.text[i] for i in range(len(self.text))]))
        l.sort()
        self.nodes = [Node(i, self.text.count(i)) for i in l]

    def TreeHuffman(self):
        nodes = self.nodes
        while len(nodes) > 1:
            nodes = sorted(nodes, key=lambda x: x.num)
            left = nodes.pop(0)
            left.code = str(0)
            right = nodes.pop(0)
            right.code = str(1)
            newNode = Node(left.car + right.car, left.num + right.num)
            newNode.left = left
            newNode.right = right
            nodes.append(newNode)
        self.head = nodes[0]
        self.dictionary = {a.car: self.head.getCode(a.car) for a in self.nodes}
        self.assignValues(self.head, 0.0, 1.0)

    def printDict(self):
        for x in self.dictionary:
            print(x+" -> "+self.dictionary[x])

    def encode(self):
        return "".join([self.dictionary[self.text[i]] for i in range(len(self.text))])


def CalculateRatio(width, elm):
    global raduis
    raduis = (width/((elm+1)*4))
