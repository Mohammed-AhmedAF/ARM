from tkinter import *
from functools import partial
from tkinter import ttk
import ttkbootstrap as ttkb

def calculateBaudrate():
    try:
        sysClk = int(sysClockEntry.get())*1000000
        sysDiv = int(clockDivCombobox.get())
        baudrate = int(baudrateCobombox.get())
    
        brd = sysClk / (sysDiv*baudrate)

        iprd = int(brd)
        prdf = brd-int(brd)
        fprd = int(prdf*64+0.5)

        integerValueLabel['text'] = str(iprd)
        fractionValueLabel['text'] = str(fprd)
        statusLabel.config(text="Calculated successfully!")
    except:
        statusLabel.config(text="Error in calculation: Check entries.")

app = ttkb.Window(themename="darkly")
app.title("Tiva-C baudrate calculator")
app.iconbitmap("images/appIcon.ico")
app.resizable(False,False)
baudrateFrame = Frame(app)

sysClockVal = StringVar()

baudrateLabel = Label(baudrateFrame,text="Baudrate ")
sysClockLabel = Label(baudrateFrame,text="System Clock (Mhz)")
sysClockEntry = Entry(baudrateFrame,textvariable=sysClockVal)
sysClockEntry.insert(0,"16")
clockDivLabel = Label(baudrateFrame,text="Clock divisor ")
clockDivCombobox = ttk.Combobox(baudrateFrame,state="readonly")
clockDivCombobox['values'] = [16,8]
clockDivCombobox.current(0)
baudrateCobombox = ttk.Combobox(baudrateFrame,state="readonly")
baudrateCobombox['values'] = [9600,19200,38400,57600,115200]
baudrateCobombox.current(0)

integerLabel = Label(baudrateFrame,text="Integer (IBRD): ")
integerValueLabel = Label(baudrateFrame,text="0")
fractionLabel = Label(baudrateFrame,text="Fraction (FBRD): ")
fractionValueLabel = Label(baudrateFrame,text="0")
statusLabel = Label(app,relief="sunken")


calculateButton = Button(baudrateFrame,text="Calculate!",command=calculateBaudrate)

#Widgets positining
baudrateFrame.grid(row=0,column=0,padx=5,pady=5,sticky=E+W+S+N)
baudrateLabel.grid(row=0,column=0,padx=5,sticky=E+W+S+N)
sysClockLabel.grid(row=1,column=0,padx=5,pady=5,sticky=E+W+S+N)
sysClockEntry.grid(row=1,column=1,padx=5,pady=5,sticky=E+W+S+N)
clockDivLabel.grid(row=2,column=0,padx=5,pady=5,sticky=E+W+S+N)
clockDivCombobox.grid(row=2,column=1,padx=5,pady=5,sticky=E+W+S+N)
integerLabel.grid(row=3,column=0,padx=5,pady=5,sticky=E+W+S+N)
integerValueLabel.grid(row=3,column=1,padx=5,pady=5,sticky=E+W+S+N)
fractionLabel.grid(row=4,column=0,padx=5,pady=5,sticky=E+W+S+N)
fractionValueLabel.grid(row=4,column=1,padx=5,pady=5,sticky=E+W+S+N)
baudrateCobombox.grid(row=0,column=1,padx=5,sticky=E+W+S+N)
calculateButton.grid(row=5,column=0,sticky=E+W+S+N)
statusLabel.grid(row=1,column=0,sticky=E+W+N+S,padx=5,pady=5)
app.mainloop()
