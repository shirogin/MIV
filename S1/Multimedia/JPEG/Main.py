from JPEG import JPEG


def MatrixToStr(file, mat):
    for i in mat:
        x = []
        for j in i:
            x.append(str(j))
        file.write("[ "+", ".join(x)+" ]\n")

        #l.append(", ".join(x))
with open("image.txt") as mat:
    data = [[int(a) for a in l.split(" ")] for l in mat]
    image = JPEG(data)
with open("resu.txt", "w+") as fes:
    print(image.RLE)
    fes.write(image.RLE)


'''
dct = DCT.dctTransform(data)
QUENT = DCT.Quantization(dct)
DEQUENT = DCT.DeQuantization(QUENT)
idct = DCT.IdctTransform(DEQUENT)
zigzag = DCT.zigZagFashion(QUENT)
rle = RLE.encode(zigzag)
rleList = [ord(rle[i]) for i in range(len(rle))]





with open("result.txt", "w+", encoding="utf-8")as res:
    res.write("The results are :\nImage : \n")
    MatrixToStr(res, data)
    res.write("DCT :\n")
    MatrixToStr(res, dct)
    res.write("Quantization :\n")
    MatrixToStr(res, QUENT)
    res.write("DeQuantization :\n")
    MatrixToStr(res, DEQUENT)
    res.write("IDCT :\n")
    MatrixToStr(res, idct)
    res.write("\nZigZag list :\n")
    res.write(str(zigzag))
    res.write("\nRLE :\n")
    print(rle)
    res.write(rle)
    res.write("\nRLE List of Bytes:\n")
    res.write(str(rleList))

print(len(rleList)/64)
'''
