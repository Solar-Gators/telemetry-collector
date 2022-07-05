import serial, configparser, requests
config = configparser.ConfigParser()
config.readfp(open("conf.cfg"))

ser = serial.Serial(config.get("UART", "PORT"), config.get("UART", "BAUD_RATE"))

def runs(path, body):
    requests.post(
        "http://localhost:9000/api/" + path,
        json=body
    )

def wait_for_transmission():
    global ser
    d = ser.read(1)
    return int.from_bytes(d, "little")
