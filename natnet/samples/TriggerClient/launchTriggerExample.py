import os
import time
import subprocess

proc = subprocess.Popen(["./build/triggerClient", "25.54.203.95", "rec"])
print("-> command: rec sended")
time.sleep(10)
print("waiting")
proc = subprocess.Popen(["./build/triggerClient", "25.54.203.95", "stop"])
print("-> command: stop sended")
proc.wait()

