import sys
from socket import *
from lib import Lib

import socket

PORT = 9000
BUFSIZE = 1000

def main(argv):
    serverName = '127.0.0.1'
    clientSocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    clientSocket.connect((serverName, PORT))
    sentence = raw_input('Input lowercase sentence:')
    clientSocket.send(sentence.encode())
    modifiedSentence = clientSocket.recv(1024)
    print('From server:',modifiedSentence.decode())

    clientSocket.close()
def receiveFile(fileName,  conn):
	# TO DO Your Code
	print('jajaja')

if __name__ == "__main__":
   main(sys.argv[1:])
