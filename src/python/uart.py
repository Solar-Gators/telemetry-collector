import serial
ser = serial.Serial("/dev/cu.usbserial-AK08MOF9", 57600)

def wait_for_transmission():
    global ser
    d = ser.read(1)
    return ord(d[0])
