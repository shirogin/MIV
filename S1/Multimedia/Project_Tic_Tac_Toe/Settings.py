import json


class Settings:
    def __init__(self):
        file = open("Settings.json", "r")
        self.settings = json.load(file)
        print(self.settings)
        self.display = self.settings["display"]
        self.render = self.settings["render"]
        self.gamePlay = self.settings["gamePlay"]
        slotX = self.display["table"]["width"]/3
        slotY = self.display["table"]["height"]/3
        self.shapes = {
            "slot": {
                "width": slotX,
                "height": slotY,
                "middleX": slotX/2,
                "middleY": slotY/2
            },
            "slots": [[], [], []],
            "lines": [
                [
                    {"x": self.display["table"]["x"]+slotX,
                     "y": self.display["table"]["y"]},
                    {"x": self.display["table"]["x"]+slotX,
                     "y": self.display["table"]["y"]+self.display["table"]["height"]}],
                [
                    {"x": self.display["table"]["x"]+(slotX*2),
                     "y": self.display["table"]["y"]},
                    {"x": self.display["table"]["x"]+(slotX*2),
                        "y": self.display["table"]["y"]+self.display["table"]["height"]}],
                [
                    {"x": self.display["table"]["x"],
                     "y": self.display["table"]["y"]+slotY},
                    {"x": self.display["table"]["x"] + self.display["table"]["width"],
                        "y": self.display["table"]["y"] + slotY}],
                [
                    {"x": self.display["table"]["x"],
                     "y": self.display["table"]["y"] + (slotY * 2)},
                    {"x": self.display["table"]["x"] + self.display["table"]["width"],
                        "y": self.display["table"]["y"] + (slotY*2)}],
            ]
        }
        for x in range(3):
            for y in range(3):
                self.shapes["slots"][x].append([(x*slotX) + slotX/2 + self.display["table"]["x"],
                                                (y*slotY) + slotY/2 + self.display["table"]["y"]])
