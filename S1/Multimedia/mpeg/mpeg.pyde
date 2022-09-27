

images = []
current_Image = 0
selectArea = None
selectedArea = None
ImageP = 48
ImageSize = {"width": 1024, "height": 592}


class Select:
    def __init__(self, color, x, y, width=None, height=None):
        self.color = color
        self.cx = x
        self.x = int(round(x/16)*16)
        self.cy = y
        self.y = int(round(y/16)*16)
        if(width == None and height == None):
            self.change(x, y)
        else:
            self.width = int(width)
            self.height = int(height)

    def positiveSelect(self):
        return Select(self.color, self.x+self.width if self.width < 0 else self.x, self.y+self.height if self.height < 0 else self.y, abs(self.width), abs(self.height))

    def copy(self, color=None):
        return Select(self.color if color == None else color, self.x, self.y, self.width, self.height)

    def draw(self):
        stroke(self.color)
        noFill()
        rect(self.x, self.y, self.width, self.height)

    def change(self, x, y):
        self.width = (round((x-self.x)/16)*16)
        self.height = (round((y-self.y)/16)*16)

    def valid(self):
        return abs(self.width) >= 16 and abs(self.height) >= 16


class MPEG:
    def __init__(self, frame1, frame2, selectedArea, padding=1):
        self.frame1 = frame1
        self.frame2 = frame2
        self.selectedArea = selectedArea.positiveSelect()
        self.padding = padding
        self.frame = self.frame1.get(
            self.selectedArea.x-ImageP, self.selectedArea.y, self.selectedArea.width, self.selectedArea.height)
        self.frame.loadPixels()
        self.GlobalSelect = Select("#15c2b6", self.selectedArea.x-(16*self.padding), self.selectedArea.y-(
            16*self.padding), self.selectedArea.width+(2*(16*self.padding)), self.selectedArea.height+(2*(16*self.padding)))
        self.bestMatch()

    def bestMatch(self):
        mse = None
        max = [0, 0]
        for i in range(-16*self.padding, 16*self.padding):
            for j in range(-16*self.padding, 16*self.padding):
                bloc = self.frame2.get(self.selectedArea.x-ImageP + i, self.selectedArea.y +
                                       j, self.selectedArea.width, self.selectedArea.height)
                newMse = self.MSE(bloc)
                if mse == None or mse > newMse:
                    mse = newMse
                    max = [i, j]
        self.MSEArea = Select("#cfcf1b",
                              self.selectedArea.x + max[0], self.selectedArea.y + max[1], self.selectedArea.width, self.selectedArea.height)
        print(mse, max)

    def MSE(self, bloc):
        bloc.loadPixels()
        mse = 0
        for x in range(self.selectedArea.width * self.selectedArea.height):
            mse += (brightness(bloc.pixels[x]) -
                    brightness(self.frame.pixels[x])) ** 2
        return mse/(self.selectedArea.width * self.selectedArea.height)


def setup():
    global images
    textAlign(CENTER)
    size(ImageSize["width"]+ImageP, ImageSize["height"])
    images = [loadImage("frame1.png"), loadImage("frame2.png")]


def draw():
    if(current_Image == 0):
        global selectArea
        background("#b0630b")
        image(images[0], ImageP, 0)
        if(selectArea != None):
            selectArea.draw()
        rotatedMessage("Select wanted Area")


def rotatedMessage(msg):
    pushMatrix()
    rotate(radians(-90))
    text(msg, -300, 20)
    popMatrix()


def keyTyped():
    global selectedArea
    global current_Image
    if current_Image == 1 and key == '\n':
        selectedArea = None
        current_Image = 0


def mousePressed():
    global selectArea
    if(current_Image == 0 and mouseX > ImageP):
        selectArea = Select("#ff0000", mouseX, mouseY)


def mouseDragged():
    global selectArea
    if(current_Image == 0 and mouseX > ImageP and mouseX < (ImageSize["width"]+ImageP) and mouseY < ImageSize["height"] and mouseY > 0 and selectArea):
        selectArea.change(mouseX, mouseY)


def mouseReleased():
    global selectArea
    global current_Image
    if(current_Image == 0 and mouseX > ImageP and selectArea != None and selectArea.valid()):
        global selectedArea
        print(selectArea)
        selectedArea = selectArea.copy("#ff5522")
        sel = MPEG(images[0], images[1], selectArea)
        background("#b0630b")
        image(images[1], ImageP, 0)
        rotatedMessage("Press ENTER to restart the process")
        sel.GlobalSelect.draw()
        sel.MSEArea.draw()
        current_Image = 1

    selectArea = None
