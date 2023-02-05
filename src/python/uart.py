import serial, os, socket, json

ser = serial.Serial(os.environ.get("UART_PORT"), os.environ.get("UART_BAUD_RATE"))
sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

UDP_PORT = 8000

def runs(path, body):
    data = json.dumps({
        "model": path,
        **body,
    }).encode()
    sock.sendto(data, ("127.0.0.1", UDP_PORT))
    sock.sendto(data, ('api.ufsolargators.org', UDP_PORT))

def wait_for_transmission():
    global ser
    d = ser.read(1)
    return int.from_bytes(d, "little")
