import serial, os, socket, json

ser = serial.Serial(os.environ.get("UART_PORT"), os.environ.get("UART_BAUD_RATE"))
sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

INTERNAL_UDP_PORT = os.environ.get("INTERNAL_UDP_PORT")
INTERNAL_UDP_HOST = os.environ.get("INTERNAL_UDP_HOST")
EXTERNAL_UDP_PORT = os.environ.get("EXTERNAL_UDP_PORT")
EXTERNAL_UDP_HOST = os.environ.get("EXTERNAL_UDP_HOST")

def runs(path, body):
    data = json.dumps({
        "model": path,
        **body,
    }).encode()
    sock.sendto(data, (INTERNAL_UDP_PORT, INTERNAL_UDP_PORT))
    # Try to send to external server, but if it fails then ignore it
    try:
        sock.sendto(data, (EXTERNAL_UDP_PORT, EXTERNAL_UDP_HOST))
    except socket.error:
        pass

def wait_for_transmission():
    global ser
    d = ser.read(1)
    return int.from_bytes(d, "little")
