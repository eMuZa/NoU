#include <iostream>
#include "MsgQueue.hpp"
#include "Message.hpp"
#include <unistd.h>

enum {POINT3DDef};
MsgQueue recMsg(20);

#define numOfThreads 2

struct Point3D : public Message
{
    int x;
    int y;
    int z;
};

void ReceieveHandler(unsigned id, Message* msg)
{
    switch(id){
        case POINT3DDef:
        Point3D * point = reinterpret_cast<Point3D*>(msg);
        std::cout << std::endl << "X: " << point->x << std::endl << "Y: " << point->y << std::endl << "Z: " << point->z << std::endl;
        break;    
    }
    
}

void *reciever(void*)
{
    unsigned long id;
    while(1)
    {
        Message* msg = recMsg.receive(id);
        ReceieveHandler(id, msg);
        delete(msg);
    }
}

void *sender(void*)
{
    int i = 0;
    while(1)
    {
        Point3D *point = new Point3D;


        point->x = 1+i;
        point->y = 2+i;
        point->z = 3+i;
        i++;
    
        recMsg.send(POINT3DDef,point);

        sleep(1);
    }

}


int main()
{
    pthread_t threads[numOfThreads];
    
    if(int error = pthread_create(&threads[0], NULL, reciever, (void *) NULL))
    {
        std::cout << "Error: unable to create thread: 1, error ID : " << error << std::endl;
        exit(-1);
    }
    if(int error = pthread_create(&threads[1], NULL, sender, (void *) NULL))
    {
        std::cout << "Error: unable to create thread: 2, error ID : " << error << std::endl;
        exit(-1);
    }

    for(size_t i = 0; i < numOfThreads; i++)
    {
         if(int error = pthread_join(threads[i], NULL))
        {
            std::cout << "Error: unable to join threadnr : " << i << " with error ID: " << error << std::endl;
            exit(-1);
        }
    }


    return 0;
}