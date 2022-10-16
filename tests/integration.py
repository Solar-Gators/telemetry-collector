import os, pty, subprocess, time
from sys import stderr


def fake_port():
    master, slave = pty.openpty()
    s_name = os.ttyname(slave)

    return s_name, master, slave

def start_collector(port, service_url):
    my_env = {}
    my_env["UART_PORT"] = port
    my_env["UART_BAUD_RATE"] = '98000'
    my_env["GUI_SERVICE"] = service_url
    return subprocess.Popen("./collector", env=my_env)

def test_start_condition(capsys):
    # Setup fake port
    s_name, master, slave = fake_port()

    # Start collector
    start_collector(s_name, "test")
    # TODO: Figure out how to signal that the collector is connected
    time.sleep(1)

    # Send a none start condition
    os.write(master, b'\0x123')
    os.write(master, b'\0x22')

    # TODO: Add some assertions from stdout
