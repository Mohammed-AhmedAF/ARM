from cProfile import label
from cgitb import text
from msilib.schema import CheckBox
from tkinter import *
from tkinter import ttk

def getChosenModule():
    module = moduleCmbBox.get()
    return module[-1]

def getStopBits():
    stopBitsChoice = stopBitsCmbBox.get()
    if stopBitsChoice == 1:
        return "UART_STOPBITS_1"
    else:
        return "UART_STOPBITS_2"


def getFIFOChoice():
    FIFOChoice = FIFOVar.get()
    if FIFOChoice == 0:
        return "UART_FIFO_DISABLED"
    else:
        return "UART_FIFO_ENABLED"

def getClockSourceChoice():
    clockSource = clockSourceCmbBox.get()
    if clockSource == "RC":
        return "UART_CLOCKSOURCE_RC"
    else:
        return "UART_CLOCKSOURCE_PIOSC"

def getWordSizeChoice():
    wordSizeChoice = int(wordSizeCmbBox.get())
    if wordSizeChoice == 5:
        return "UART_WORDSIZE_5"
    elif wordSizeChoice == 6:
        return "UART_WORDSIZE_6"
    elif wordSizeChoice == 7:
        return "UART_WORDSIZE_7"
    elif wordSizeChoice == 8:
        return "UART_WORDSIZE_8"
    else:
        return "UART_WORDSIZE_8"

def getHighSpeed():
    if highSpeedVar == 0:
        return "UART_HIGHSPEED_DIV16"
    else:
        return "UART_HIGHSPEED_DIV8"


def getCalculatedBdrParam(param):
    sysClk = int(systemClockCmbBox.get())*1000000
    sysDiv = int(highSpeedVar.get())
    baudrate = int(baudrateCmbBox.get())

    brd = sysClk / (sysDiv*baudrate)
    iprd = int(brd)
    prdf = brd - int(brd)
    fprd = int(prdf*64+0.5)
    if param == "INTEGER":
        return str(iprd)
    else:
        return str(fprd)

def getInterrupts():
    return "INTERRUPS"


def generateStruct():
    generatedCodeText.config(state=NORMAL)
    generatedCodeText.delete("1.0",END)
    statusLabel.config(text="Generated!")
    structName = f"uart{getChosenModule()}Config"
    generatedCodeText.insert(INSERT,f"UARTConfig_t * {structName};\r\n")
    generatedCodeText.insert(INSERT,f"{structName}.u8Module" + " = " + moduleCmbBox.get() + ";\r\n")
    generatedCodeText.insert(INSERT,f"{structName}.u8StopBits" + " = " + getStopBits() + ";\r\n")
    generatedCodeText.insert(INSERT,f"{structName}.u8FIFOEnabled" + " = " + getFIFOChoice() + ";\r\n")
    generatedCodeText.insert(INSERT,f"{structName}.u8ClockSource" + " = " + getClockSourceChoice() + ";\r\n")
    generatedCodeText.insert(INSERT,f"{structName}.u8WordSize" + " = " + getWordSizeChoice() + ";\r\n")
    generatedCodeText.insert(INSERT,f"{structName}.u8HighSpeedEnabled" + " = " + getHighSpeed() + ";\r\n")
    generatedCodeText.insert(INSERT,f"{structName}.u16Integer" + " = " + getCalculatedBdrParam("INTEGER") + ";\r\n")
    generatedCodeText.insert(INSERT,f"{structName}.u8Fraction" + " = " + getCalculatedBdrParam("FRACTION") + ";\r\n")
    generatedCodeText.insert(INSERT,f"{structName}.u8InterruptsEnabled" + " + " + getInterrupts() + ";\r\n")
    generatedCodeText.insert(INSERT,f"UART_vidInit(&{structName});\r\n")
    generatedCodeText.config(state=DISABLED)

top = Tk()
top.title("UART Configurator")


moduleList = ["UART_MODULE_0","UART_MODULE_1","UART_MODULE_2","UART_MODULE_3","UART_MODULE_4","UART_MODULE_5",
"UART_MODULE_6","UART_MODULE_7"]
clockSourceList = ["RC","PIOSC"]
baudrateList = [9600,19200,38400,57600,115200]
systemClockList = [8,16,20,25,40,50,80]
stopBitsList = [1,2]
wordSizeList = [5,6,7,8]
FIFOVar = IntVar()
highSpeedVar = IntVar()

