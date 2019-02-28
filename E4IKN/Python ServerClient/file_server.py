import sys
import socket as s
from lib import Lib

HOST = '127.0.0.1'
PORT = 9000
BUFSIZE = 1024

def main(argv):

    serverSocket = s.socket(s.AF_INET,s.SOCK_STREAM)
    serverSocket.bind((HOST,PORT))
    serverSocket.listen(1)
    print 'The server is ready to receive'
    while True:
        connectionSocket, addr = serverSocket.accept()
        print("client connected: " + str(addr))
        filePath = connectionSocket.recv(BUFSIZE).decode()

<<<<<<< HEAD
=======
        sentence = connectionSocket.recv(1024).decode()
        sendFile(sentence,check_File_Exists(sentence),connectionSocket)
>>>>>>> caf51db3d7f34abf8003c63e2a64c577317de2c3

        sendFile(data,check_File_Exists(data),connectionSocket)
        connectionSocket.close()
        print("client disconnected: " + str(addr))

def sendFile(fileName,  fileSize,  conn):
    if os.path.isfile(fileName):
        conn.send(str(os.path.getsize(fileName)))
        usrResp = conn.recv(BUFSIZE)
        if usrResp == "OK":
            with open(fileName, 'rb') as f:
                bytestoSend = f.read(BUFSIZE)
                conn.send(bytestoSend)
                while bytestoSend != "":
                    bytestoSend = f.read(BUFSIZE)
                    conn.send(bytestoSend)
    else:
        conn.send("ERR")

if __name__ == "__main__":
   main(sys.argv[1:])
