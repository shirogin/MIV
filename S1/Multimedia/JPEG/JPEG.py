import DCT
from RLE import RLE


class JPEG:
    def __init__(self, image, encode=True, encoding="RLE", coff=5):
        self.image = image
        self.height = len(image)
        self.width = len(image[0])
        self.coff = coff
        self.blocks = self.cutToBlocks()
        if(encode):
            self.RLE = self.encodeRLE()
        else:
            self.RLE = self.decodeRLE()

    def collectBlocks(self):
        image = [[0 for x in range(self.width)] for y in range(self.height)]
        p = 0
        for y in range(0, self.height, 8):
            for x in range(0, self.width, 8):
                j = 0
                while(j < 8 and (y+j) < self.height):
                    i = 0
                    while(i < 8 and (x+i) < self.width):
                        u = y+j
                        v = x+i
                        image[u][v] = self.blocks[p][j][i]
                        i += 1
                    j += 1
                p += 1
        return image

    def decodeRLE(self):
        blocks = []
        for block in self.blocks:
            DEQUENT = DCT.DeQuantization(block)
            idct = DCT.IdctTransform(DEQUENT)
            blocks.append(idct)
        return

    def encodeRLE(self):
        rle = str(chr(int(self.width/256))) + str(chr(self.width % 256)) + \
            str(chr(int(self.height/256))) + str(chr(self.height % 256))
        for block in self.blocks:
            dct = DCT.dctTransform(block)
            QUENT = DCT.Quantization(dct)
            zigzag = DCT.zigZagFashion(QUENT)
            rle += RLE.encode(zigzag)
        return rle

    def cutToBlocks(self):
        blocks = []
        for y in range(0, self.height, 8):
            for x in range(0, self.width, 8):
                block = []
                j = 0
                while(j < 8 and (y+j) < self.height):
                    line = []
                    i = 0
                    while(i < 8 and (x+i) < self.width):
                        line.append(self.image[y+j][x+i])
                        i += 1
                    block.append(line)
                    j += 1
                blocks.append(block)
        return blocks
