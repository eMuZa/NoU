import sys
import socket
import os

HOST = '10.0.0.2'
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

        clientMsg = "Message from Client:{}".format(message)
        clientIP  = "Client IP Address:{}".format(address)

        print(clientMsg)
        print(clientIP)

    #Sending to client
        UDPServerSocket.sendto(clientMsg,addr)

if __name__ == "__main__":
   main(sys.argv[1:])
