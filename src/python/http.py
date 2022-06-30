import requests

def run(path, body):
    requests.post(
        "http://172.20.10.4:9000/" + path,
        json=body
    )
