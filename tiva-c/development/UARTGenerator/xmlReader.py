import xml.dom.minidom

doc = 0

def openFile():
    global doc
    doc = xml.dom.minidom.parse('uartPorts.xml')


def getModuleGPIOParameters(uartModule):
    moduleData = dict()
    module = doc.getElementsByTagName(uartModule)
    portName = module.item(0)
    moduleNodes = portName.childNodes
    #Get port
    port =moduleNodes.item(1).firstChild.nodeValue.strip()
    moduleData['port'] = port
    print(port)
    print(moduleNodes.item(2))
    #Get Rx pin
    rxPin = moduleNodes.item(3).firstChild.nodeValue.strip()
    print(rxPin)
    moduleData['rx'] = rxPin
    #Get Tx pin
    txPin = moduleNodes.item(5).firstChild.nodeValue.strip()
    print(txPin)
    moduleData['tx'] = txPin
    return moduleData
