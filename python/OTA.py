import serial
import time

SERIALPORT = "COM3"  # the default com/serial port the receiver is connected to
BAUDRATE = 115200      # default baud rate we talk to Moteino
TARGET = 0               # Node ID of the Target that is being OTA reflashed
HEX = "C:\\Users\\viraj\\source\\repos\\windfarm\\windfarm\\Debug\\windfarm.hex"      # the HEX file containing the new program for the Target
LINESPERPACKET = 3     # HEX lines to send per RF packet (1,2 or 3)
retries = 2


def openSerialPort():
    try:
        # open serial port
        ser = serial.Serial(SERIALPORT, BAUDRATE, timeout=1) # timeout = 0 means nonblocking
        ser.setDTR(False)
        ser.setRTS(False)
        time.sleep(2)
        ser.flushInput()
    except IOError:
        print("COM Port [", SERIALPORT, "] not found, exiting...")
        exit(1)

def main():
    openSerialPort()
    


if __name__ == "__main__":
    main()