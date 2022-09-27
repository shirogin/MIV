class ScreenManager {
    screen = "MAIN"
    constructor(gameManager) {
        this.gameManager = gameManager;
        this.init();
    }

    init() {
        this.drawBackground()
        if (this.screen === "MAIN") {
            this.drawButton({...settings.display.btns.start1,message:"⨂ Start 1 ⨂"})
            this.drawButton({...settings.display.btns.start2,message:"⨂ Start 2 ⨂"})
            this.drawButton({...settings.display.btns.switch,message:this.gameManager.game.players[0].symbole==="X"?"X | 0":"0 | X",selected:true})
            this.drawButton({
                ...settings.display.btns.selectPlayer.player,
                message:"Second Player",
                selected:!settings.gamePlay.Computer
            })
            this.drawButton({
                ...settings.display.btns.selectPlayer.computerD,
                message:"RANDM Computer",
                selected:settings.gamePlay.Computer && !settings.gamePlay.AI
            })
            this.drawButton({
                ...settings.display.btns.selectPlayer.computerS,
                message:"Smart Computer",
                selected:settings.gamePlay.Computer && settings.gamePlay.AI
            })
            this.drawColorButtons();
            this.drawColorButtons(1);
            if (settings.gamePlay.Computer && settings.gamePlay.AI) {
                for (const dif in settings.display.btns.difficulty) {
                    this.drawButton({...settings.display.btns.difficulty[dif],message:dif.toUpperCase(),selected:settings.display.btns.difficulty[dif].level===settings.gamePlay.Difficulty})
                }
            }
            return;
        }
        this.drawButton({
            ...settings.display.btns.back,message:"⨂ HOME ⨂",selected:true
        })
        this.drawBoard()
        if (this.gameManager.game) {
            this.drawPlayerScore(0)
            this.drawPlayerScore(1)
        }
    }
    drawPlayerScore(player) {
        if (this.gameManager.game.lastWinner && this.gameManager.game.lastWinner.player === player) {
            fill(...settings.display.players[player].highlighted)
            stroke(...settings.display.players[player].highlighted)
        }
        else {
            fill(...settings.display.players[player].color)
            stroke(...settings.display.players[player].color)
        }
        strokeWeight(settings.display.players[player].name.stroke)
        textSize(settings.display.players[player].name.size)
        text(this.gameManager.game.players[player].name, settings.display.players[player].name.x, settings.display.players[player].name.y)
        strokeWeight(settings.display.players[player].score.stroke)
        textSize(settings.display.players[player].score.size)
        text(this.gameManager.game.players[player].score, settings.display.players[player].score.x, settings.display.players[player].score.y)
    }
    drawBackground() {
        background(...settings.display.background)
        this.drawTitle()
    }
    drawTitle() {
        noStroke()
        fill(...settings.display.title.color)
        textSize(100)
        text("TIC TAC TOE", settings.display.title.x, settings.display.title.y)
    }
    drawDialog(message) {
        if(message==="TIE")stroke(settings.display.dialog.color)
        else stroke(...settings.palettes.colors[this.gameManager.game.players[this.gameManager.game.cp].color]);
        fill(settings.display.dialog.background)
        rect(...settings.display.dialog.rect)
        fill(settings.display.dialog.color)
        text(message, ...settings.display.dialog.message)
    }
    drawButton(button) {
        textSize(settings.display.btns.size)
        stroke(...settings.display.btns.stroke)
        strokeWeight(button.selected ? settings.display.btns.strokeWeight : 0)
        noFill()
        rect(...button.rect)
        strokeWeight(1)
        fill(...(button.color?button.color:settings.display.btns.color))
        text(button.message.toUpperCase(), ...button.text)
    }
    drawColorButtons(g=0) {
        let palettes=settings.palettes;
        palettes.rects[g].forEach((rect,i)=>{
            this.drawColorButton({
                rect,
                selected:this.gameManager.game.players[g].color===i,
                color:palettes.colors[i]
            })
        })
    }
    drawColorButton(button) {
        stroke(...settings.display.btns.stroke)
        strokeWeight(button.selected ? settings.display.btns.strokeWeight : 0)
        fill(...button.color)
        rect(...button.rect)
    }
    getBackBtn(){
        if(this.getBtn(settings.display.btns.back)) return "HOME";
    }
    getOneBtn(){
        let btns=settings.display.btns
        if(this.getBtn(btns.start1)) return "START1";
        if(this.getBtn(btns.start2)) return "START2";
        if(this.getBtn(btns.switch)) return "SWITCH";
        for (const dif in btns.selectPlayer) {
            if(this.getBtn(btns.selectPlayer[dif])) return dif.toUpperCase();    
        }
        for (const dif in btns.difficulty) {
            if(this.getBtn(btns.difficulty[dif])) return dif.toUpperCase();    
        }
        return null;
    }
    getBtn(btn){
        let [x, y, width, height] = btn.rect
        if ((mouseX > x) && (mouseX < (x + width)) && (mouseY > y) && (mouseY < (y + height))) return true;
        return false;
    }
    getColor(p=0){
        for (const rect in settings.palettes.rects[p]) {
            if(this.getBtn({rect:settings.palettes.rects[p][rect]})) return "C"+p+":"+rect;
        }
        return false
    }
    drawChoice() {
        textSize(settings.display.twoPlayer.size)
        stroke(...settings.display.twoPlayer.color)
        strokeWeight(1)
        fill(...settings.display.twoPlayer.color)
        text(settings.gamePlay.Computer ? "2 Players" : "Computer", ...settings.display.twoPlayer.text)
    }
    drawDifficulty() {
        textSize(settings.display.difficulty.size)
        stroke(...settings.display.difficulty.color)
        strokeWeight(1)
        fill(...settings.display.difficulty.color)
        text(["Very Hard", "Hard", "Normal", "Easy"][settings.gamePlay.Difficulty - 1], ...settings.display.difficulty.text)
    }
    drawWinLine() {
        let l = this.gameManager.game.lastWinner.list,
            game = this.gameManager.game,
            { middleX: slotXP, middleY: slotYP } = settings.shapes.slot
        strokeWeight(settings.display.WinStroke)
        stroke(...settings.palettes.colors[this.gameManager.game.players[this.gameManager.game.cp].color]);
        if (l == "P")
            return line(settings.shapes.slots[0][0][0] - slotXP, settings.shapes.slots[0][0][1] - slotYP,
                settings.shapes.slots[2][2][0] + slotXP, settings.shapes.slots[2][2][1] + slotYP);
        if (l == "S")
            return line(settings.shapes.slots[0][2][0] - slotXP, settings.shapes.slots[0][2][1] + slotYP,
                settings.shapes.slots[2][0][0] + slotXP, settings.shapes.slots[2][0][1] - slotYP);
        if (l[0] == "V")
            return line(settings.shapes.slots[int(l[1])][0][0], settings.shapes.slots[int(l[1])][0][1] - slotYP,
                settings.shapes.slots[int(l[1])][2][0], settings.shapes.slots[int(l[1])][2][1] + slotYP)
        if (l[0] == "H")
            return line(settings.shapes.slots[0][int(l[1])][0] - slotXP, settings.shapes.slots[0][int(l[1])][1],
                settings.shapes.slots[2][int(l[1])][0] + slotXP, settings.shapes.slots[2][int(l[1])][1]);
    }
    drawBoard() {
        noFill()
        strokeJoin(ROUND)
        strokeWeight(settings.display.table.stroke)
        stroke(...settings.display.table.color)
        if (settings.display.table.border) rect(settings.display.table.x, settings.display.table.y, settings.display.table.width, settings.display.table.height);
        settings.shapes.lines.forEach(l => line(l[0]["x"], l[0]["y"], l[1]["x"], l[1]["y"]));

    }
    getSlot() {
        if ((mouseX > settings.display.table.x) && (mouseX < (settings.display.table.x + settings.display.table.width)) && (mouseY > settings.display.table.y) && (mouseY < (settings.display.table.y + settings.display.table.height))) {
            let c = mouseX - settings.display.table.x,
                d = mouseY - settings.display.table.y,
                x = 0, bj = false,
                y = 0;
            for (let i = 1; i < 3; i++) {
                if ((settings.shapes.slot.width * (i)) > c) break;
                x = i;
            }
            for (let i = 1; i < 3; i++) {
                if ((settings.shapes.slot.height * (i)) > d) break;
                y = i;
            }
            return { x, y }
        }
        return null;
    }
    drawValue({ x, y }) {
        noFill()
        strokeWeight(settings.display.shapes.stroke)
        let pos = settings.shapes.slots[x][y],
            shape = this.gameManager.game.get(x, y),
            c=this.gameManager.game.players[this.gameManager.game.cp].color;
        stroke(...settings.palettes.colors[c])
        if (shape === "O") {
            circle(pos[0], pos[1], settings.display.shapes.circle.radius)
        }
        else if (shape === "X") {
            settings.display.shapes.cross.lines.forEach(l =>
                line(l[0].x + pos[0], l[0].y + pos[1], l[1].x + pos[0], l[1].y + pos[1])
            )
        }

    }
}