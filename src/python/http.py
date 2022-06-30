import requests

def run(p):
    print(p)
    requests.post(
        "http://172.20.10.4:9000/api/mitsuba",
        json=p
    )
