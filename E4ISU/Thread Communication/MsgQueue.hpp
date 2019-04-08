#ifndef MSGQUEUE_HPP_ // include guard
#define MSGQUEUE_HPP_
#include "Message.hpp"
#include <iostream>
#include <queue>
#include <pthread.h>
#include <utility>
#include <string>


class MsgQueue: public Message
{
public:
    MsgQueue(unsigned long maxSize);
    void send(unsigned long id, Message* msg = NULL);
    Message* receive(unsigned long& id);
    ~MsgQueue();
private:
    struct Item
    {
        unsigned long id_;
        Message* msg_;
    };
    std::queue <Item> container_;
    pthread_mutex_t lock;
    pthread_cond_t sendToQueue;
    pthread_cond_t takeFromQueue;
    unsigned long maxSize_;
  };

#endif /* Message */