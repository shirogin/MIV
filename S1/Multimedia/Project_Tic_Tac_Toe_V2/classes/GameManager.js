const delay = (ms) => new Promise((res) => setTimeout(res, ms));
class GameManager {
  constructor() {
    console.dir(settings);
    this.setup();
    this.game = new Game("Player 1", "Player 2", this);
    this.screenManager = new ScreenManager(this);
  }
  setup() {
    var slotX = settings.display.table.width / 3,
      slotY = settings.display.table.height / 3;
    settings.shapes = {
      slot: {
        width: slotX,
        height: slotY,
        middleX: slotX / 2,
        middleY: slotY / 2,
      },
      slots: [[], [], []],
      lines: [
        [
          {
            x: settings.display["table"]["x"] + slotX,
            y: settings.display["table"]["y"],
          },
          {
            x: settings.display["table"]["x"] + slotX,
            y:
              settings.display["table"]["y"] +
              settings.display["table"]["height"],
          },
        ],
        [
          {
            x: settings.display["table"]["x"] + slotX * 2,
            y: settings.display["table"]["y"],
          },
          {
            x: settings.display["table"]["x"] + slotX * 2,
            y:
              settings.display["table"]["y"] +
              settings.display["table"]["height"],
          },
        ],
        [
          {
            x: settings.display["table"]["x"],
            y: settings.display["table"]["y"] + slotY,
          },
          {
            x:
              settings.display["table"]["x"] +
              settings.display["table"]["width"],
            y: settings.display["table"]["y"] + slotY,
          },
        ],
        [
          {
            x: settings.display["table"]["x"],
            y: settings.display["table"]["y"] + slotY * 2,
          },
          {
            x:
              settings.display["table"]["x"] +
              settings.display["table"]["width"],
            y: settings.display["table"]["y"] + slotY * 2,
          },
        ],
      ],
    };
    for (let x = 0; x < 3; x++) {
      for (let y = 0; y < 3; y++) {
        settings.shapes.slots[x][y] = [
          x * slotX + slotX / 2 + settings.display["table"]["x"],
          y * slotY + slotY / 2 + settings.display["table"]["y"],
        ];
      }
    }
    let btns = settings.palettes.colorBtns,
      Rect1 = [...btns["groupe1"], ...btns.rect],
      Rect2 = [...btns["groupe2"], ...btns.rect];
    settings.palettes.rects = [];
    settings.palettes.rects[0] = settings.palettes.colors.map((color, i) => {
      let ps = [
        (btns.rect[0] + btns.space) * (i % btns.col),
        (btns.rect[1] + btns.space) * Math.floor(i / btns.col),
        0,
        0,
        0,
      ];
      return Rect1.map((r, i) => r + ps[i]);
    });
    settings.palettes.rects[1] = settings.palettes.colors.map((color, i) => {
      let ps = [
        (btns.rect[0] + btns.space) * (i % btns.col),
        (btns.rect[1] + btns.space) * Math.floor(i / btns.col),
        0,
        0,
        0,
      ];
      return Rect2.map((r, i) => r + ps[i]);
    });
    settings.palettes.rects.groupe1;
    background(...settings.display.background);
    createCanvas(settings.display.width, settings.display.height);
    frameRate(settings.render.FPS);
    textFont(settings.display.font);
    textAlign(CENTER);
  }
  init() {
    this.screenManager.init();
    if (this.screenManager.screen === "GAME") this.game.init();
  }
  clickedCase(Case) {
    switch (Case) {
      case "START1":
        this.game.cp = 0;
        this.screenManager.screen = "GAME";
        return this.init();
      case "START2":
        this.game.cp = 1;
        this.screenManager.screen = "GAME";
        return this.init();
      case "HOME":
        this.screenManager.screen = "MAIN";
        break;
      case "COMPUTERS":
        settings.gamePlay.Computer = settings.gamePlay.AI = true;
        break;
      case "COMPUTERD":
        settings.gamePlay.Computer = !(settings.gamePlay.AI = false);
        break;
      case "PLAYER":
        settings.gamePlay.Computer = false;
        break;
      case "EASY":
      case "NORMAL":
      case "HARD":
      case "VERY HARD":
        settings.gamePlay.Difficulty =
          settings.display.btns.difficulty[Case.toLowerCase()].level;
        break;
      case "SWITCH":
        this.game.players[0].symbole =
          this.game.players[0].symbole === "X" ? "O" : "X";
        this.game.players[1].symbole =
          this.game.players[0].symbole === "X" ? "O" : "X";
        break;
      default:
        break;
    }
    this.screenManager.init();
  }
  clickedColor(cl) {
    let { 1: p, 2: c } = cl.match(/C(\d):(\d+)/);
    this.game.players[p].color = Number(c);
    this.init();
  }
  async gameOver() {
    if (this.game.lastWinner && this.game.lastWinner.player !== "TIE") {
      this.screenManager.drawWinLine();
      this.screenManager.drawDialog(
        this.game.players[this.game.lastWinner.player].name
      );
    } else {
      this.screenManager.drawDialog("TIE");
    }
    await delay(settings.gamePlay.Dialog * 1000);
    this.init();
  }
}
