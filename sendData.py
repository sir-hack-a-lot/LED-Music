import serial, time
ser = serial.Serial('/dev/ttyACM0');

def color(r,g,b):
    ret = 0
    ret+= b;
    ret+= g << 8;
    ret+= r << 16;

    return ret;

for i in range(0,255):
    data = (i + color(255,0,0)).to_bytes(4,byteorder='big');
    ser.write(data)

    print(i, " --> ", data)
    time.sleep(0.125)
