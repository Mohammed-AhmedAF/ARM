from tkinter import *
from functools import partial
from tkinter import ttk

def calculateBaudrate():
    print("Test complete!")

app = Tk()

baudrateFrame = Frame(app)

baudrateLabel = Label(baudrateFrame,text="Baudrate: ")
baudrateCobombox = ttk.Combobox(baudrateFrame,state="readonly")
baudrateCobombox['values'] = [9600,19200,38400,57600,115200]
baudrateCobombox.current(0)

integerLabel = Label(baudrateFrame,text="Integer: ")
integerValueLabel = Label(baudrateFrame,text="0")
fractionLabel = Label(baudrateFrame,text="Fraction: ")
fractionValueLabel = Label(baudrateFrame,text="0")

calculateButton = Button(baudrateFrame,text="Calculate!",command=calculateBaudrate)

#Widgets positining
baudrateFrame.grid(row=0,column=0,padx=5,pady=5,sticky=E+W+S+N)
baudrateLabel.grid(row=0,column=0,padx=5,sticky=E+W+S+N)
integerLabel.grid(row=3,column=0,padx=5,pady=5,sticky=E+W+S+N)
integerValueLabel.grid(row=3,column=1,padx=5,pady=5,sticky=E+W+S+N)
fractionLabel.grid(row=4,column=0,padx=5,pady=5,sticky=E+W+S+N)
fractionValueLabel.grid(row=4,column=1,padx=5,pady=5,sticky=E+W+S+N)
baudrateCobombox.grid(row=0,column=1,padx=5,sticky=E+W+S+N)
calculateButton.grid(row=5,column=0,sticky=E+W+S+N)

app.mainloop()