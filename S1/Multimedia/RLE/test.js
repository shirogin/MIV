const fs =require("fs"),
    fsP=fs.promises
    path= require("path");
class Pixel{
    R;G;B;
    constructor(red=255,green=255,blue=255){
        this.R=red;
        this.G=green;
        this.B=blue;
    }
    Hex(){
        return "#" + (this.R+0x100).toString(16).substr(-2).toUpperCase()+(this.G+0x100).toString(16).substr(-2).toUpperCase()+(this.B+0x100).toString(16).substr(-2).toUpperCase();
    }
    equals(pixel){
        return this.R===pixel.R &&  this.G===pixel.G &&  this.B===pixel.B;
    }
}
class BMP{
    HEADER={};
    DIBHEADER={};
    DATA=[];
    constructor(buffer){
        this.HEADER.Signature={dec:buffer.readInt16LE(0),hex: (buffer.readInt16LE(0)+0x10000).toString(16).substr(-4).toUpperCase()};
        this.HEADER.Size={dec:buffer.readInt32LE(2),hex: (buffer.readInt32LE(2)+0x100000000).toString(16).substr(-8).toUpperCase()};
        this.HEADER.Reserved1= (buffer.readInt16LE(6)+0x10000).toString(16).substr(-4).toUpperCase();
        this.HEADER.Reserved2= (buffer.readInt16LE(8)+0x10000).toString(16).substr(-4).toUpperCase();
        this.HEADER.Offset={dec:buffer.readInt32LE(10),hex: (buffer.readInt32LE(10)+0x100000000).toString(16).substr(-8).toUpperCase()};
        this.DIBHEADER.HSize={dec:buffer.readInt32LE(14),hex: (buffer.readInt32LE(14)+0x100000000).toString(16).substr(-8).toUpperCase()};
        this.DIBHEADER.Width={dec:buffer.readInt32LE(18),hex: (buffer.readInt32LE(18)+0x100000000).toString(16).substr(-8).toUpperCase()};
        this.DIBHEADER.Height={dec:buffer.readInt32LE(22),hex: (buffer.readInt32LE(22)+0x100000000).toString(16).substr(-8).toUpperCase()};
        let Height=this.DIBHEADER.Height.dec,
            color=[],data=[...buffer].slice(this.HEADER.Offset.dec).reverse();
        data.forEach((value,size)=>{
            //console.log(size)
            color.push(value);
            if(size%3===2){
                console.log(color);
                this.DATA.push(new Pixel(...color));
                color=[];
            }
        })
    }
}
class RLE{
    static decode(){

    }
    static encode(Pixels){
        console.log(Pixels)
    }
}
fsP.readFile(path.join(__dirname,"./Untitled.bmp")).then(buffer=>{
    if( buffer instanceof Buffer) {
        let bmp=new BMP(buffer);
        console.log(bmp)
        RLE.encode(bmp.DATA)
    }
    
}).catch(err=>{
    console.error(err);
})
