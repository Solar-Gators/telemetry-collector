import serial, requests, os

ser = serial.Serial(os.environ.get("UART_PORT"), os.environ.get("UART_BAUD_RATE"))

def runs(path, body):
    requests.post(
        f"{os.environ.get('GUI_SERVICE')}/api/{path}",
        json=body
    )

def wait_for_transmission():
    global ser
    d = ser.read(1)
    return int.from_bytes(d, "little")
