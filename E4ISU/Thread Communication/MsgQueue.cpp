    #include "MsgQueue.hpp"
    
    MsgQueue::MsgQueue(unsigned long maxSize)
    {
        lock = PTHREAD_MUTEX_INITIALIZER;
        takeFromQueue = PTHREAD_COND_INITIALIZER;
        sendToQueue = PTHREAD_COND_INITIALIZER;
        maxSize_ = maxSize;
    }
    void MsgQueue::send(unsigned long id, Message* msg = nullptr)
    {
        pthread_mutex_lock(&lock);

        container_.emplace(msg, id);
        
        while(container_.size()>=maxSize_)
        {
            pthread_cond_wait(&sendToQueue, &lock);
        }

        container_.push(Item);
        pthread_cond_signal(&takeFromQueue);
        
        pthread_mutex_unlock(&lock);
    }
    Message* MsgQueue::receive(unsigned long& id)
    {
        pthread_mutex_lock(&lock);

        while(cotainer_.empty())
        {
            pthreadd_cond_wait(&takeFromQueue, &lock);
        }

        Item.msg_ = container_.first();
        Item.id_ = container_.second();

        id = Item.id_;

        container_.pop();
        pthread_cond_signal(&sendToQueue);
        pthread_mutex_unlock(&lock);

        return Item.msg_;
    }
    MsgQueue::~MsgQueue()
    {

    }