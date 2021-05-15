#Calculate the values of IBRD and FBRD for UART
#of Tiva-C

askerFlag = True

def validateBaudrate(baudrate):
    if int(baudrate) == 9600 or int(baudrate) == 115200:
      return True
    else:
      return False

def askForBaudrate():
  baudrate = input("Enter baudrate: ")
  if baudrate.isnumeric() and validateBaudrate(baudrate):
    return baudrate
  else:
    print("Wrong value")
    return 0
    
while(askerFlag):
  global baudrate
  result = int(askForBaudrate())
  if result != 0:
    baudrate = result
    break

  
clkDiv = 8 #16 or 8 depending on HSE in UARTCTL
sysClk = 16000000
brd = sysClk / (clkDiv*baudrate)


iprd = int(brd)
prdf = brd-int(brd)
fprd = int(prdf*64+0.5)

print("For clock division: " + str(clkDiv) + ", System clock: " + str(sysClk))
print("------------------")
print("IBRD: " + str(iprd))
print("FBRD: " + str(fprd))
print("------------------")
