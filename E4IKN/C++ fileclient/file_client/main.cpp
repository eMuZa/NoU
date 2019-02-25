//============================================================================
// Name        : file_client.cpp
// Author      : Lars Mortensen
// Version     : 1.0
// Description : file_client in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iknlib.h>

using namespace std;

void receiveFile(string fileName, int filesize, int socketfd);

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 3)
    {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    char buffer[100];

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
        error("ERROR connecting");
    }

    n = write(sockfd,argv[3],strlen(argv[3]));
    if (n < 0)
    {
         error("ERROR writing to socket");
    }
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0)
    {
         error("ERROR reading from socket" );
    }
    int filesize = atoi(buffer);
    if(filesize != 0)
    {
        receiveFile(argv[3], filesize,sockfd);
    }
    else
    {
        cout << "File not found!" << endl;
    }

    close(sockfd);
    return 0;
}

/**
 * Modtager filstørrelsen og udskriver meddelelsen: "Filen findes ikke" hvis størrelsen = 0
 * ellers
 * Åbnes filen for at skrive de bytes som senere modtages fra serveren (HUSK kun selve filnavn)
 * Modtag og gem filen i blokke af 1000 bytes indtil alle bytes er modtaget.
 * Luk filen, samt input output streams
 *
 * @param fileName Det fulde filnavn incl. evt. stinavn
 * @param sockfd Stream for at skrive til/læse fra serveren
 */
void receiveFile(string fileName, int filesize, int sockfd)
{  
    ofstream file(fileName, ofstream::binary | ios::trunc);
    if (file.is_open())
    {
        for(int i = 0; i < filesize/1000+1; i++)
        {
            int size;
            char buffer[1000];
            int n = read(sockfd,buffer,1000);
            if (n < 0)
            {
                 error("ERROR reading from socket" );
            }
            file.seekp (1000*i);
            if(i == filesize/1000)
            {
                size = filesize-(i*1000);
                file.write (buffer, size);
                cout << "im here " << size << endl;
            }
            else
            {
                size = 1000;
                file.write (buffer, 1000);
            }
        }
        cout << "File Downloaded!" << endl;
        cout << "Name: " << fileName << endl;
        cout << "Size: " << filesize << endl;
        file.close();
    }
}

