class Images:
    @staticmethod
    def save(data,filename):
        result=""
        for i in data:
            result+=chr(i);
        saveBytes(filename,result)
    @staticmethod
    def visualize(data,height,width,offsetH=0,offsetW=0,scale=1):
        x=0
        y=0
        for elem in data:
            pixel=ord(elem)
            for s in range(scale):
                for ss in range(scale):
                    set(((x+offsetW)*scale)+s,((y+offsetH)*scale)+ss,color(pixel))
            x=(x+1)%width
            if(x==0): y=(y+1)%height
        