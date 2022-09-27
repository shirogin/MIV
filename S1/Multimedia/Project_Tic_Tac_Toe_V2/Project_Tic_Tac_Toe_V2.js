
function preload() {
    settings = loadJSON("./data/Settings.json");
}


function setup() {
    gameManager = new GameManager()
    //line(settings.display.width/2,0,settings.display.width/2,settings.display.height)
}


function draw() {
    if((gameManager.screenManager.screen==="GAME" && (gameManager.screenManager.getSlot() || gameManager.screenManager.getBackBtn())) || (gameManager.screenManager.screen==="MAIN" && (gameManager.screenManager.getOneBtn()|| gameManager.screenManager.getColor() ||gameManager.screenManager.getColor(1)))) 
        cursor(HAND);
    else cursor(ARROW)
}

function mousePressed(){
    if(gameManager.screenManager.screen==="GAME"){
        let slot=gameManager.screenManager.getSlot();
        if(slot) return gameManager.game.nextMove(slot);
        if(gameManager.screenManager.getBackBtn()) gameManager.clickedCase("HOME");
    }else if(gameManager.screenManager.screen==="MAIN"){
        let btn=gameManager.screenManager.getOneBtn();
        if(btn) return gameManager.clickedCase(btn);
        let cl=gameManager.screenManager.getColor() ||gameManager.screenManager.getColor(1);
        if(cl)gameManager.clickedColor(cl);
    }
    /*if(gameManager.screenManager.getSwitch()) return gameManager.switchC();
    if(gameManager.screenManager.getDifficulty()) return gameManager.switchD();*/

}
