import Huffman


def setup():
    huffman = Huffman.Huffman("Moon light")
    size(1200, 600)
    Huffman.CalculateRatio(1200, len(huffman.dictionary))
    print("encode: ", huffman.encode())
    huffman.printDict()
    global nodes
    nodes = [huffman.head]
    textAlign(CENTER, CENTER)
    frameRate(3)


def draw():
    if(len(nodes) > 0):
        head = nodes.pop(0)
        head.draw()
        if(head.left):
            nodes.append(head.left)
        if(head.right):
            nodes.append(head.right)
