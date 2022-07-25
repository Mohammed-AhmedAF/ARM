from tkinter import *
from tkinter import ttk

def calculateBaudrate():
    systemClock = int(systemClockCmBox.get())*1000000
    baudrate = int(baudrateCmBox.get())
    if overSampVar.get() == 1:
        usartdivDecimal = (systemClock)/((baudrate)*16)
    else:
        usartdivDecimal = (systemClock)/((baudrate)*8)

    #Get the fraction
    mantissa = int(usartdivDecimal)
    print(mantissa)
    fraction = usartdivDecimal - mantissa
    fraction = round(fraction*16)
    usartdivResultLabel.config(text=str(hex(mantissa))+str(fraction))

window = Tk()
window.resizable(width=False,height=False)
baudrateValues = [9600,19200,38400,57600,115200]
systemClockValues = [16,24,36,48,56,72]
window.title("STM32 UART Calculator")
overSampVar = IntVar()

inputFrame = Frame(window)
systemClockLabel = Label(inputFrame,text="System clock")
systemClockCmBox = ttk.Combobox(inputFrame,values=systemClockValues,state="readonly")
systemClockCmBox.current(0)
baudrateLabel = Label(inputFrame,text="Baudrate ")
baudrateCmBox = ttk.Combobox(inputFrame,values=baudrateValues,state="readonly")
baudrateCmBox.current(0)
calculateButton = Button(inputFrame,text="Calculate",command=calculateBaudrate)
overSamplingLabel = Label(inputFrame,text="Over sampling")
overSamplingChBox = Checkbutton(inputFrame,variable=overSampVar,onvalue=1,offvalue=0)
usartdivLabel = Label(inputFrame,text="USARTDIV")
usartdivResultLabel = Label(inputFrame,foreground="blue")

inputFrame.grid(row=0,column=0)
systemClockLabel.grid(row=0,column=0,padx=10,pady=5)
baudrateLabel.grid(row=1,column=0,padx=10,pady=5)
baudrateCmBox.grid(row=1,column=1,padx=10,pady=5)
systemClockCmBox.grid(row=0,column=1,padx=10,pady=5)
overSamplingLabel.grid(row=2,column=0,padx=10,pady=5)
overSamplingChBox.grid(row=2,column=1,padx=10,pady=5)
calculateButton.grid(row=3,column=0,padx=10,pady=5)
usartdivLabel.grid(row=4,column=0,padx=10,pady=10)
usartdivResultLabel.grid(row=4,column=1,padx=10,pady=10)


window.mainloop()