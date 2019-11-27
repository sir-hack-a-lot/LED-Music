import serial
import time, math
import pandas as pd

ser = serial.Serial('/dev/ttyACM0');

def color(r,g,b):
    ret = 0
    ret+= b << 8;
    ret+= g << 16;
    ret+= r << 24;

    return ret;

# format weather data into a light sequence throughout an LED strip
def fmtData (path_to_csv):
    data = pd.read_csv(path_to_csv)
    rows = data.shape[0]
    
    prevMin=0; prevMax=0;
    for i in range(0,rows):
        val = int((i/rows) * int(rows/7))

        tempMin= int(1e2*(math.log(abs(int(data.loc[i,['tempMin']]))+ math.e)))
        tempMax= int(1e2*(math.log(abs(int(data.loc[i,['tempMax']]))+ math.e)))
        
        diffMin=abs(tempMin-prevMin); diffMax=abs(tempMax-prevMax);
        
        if(diffMin <= 255 and diffMin >= 0 and diffMax >= 0 and diffMax <= 255): 
            red = diffMax
            green =0 
            blue = diffMin
        else:
            red=0; green=0; blue=0;

        #print("(red: ",red,",blue: ",blue)
        
        prevMin= tempMin
        prevMax= tempMax

        serData = (val + color(red,green,blue)).to_bytes(4,byteorder='big');
        if ser.open:
            ser.write(serData)
            print(val, "\t",serData)
            time.sleep(0.125)
        

fmtData('clean_weather_data.csv');
