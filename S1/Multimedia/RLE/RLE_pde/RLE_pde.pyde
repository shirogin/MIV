from RLE import RLE
from Images import Images
from ImagesData import Images as ImagesList
size(180,600)
for i in range(len(ImagesList)):
    #saving image data
    imageName="images/"+str(i+1)+".Pimg"
    Images.save(ImagesList[i],imageName)

    #encode images
    file=loadBytes(imageName)
    Ti=len(file)
    encode=RLE.encode(file)
    Tr=len(encode)
    #print("encode : ",len(encode))
    saveBytes("encoded/"+imageName,encode)

    #decode images
    file2=loadBytes("encoded/"+imageName)
    decode=RLE.decode(file2)
    Images.visualize(decode,6,6,(i*7),0,30)
    #print("decode : ",len(decode))
    
    print("Ti: ",Ti," Tr: ",Tr," Taux de comp : ",1.0-(float(Tr)/float(Ti)))
    saveBytes("decoded/"+imageName,decode)
