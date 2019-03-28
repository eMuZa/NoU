import socket
import sys
import string
import os

PORT = 9000 #Port til transmisions
BUFSIZE = 1024 # Stoerrelse af sendt data buffer
serverAddressPort = ("127.0.0.1", PORT)



def main(argv):
    #Making Socket
    UDPClientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    #Getting Raw Input
    msgToSend = input('Your Message: ')

    #Error Handle
    if not((msgToSend == "U") or (msgToSend == "u") or (msgToSend == "L") or (msgToSend == "l")):
        print("Error not a valid character: ")
        UDPClientSocket.close()


    #Encodeing Message
    bytestoSend = str.encode(msgToSend)

    #Sendng Message
    UDPClientSocket.sendto(bytestoSend, serverAddressPort)

    #Receaving message from server
    msgFromServer = UDPClientSocket.recvfrom(BUFSIZE)

    #Formatting Message
    msg = "Message from Server {}".format(str(msgFromServer[0], "utf-8"))

    #Printing Message
    print(msg)

if __name__ == "__main__":
    main(sys.argv[1:])
