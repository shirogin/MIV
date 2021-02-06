
obst=[[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
[1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,1],
[1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
[1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1],
[1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,1],
[1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1],
[1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
[1,0,0,0,0,3,0,0,0,0,0,0,1,0,0,1],
[1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1],
[1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1],
[1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1],
[1,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1],
[1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1],
[1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1],
[1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]]; 

class Noed:
    Type=0
    x=0
    y=0
    def __init__(self,Type,x,y):
        self.Type=Type
        self.x=x
        self.y=y
    def isObstacle(self):
        return self.Type==1
class Largeur:
    def __init__(self,noeds,init,objective) :
        print(self.larg(noeds,init,objective) )

    def larg(self,noeds,init,objective) :
        print(init,objective)
        if(init==objective):
            return [init];
        ouvert=[init]
        ferme=[]
        found=False
        while (not found) and len(ouvert)>0:
            current=ouvert.pop(0)
            adja=self.adj(noeds,current.x,current.y)
            for son in adja:
                if( son == objective):
                    return son
                elif( son.Type== 0 ):
                    try:
                        ferme.index(son)
                    except:
                        print(son.Type,son.x,son.y)
                        son.Type=5
                        dtable(noeds)
                        ouvert.append(son)
                else :
                    ferme.append(son)

    def adj(self,noeds,x,y):
        myList=[]
        if( ( ( y + 1 ) < len( noeds ) ) ):
            myList.append(noeds[y+1][x])
        if(((x+1)<len(noeds[0])) ):
            myList.append(noeds[y][x+1])
        if( ( ( x - 1 ) >= 0 ) ):
            myList.append(noeds[y][x-1])
        if( ( ( y - 1 ) >= 0 ) ):
            myList.append(noeds[y-1][x])
        return myList
Noeds=[]
init=None
fin=None
for y in range(len(obst)):
    Noeds.append([])
    for x in range(len(obst[y])):
        NOED=Noed(obst[y][x],x,y)
        Noeds[y].append(NOED)
        if(obst[y][x]==3):
            fin=NOED
        if(obst[y][x]==2):
            init=NOED
size(512, 512)
w=512
h=512
out = createImage(w,h,RGB)
out.loadPixels()
def dtable(noeds):
    for x in range(w):
        for y in range(h):
            loc = x + y*w;
            stepx=w/16;
            stepy=h/16;
            i= y/stepy; j=x/stepx;
            val=noeds[i][j].Type;
            if( val==0):
                r= 0
                g=0
                b=0
            elif val==1 :
                r= 0
                g=0
                b=255
            elif val ==2:
                r= 255 
                g=0
                b=0
            elif val==3:
                r= 0 
                g=255
                b=0
            else :
                r=10
                g=20
                b=100
            c = color(r, g, b);
            out.pixels[loc]=c;
    out.updatePixels()
    image(out,0,0)
dtable(Noeds)
Largeur(Noeds,init,fin)