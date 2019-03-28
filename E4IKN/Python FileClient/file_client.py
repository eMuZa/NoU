import sys
from socket import *
import string
import os

import socket

PORT = 9000 #Port til transmisions
BUFSIZE = 1024 # Stoerrelse af sendt data buffer
serverName = '127.0.0.1' # IP

def main(argv):
    clientSocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    clientSocket.connect((serverName, PORT))
    filePath = raw_input('Your Filesname : ')

    if filePath != 'c':
        clientSocket.send(filePath)
        receiveFile(filePath,clientSocket)

    clientSocket.close()


def receiveFile(fileName,  conn):
    data = conn.recv(BUFSIZE)
    if data[:3] != "ERR":
        fileSize = int(data)
        message = raw_input("File does exist, filesize:" + str(fileSize) + " Bytes: download press [y or n]: ")
        if message == "y":
            conn.send("OK")

            f = open("new " + fileName[fileName.rfind('/', 0,  len(fileName))+1:], 'wb')

            data = conn.recv(BUFSIZE)
            totalRecvLength = len(data)
            f.write(data)
            while totalRecvLength < fileSize:
                data = conn.recv(BUFSIZE)
                totalRecvLength += len(data)
                f.write(data)
                print("{0:.2f}".format((float(totalRecvLength)/float(fileSize))*100)+"% Done")
                print("Download is finished")
    else:
        print("File does not exit")

if __name__ == "__main__":
   main(sys.argv[1:])
