import serial

serialPort = serial.Serial(port="COM11",baudrate=9600)

f = open("temperature.txt","w+")
while(1):
    tempData = serialPort.readline()
    line = str(tempData,'UTF-8')
    f.write(line)
    print(line)