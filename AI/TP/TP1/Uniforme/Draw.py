
def drawTable(world):
    for row in range(len(world)):
        for column in range(len(world[row])):
            if(world[row][column].Type == 0):
                f = [150, 150, 150]
            elif world[row][column].Type == 1:
                f = [0, 60, 255]
            elif world[row][column].Type == 2:
                f = [255, 0, 0]
            elif world[row][column].Type == 3:
                f = [0, 150, 60]
            else:
                f = [10, 10, 20]
            fill(f[0], f[1], f[2])
            rect(column*20, row*20, 20, 20)
