import serial, ConfigParser
config = ConfigParser.ConfigParser()
config.readfp(open("../../conf.cfg"))

ser = serial.Serial(config.get("UART", "PORT"), config.get("UART", "BAUD_RATE"))

def wait_for_transmission():
    global ser
    d = ser.read(1)
    return ord(d[0])
