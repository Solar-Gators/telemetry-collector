import requests

def run(path, body):
    requests.post(
        "http://localhost:9000/api/" + path,
        json=body
    )
