#include <iostream>
#include "MsgQueue.hpp"
#include "Message.hpp"



struct Point3D : public Message
{
    int x;
    int y;
    int z;
}

void *reciever(void* data)
{

}

void *sender(void* data)
{

}


int main()
{
    pthread_t sender;
    pthread_t reciever;



    return 0;
}