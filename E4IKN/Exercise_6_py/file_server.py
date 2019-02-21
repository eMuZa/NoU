import sys
import socket as s
from lib import Lib

HOST = ''
PORT = 9000
BUFSIZE = 1000

def main(argv):


    serverSocket = s.socket(s.AF_INET,s.SOCK_STREAM)
    serverSocket.bind((HOST,PORT))
    serverSocket.listen(1)
    print 'The server is ready to receive'
    while True:
        connectionSocket, addr = serverSocket.accept()

        sentence = connectionSocket.recv(1024).decode()
        sendFile(data,check_File_Exists(data),connectionSocket)

        connectionSocket.close()

def sendFile(fileName,  fileSize,  conn):
    if fileName:
        conn.send(fileSize)
        f = open(fileName,'rb')
        l = f.read(BUFSIZE)
        while(l):
            conn.send(l)
            l = f.read(BUFSIZE)
        f.close()
        print 'File transfer complete'
        conn.send('File Transfer complete on the client')
    else:
        conn.send('No such file')

if __name__ == "__main__":
   main(sys.argv[1:])
