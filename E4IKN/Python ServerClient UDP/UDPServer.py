import sys
import socket
import os

fileName = "/proc/uptime"
fileName2 = "/proc/loadavg"

HOST = '127.0.0.1'
PORT = 9000
BUFSIZE = 1024


def main(argv):
#Creating Socket
    UDPServerSocket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

#Binding Socket addr and ip
    UDPServerSocket.bind((HOST, PORT))

#Startup print
    print("UDP Server up and listening")

    while (1):
        bytesAddrPair = UDPServerSocket.recvfrom(BUFSIZE)
        message = bytesAddrPair[0]
        addr = bytesAddrPair[1]

        clientMsg = message
        clientIP  = "Client IP Address:{}".format(addr)

        print(clientMsg)
        print(clientIP)

        if ((message == "u") or (message == "U")):

            with open(fileName, 'rb') as f:
                bytestoSend = f.read(BUFSIZE)
        else:
            with open(fileName2, 'rb') as t:
                bytestoSend = t.read(BUFSIZE)

    #Sending to client
        UDPServerSocket.sendto(bytestoSend,addr)

if __name__ == "__main__":
   main(sys.argv[1:])
