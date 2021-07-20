#!/usr/bin/env python3

from tkinter import *
from tkinter import ttk
import platform
import serial


def sendLED(ledNumber: int):
    if (ledNumber==0):
        try:
            ser.write(b'a')
        except:
            statusLabel['text'] = "Failed to send command."
    elif (ledNumber == 1):
        try:
            ser.write(b'b')
        except:
            statusLabel['text'] = "Failed to send command."
    elif (ledNumber == 2):
        try:
            ser.write(b'c')
        except:
            statusLabel['text'] = "Failed to send command."

def sendCommand(commandByte: int):
    if (commandByte == 'r'):
        ser.write(b's')
        numb = 3
        ser.write(numb.to_bytes(1,'little'))
        ser.write(b'r')
    elif (commandByte == 'd'):
        ser.write(b's')
        numb = 3
        ser.write(numb.to_bytes(1,'little'))
        ser.write(b'd')


def connectByUART() -> None:
    global ser
    global baudrate
    if (platform.system().startswith("Win")):
        port = portCmbox.get()
    else:
        port = "dev/ttypUSB0"
    if not ser.is_open:
        try:
            baudrate = baudrateCmbox.get()
            ser = serial.Serial(port,baudrate)
            statusLabel['text'] = "Connection established!"
        except:
            statusLabel['text'] = "Connection could not be established."
    else:
        if baudrate != baudrateCmbox.get():
            ser.close()
            connectByUART()
        else:
            statusLabel['text'] = "Connection already opened!"

#Global variables
ser = serial.Serial()
baudrate = 0

root = Tk()
root.title("Stopwatch GUI")
root.resizable(width=False,height=False)

try:
    photo = PhotoImage(file="images/led.png")
    root.iconphoto(False,photo)
except:
    print("No photo")

statusLabel = Label(root,text="",relief=SUNKEN,anchor=W)
osLabel = Label(root,text=platform.system(),relief=SUNKEN,anchor=W)

connectionFrame = LabelFrame(root,text="Connection")
controlFrame = LabelFrame(root,text="Control")

resetBtn = Button(controlFrame,text="Reset",command=lambda: sendCommand('r'))
downCountBtn = Button(controlFrame,text="Count down",command=lambda: sendCommand('d'))

baudrateCmbox = ttk.Combobox(connectionFrame,values=[9600,19200,38400,57600,115200],state="readonly")
baudrateCmbox.current(0)
portCmbox = ttk.Combobox(connectionFrame,values=["COM3","COM4","COM5","COM6","COM7","COM8","COM9","COM10","COM11","COM12","COM13"],state="readonly")
portCmbox.current(1)

connectBtn = Button(connectionFrame,text="Connect",command=connectByUART)

connectionFrame.grid(row=0,column=3,sticky=W+S+N+E,padx=5)
controlFrame.grid(row=0,column=0,sticky=W+S+N+E,padx=5,columnspan=3)

connectByUART()

#Elements placement

resetBtn.grid(row=0,column=2,columnspan=2,sticky=W+E,padx=5)
downCountBtn.grid(row=1,column=2,columnspan=2,sticky=W+E,padx=5)

connectBtn.grid(row=2,column=0,sticky=W+E,padx=5,pady=5)
baudrateCmbox.grid(row=1,column=0,sticky=W+E,padx=5,pady=5)
portCmbox.grid(row=0,column=0,sticky=W+E,padx=5,pady=5)

statusLabel.grid(row=2,column=0,sticky=W+E,columnspan=3,padx=5)
osLabel.grid(row=2,column=3,sticky=W+E,padx=5,pady=5)

root.mainloop()

