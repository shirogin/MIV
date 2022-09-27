class RLE:
    @staticmethod
    def encode(byee):
        bye=[(i+256) if(i<0) else i for i in byee]
        result=""
        i=0
        while( i < len(bye)):
            j=i
            counter=1
            while(j<len(bye)-1 and bye[j+1]==bye[j]):
                counter+=1
                j+=1
            if(counter>2):
                n=counter | 32768
                result+=chr(n/256)
                result+=chr(n%256)
                result+=chr(bye[i])
                i+=counter
            else:            
                j=i
                arr=""    
                counter=0
                while(j<len(bye)-2  and not (bye[j]==bye[j+1] and bye[j+1]==bye[j+2])):
                    arr+=chr(bye[j])
                    counter+=1
                    j+=1
                if(i+counter == len(bye)-2):
                    counter+=2
                    arr+=chr(bye[-2])+chr(bye[-1])
                elif (i+counter == len(bye)-1):
                    counter+=1
                    arr+=chr(bye[-1])
                n=counter & 32767
                result+=chr(n/256)
                result+=chr(n%256)
                result+=arr
                i+=counter
        return result
    @staticmethod
    def decode(byee):
        bye=[(i+256) if(i<0) else i for i in byee]
        result=""
        i=0
        while(i<len(bye)):
            if((bye[i] & 128)==128):
                n=abs(32768-(bye[i]*256)+bye[i+1])
                for j in range(n):
                    result+=chr(bye[i+2])
                i+=3
            else :
                n=abs((bye[i]*256)+bye[i+1])
                for j in range(n):
                    result+=chr(bye[i+j+2])
                i+=2+n
        return result