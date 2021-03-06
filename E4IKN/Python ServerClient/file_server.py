import sys
import socket as s
import os

HOST = '127.0.0.1'
PORT = 9000
BUFSIZE = 1024

def main(argv):

    serverSocket = s.socket(s.AF_INET,s.SOCK_STREAM)
    serverSocket.bind((HOST,PORT))
    serverSocket.listen(1)
    print ('The server is ready to receive')
    while True:
        connectionSocket, addr = serverSocket.accept()
        print("client connected: " + str(addr))
        filePath = connectionSocket.recv(BUFSIZE).decode()

        sendFile(filePath,BUFSIZE,connectionSocket)
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
