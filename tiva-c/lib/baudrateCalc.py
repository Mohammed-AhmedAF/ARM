#Calculate the values of IBRD and FBRD for UART
#of Tiva-C

def askForBaudrate():
  baudrate = input("Enter baudrate: ")
  if baudrate.isnumeric():
    return baudrate
  else:
    print("Wrong value")
    askForBaudrate()
    
baudrate = int(askForBaudrate())
  
clkDiv = 16 #16 or 8 depending on HSE in UARTCTL
sysClk = 16000000
brd = sysClk / (clkDiv*baudrate)
print(brd)

iprd = int(brd)
prdf = brd-int(brd)
fprd = int(prdf*64+0.5)

print("IBRD: " + str(iprd))
print("FBRD: " + str(fprd))
