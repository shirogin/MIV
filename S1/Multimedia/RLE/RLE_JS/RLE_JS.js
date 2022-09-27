let data
function preload() {
    loadBytes("images/1.img",(dat)=>{
        data = dat;
    },(err)=>{
        console.error(err);
    });
  }
function setup() {
    RLE.encode(data)
}


function draw() {

}
