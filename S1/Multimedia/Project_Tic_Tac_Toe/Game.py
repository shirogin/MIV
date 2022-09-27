from threading import Timer
import random


class Player:
    def __init__(self, name, X):
        self.name = name
        self.score = 0
        self.symbole = "X" if X else "O"

    def addScore(self):
        self.score += 1


class Board:
    def __init__(self):
        self.board = [
            ["", "", ""],
            ["", "", ""],
            ["", "", ""]
        ]
        self.available = 9

    def state(self):
        won = False
        for i in range(3):
            if((self.board[0][i] != "") and (self.board[0][i] == self.board[1][i]) and (self.board[0][i] == self.board[2][i])):
                return {
                    "player": self.board[0][i],
                    "elements": "H"+str(i)
                }
        for i in range(3):
            if((self.board[i][0] != "") and (self.board[i][0] == self.board[i][1]) and (self.board[i][0] == self.board[i][2])):
                return {
                    "player": self.board[i][0],
                    "elements": "V"+str(i)
                }
        if((self.board[0][0] != "") and (self.board[0][0] == self.board[1][1]) and (self.board[0][0] == self.board[2][2])):
            return {
                "player": self.board[0][0],
                "elements": "P"
            }
        if((self.board[2][0] != "") and (self.board[2][0] == self.board[1][1]) and (self.board[2][0] == self.board[0][2])):
            return {
                "player": self.board[2][0],
                "elements": "S"
            }
        if(self.available == 0):
            return {
                "player": "TIE"
            }
        else:
            return None

    def setCase(self, i, j, symbole):
        if(self.board[i][j] == ""):
            self.board[i][j] = symbole
            self.available -= 1
            return True
        else:
            return False

    def copy(self):
        board = Board()
        for i in range(3):
            for j in range(3):
                board.board[i][j] = self.board[i][j]
        return board

    def getAvailable(self):
        av = []
        for i in range(3):
            for j in range(3):
                if(self.board[i][j] == ""):
                    av.append([i, j])
        return av


class Game:
    def __init__(self, Player1, Player2, gameManager, X=True):
        self.gameManager = gameManager
        self.players = [Player(Player1[0], X), Player(Player2[0], not X)]
        self.cp = 0
        self.init()
        self.lastWinner = {
            "player": 2,
            "list": []
        }

    def init(self):
        self.won = False
        self.on = True
        self.board = Board()
        self.checkStep()

    def initDraw(self):
        self.init()
        # drawF()

    def minimax(self, board, depth, maxim=True, Init=True):
        state = board.state()
        if(depth == 0 or state != None):
            if state == None or state["player"] == "TIE":
                return 0
            elif state["player"] == self.players[0].symbole:
                return -(depth+1)
            else:
                return depth+1
        avs = board.getAvailable()
        if(maxim):
            maxEval = float('-inf')
            maxElm = []
            for x in avs:
                nBoard = board.copy()
                nBoard.board[x[0]][x[1]] = self.players[1].symbole
                val = self.minimax(nBoard, depth-1, False, False)
                if val > maxEval:
                    maxEval = val
                    maxElm = [[x[0], x[1], val]]
                elif val == maxEval:
                    maxElm.append([x[0], x[1], val])
            if(Init):
                return maxElm
            return maxEval
        else:
            minEval = float('inf')
            for x in avs:
                nBoard = board.copy()
                nBoard.board[x[0]][x[1]] = self.players[0].symbole
                val = self.minimax(nBoard, depth-1, True, False)
                if val < minEval:
                    minEval = val
            return minEval

    def nextStep(self):
        availables = self.board.getAvailable()
        step = random.randint(0, len(availables)-1)
        self.nextMove(availables[step][0], availables[step][1])

    def AIStep(self):
        minimax = self.minimax(self.board, ceil(
            float(self.board.available)/float(self.gameManager.settings["difficulty"])))
        step = random.randint(0, len(minimax)-1)
        self.nextMove(minimax[step][0], minimax[step][1])

    def checkStep(self):
        if(self.on and self.gameManager.settings["computer"] == True and self.cp == 1):
            if(self.gameManager.settings["AI"]):
                self.AIStep()
            else:
                self.nextStep()

    def nextMove(self, i, j):
        if(not self.board.setCase(i, j, self.players[self.cp].symbole)):
            return False
        state = self.board.state()
        if(state != None):
            if(state["player"] == "X" or state["player"] == "O"):
                self.players[self.cp].addScore()
                self.lastWinner = {
                    "player": self.cp,
                    "list": state["elements"]
                }
                self.won = True
            self.on = False
            Timer(5, self.initDraw).start()
        self.cp = (self.cp+1) % 2
        # self.DrawF()
        self.checkStep()
        return True