#Configuration widgets
configFrame = LabelFrame(top,text="Configuration")
moduleLabel = Label(configFrame,text="Module:")
FIFOFrame = Frame(configFrame)
highSpeedFrame = Frame(configFrame)
interruptsFrame = Frame(configFrame)
moduleCmbBox = ttk.Combobox(configFrame,values=moduleList,state="readonly",width=17)
moduleCmbBox.current(0)
clockSourceLabel = Label(configFrame,text="Clock source:")
clockSourceCmbBox = ttk.Combobox(configFrame,values=clockSourceList,state="readonly",width=27)
clockSourceCmbBox.current(0)
baudrateCmbBox = ttk.Combobox(configFrame,values=baudrateList,state="readonly")
baudrateCmbBox.current(0)
baudrateLabel = Label(configFrame,text="Baudrate")
systemClockLabel = Label(configFrame,text="System clock:")
systemClockCmbBox = ttk.Combobox(configFrame,values=systemClockList,state="readonly")
systemClockCmbBox.current(0)
stopBitsLabel = Label(configFrame,text="Stop bits")
stopBitsCmbBox = ttk.Combobox(configFrame,values=stopBitsList,state="readonly")
stopBitsCmbBox.current(0)
wordSizeLabel = Label(configFrame,text="Word size")
wordSizeCmbBox = ttk.Combobox(configFrame,values=wordSizeList,state="readonly")
wordSizeCmbBox.current(0)
fifoEnabledLabel = Label(configFrame,text="FIFO enabled")
fifoEnabledRadioButton = Radiobutton(FIFOFrame,text="Enabled",var=FIFOVar,value=1)
fifoDisabledRadioButton = Radiobutton(FIFOFrame,text="Disabled",var=FIFOVar,value=0)
highSpeedLabel = Label(configFrame,text="Clock divisor")
highSpeedDiv16RadioButton = Radiobutton(highSpeedFrame,text="Div 16",var=highSpeedVar,value=16)
highSpeedDiv8RadioButton = Radiobutton(highSpeedFrame,text="Div 8",var=highSpeedVar,value=8)
highSpeedDiv8RadioButton.select()
interruptsLabel = Label(configFrame,text="Interrups")
receiveCheckBox = Checkbutton(interruptsFrame,text="Receive")
transmitCheckBox = Checkbutton(interruptsFrame,text="Transmit")
generateButton = Button(configFrame,text="Generate!",command=generateStruct)

#Generated code widgets
generatedCodeFrame = LabelFrame(top,text="Code")
generatedCodeText = Text(generatedCodeFrame,height=30,width=70)

#Statusbar
statusLabel = Label(top,relief=SUNKEN)

#Grid
configFrame.grid(row=0,column=0,padx=5,pady=5,sticky=W+E+N+S)
generatedCodeFrame.grid(row=0,column=1,padx=5,pady=5,sticky=W+E+N+S)
moduleLabel.grid(row=0,column=0,padx=5,pady=5,sticky=W+E+N+S)
moduleCmbBox.grid(row=0,column=1,padx=5,pady=5,sticky=W+E+N+S)
clockSourceLabel.grid(row=1,column=0,padx=5,pady=5,sticky=W+E+N+S)
clockSourceCmbBox.grid(row=1,column=1,padx=5,pady=5,sticky=W+E+N+S)
baudrateLabel.grid(row=2,column=0,padx=5,pady=5,stick=W+E+N+S)
baudrateCmbBox.grid(row=2,column=1,padx=5,pady=5,sticky=W+E+N+S)
systemClockLabel.grid(row=3,column=0,padx=5,pady=5,sticky=W+E+N+S)
systemClockCmbBox.grid(row=3,column=1,padx=5,pady=5,sticky=W+E+N+S)
stopBitsLabel.grid(row=4,column=0,padx=5,pady=5,sticky=W+E+N+S)
stopBitsCmbBox.grid(row=4,column=1,padx=5,pady=5,sticky=W+E+N+S)
wordSizeLabel.grid(row=5,column=0,padx=5,pady=5,sticky=W+E+N+S)
wordSizeCmbBox.grid(row=5,column=1,padx=5,pady=5,stick=W+E+N+S)
fifoEnabledLabel.grid(row=6,column=0,padx=5,pady=5,sticky=W+E+N+S)
FIFOFrame.grid(row=6,column=1,padx=5,pady=5,stick=W+E+N+S)
fifoEnabledRadioButton.grid(row=0,column=0,padx=5,pady=5,sticky=W+E+N+S)
fifoDisabledRadioButton.grid(row=0,column=1,padx=5,pady=5,sticky=W+E+N+S)
highSpeedFrame.grid(row=7,column=1,padx=5,pady=0,sticky=W+E+N+S)
highSpeedLabel.grid(row=7,column=0,padx=5,pady=0,sticky=W+E+N+S)
highSpeedDiv16RadioButton.grid(row=0,column=0,padx=5,pady=0,sticky=W+E+N+S)
highSpeedDiv8RadioButton.grid(row=0,column=1,padx=5,pady=0,sticky=W+E+N+S)
interruptsLabel.grid(row=8,column=0,padx=5,pady=5,sticky=W+E+N+S)
interruptsFrame.grid(row=8,column=1,padx=5,pady=5,sticky=W+E+N+S)
receiveCheckBox.grid(row=0,column=0,padx=5,pady=5,sticky=W+E+N+S)
transmitCheckBox.grid(row=0,column=1,padx=5,pady=5,sticky=W+E+N+S)
generateButton.grid(row=10,column=0,padx=5,pady=5,sticky=W+E+N+S)
generatedCodeText.pack()

statusLabel.grid(row=1,column=0,sticky=E+W+N+S,padx=5,pady=5)

def launchApp():
    top.mainloop()

if __name__ == "__main__":
    launchApp()

