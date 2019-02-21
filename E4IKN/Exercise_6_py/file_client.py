import sys
from socket import *
from lib import Lib

PORT = 9000
BUFSIZE = 1000

def main(argv):
	serverName = 'servername'
    serverPort = PORT
    clientSocket = socket(AF_INET, SOCK_STREAM)
    clientSocket.connect((serverName.serverPort))
    sentence = raw_input('Input lowercase sentence:')
    clientSocket.send(sentence.encode())
    modifiedSentence = clientSocket.recv(1024)
    print('From server:',modifiedSentence.decode())

    clientSocket.close()
def receiveFile(fileName,  conn):
	# TO DO Your Code

if __name__ == "__main__":
   main(sys.argv[1:])
