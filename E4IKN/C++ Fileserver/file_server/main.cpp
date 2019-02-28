//============================================================================
// Name        : file_server.cpp
// Author      : Lars Mortensen
// Version     : 1.0
// Description : file_server in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iknlib.h>

using namespace std;

void sendFile(string fileName, int filesize, int outToClient);

/**
 * main starter serveren og venter på en forbindelse fra en klient
 * Læser filnavn som kommer fra klienten.
 * Undersøger om filens findes på serveren.
 * Sender filstørrelsen tilbage til klienten (0 = Filens findes ikke)
 * Hvis filen findes sendes den nu til klienten
 *
 * HUSK at lukke forbindelsen til klienten og filen nÃ¥r denne er sendt til klienten
 *
 * @throws IOException
 *
 */
int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, filesize;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2)
     {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
     {
        error("ERROR opening socket");
     }
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) & serv_addr, sizeof(serv_addr)) < 0)
     {
         error("ERROR on binding");
     }

     while(1)
     {
        //int filesize;
        listen(sockfd,5);
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
        {
             error("ERROR on accept");
        }
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);       
        if (n < 0)
        {
            error("ERROR reading from socket");
        }

        if((filesize = check_File_Exists(buffer)) != 0)
        {
            sendFile(buffer, filesize, newsockfd);
        }
        else
        {
            n = write(newsockfd,"0",1);
            if (n < 0)
            {
                error("ERROR writing to socket");
            }
        }
        close(newsockfd);
     }
     close(sockfd);
     printf("Shutting down");
     return 0;
}

/**
 * Sender filen som har navnet fileName til klienten
 *
 * @param fileName Filnavn som skal sendes til klienten
 * @param fileSize Størrelsen på filen, 0 hvis den ikke findes
 * @param outToClient Stream som der skrives til socket
     */
void sendFile(string fileName, int filesize, int outToClient)
{
    int n;
    char buffer[filesize];
    sprintf(buffer, "%d", filesize);
    cout << "Requested file:   " << fileName << endl;
    cout << "Filesize:         " << filesize << endl;

    n = write(outToClient, buffer, strlen(buffer)+1);
    if (n < 0)
    {
        error("ERROR writing to socket");
    }


    ifstream file(fileName, ios::binary);
    if (file.is_open())
    {
        for(int i = 0; i < filesize/1000+1; i++)
        {
            int size;
            file.seekg (1000*i);
            if(i == filesize/1000)
            {
                size = filesize-(i*1000);
                file.read (buffer, size);
                cout << "Sending " << size << " bytes" << endl;
            }
            else
            {
                size = 1000;
                file.read (buffer, 1000);
                cout << "Sending " << size << " bytes" << endl;
            }
            n = write(outToClient, buffer, size);
            if (n < 0)
            {
                  error("ERROR writing to socket");
            }
        }
        cout << "File sent!" << endl;
        file.close();
    }
}
