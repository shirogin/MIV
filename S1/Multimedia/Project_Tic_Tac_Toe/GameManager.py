from Game import Game
from Settings import Settings


class GameManager:
    def __init__(self):
        self.setup()
        self.settings = Settings()
        self.game = Game(["Player 1", "X"], ["Player 2", "O"], self)

    def setup(self):
        size(self.settings.display["width"], self.settings.display["height"])
        frameRate(self.settings.render["FPS"])
        textMode(SHAPE)

    def onClick(MouseX, MousY):
        pass
