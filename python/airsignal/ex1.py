import signal
import time


def handler(signum, frame):
    print signum, frame
    signal.alarm(1)

signal.signal(signal.SIGALRM, handler)
signal.alarm(1)

while True:
    time.sleep(10)