import datetime
import time
import pyautogui
import serial
import json
    
def write_log(message):
    current_time = datetime.datetime.now()
    current_time_string = current_time.strftime("%Y-%m-%d %H:%M:%S")
    
    with open("log.txt", "a") as file:
        message = "[" + current_time_string + "]  " + message + "\n"
        file.write(message)    


# Actual STUFF

file_path = 'payload.json'

try:
    with open(file_path, 'r') as file:
        data = json.load(file)
    
    com_port = payload['COM']
    baud_rate = payload['baud-rate']
    baud_rate_str = str(baud_rate)  

except FileNotFoundError:
    write_log(f"Error: The file '{file_path}' was not found.")
except json.JSONDecodeError:
    write_log(f"Error: The file '{file_path}' is not a valid JSON.")
except Exception as e:
    write_log(f"An unexpected error occurred: {e}")

ser = serial.Serial(com_port, baud_rate)
write_log(f"Opening at {com_port}")
write_log(f"Baud Rate set to {baud_rate_str}")
write_log("Now listening!")
   
while True:
    try:
        if ser.in_waiting > 0:
            buffer = ser.readline().decode('utf-8').rstrip()
            pyautogui.typewrite(buffer)
    except Exception as e:
        print("Error:", e)