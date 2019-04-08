    #include "MsgQueue.hpp"
    #include "map"

    
    MsgQueue::MsgQueue(unsigned long maxSize)
    {
        lock = PTHREAD_MUTEX_INITIALIZER;
        takeFromQueue = PTHREAD_COND_INITIALIZER;
        sendToQueue = PTHREAD_COND_INITIALIZER;
        maxSize_ = maxSize;
    }
    void MsgQueue::send(unsigned long id, Message* msg)
    {
        pthread_mutex_lock(&lock);
        
        while(container_.size()>=maxSize_)
        {
            pthread_cond_wait(&sendToQueue, &lock);
        }

        container_.emplace(Item{id, msg});
        pthread_cond_signal(&takeFromQueue);
        
        pthread_mutex_unlock(&lock);
    }
    Message* MsgQueue::receive(unsigned long& id)
    {
        pthread_mutex_lock(&lock);

        while(container_.empty())
        {
            pthread_cond_wait(&takeFromQueue, &lock);
        }

        unsigned long int idIntern = container_.front().id_;
        Message* msgIntern = container_.front().msg_;

       

        container_.pop();
        pthread_cond_signal(&sendToQueue);
        pthread_mutex_unlock(&lock);

        return msgIntern;
    }
    MsgQueue::~MsgQueue()
    {

    }