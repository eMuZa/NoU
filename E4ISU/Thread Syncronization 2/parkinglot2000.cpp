#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t Entry_cVar = PTHREAD_COND_INITIALIZER;
pthread_cond_t Exit_cVar = PTHREAD_COND_INITIALIZER;

void openGarEntryDoor(void);
void closeGarEntryDoor(void);
void closeGarExitDoor(void);
void openGarExitDoor(void);

#define NumOfCars 4

int maxTime = 5;
int minTime = 1;

bool isEntryDoorOpen = false;
bool isExitDoorOpen = false;
bool isCarWaitingEntry = false;
bool isCarWaitingExit = false;

void *carThread(void *vari)
{
    uint16_t carNbr = *static_cast<uint16_t *>(vari);
    while(1)
    {  

    pthread_mutex_lock(&lock);
    isCarWaitingEntry = true;
    pthread_cond_signal(&Entry_cVar);
    while(isEntryDoorOpen==false)
    {
        pthread_cond_wait(&Entry_cVar, &lock);
    }
    std::cout<<"Entering parking lot from door 1 - Car ID: "<< carNbr << std::endl;
    isCarWaitingEntry = false;
    pthread_cond_signal(&Entry_cVar);
    pthread_mutex_unlock(&lock);

    int timeWait = rand() % maxTime + minTime;
    std::cout<<"Car number:" << carNbr << " waiting for " << timeWait << " seconds" << std::endl;
    sleep(timeWait);

    pthread_mutex_lock(&lock);
    isCarWaitingExit = true;
    pthread_cond_signal(&Exit_cVar);
    while(isExitDoorOpen==false)
    {
        pthread_cond_wait(&Exit_cVar, &lock);
    }
    std::cout<<"Exiting parking lot from door 2 - Car ID: "<< carNbr << std::endl;
    isCarWaitingExit = false;
    pthread_cond_signal(&Exit_cVar);
    pthread_mutex_unlock(&lock);

    sleep(1);
    }
}

void *PLCS_ENTRY_GUARD(void *vari)
{
    while(1)
    {
    pthread_mutex_lock(&lock);
    while(isCarWaitingEntry == false)
    {
        pthread_cond_wait(&Entry_cVar, &lock);
    }
    openGarEntryDoor();

    pthread_cond_signal(&Entry_cVar);
    while(isCarWaitingEntry == true)
    {
        pthread_cond_wait(&Entry_cVar, &lock);
    }
    closeGarEntryDoor();
    pthread_cond_signal(&Entry_cVar);
    pthread_mutex_unlock(&lock);
    std::cout << std::endl;
    }
}

void *PLCS_EXIT_GUARD(void *vari)
{
    while(1)
    {
    pthread_mutex_lock(&lock);
    while(isCarWaitingExit == false)
    {
        pthread_cond_wait(&Exit_cVar, &lock);
    }
    openGarExitDoor();

    pthread_cond_signal(&Exit_cVar);
    while(isCarWaitingExit == true)
    {
        pthread_cond_wait(&Exit_cVar, &lock);
    }
    closeGarExitDoor();
    pthread_cond_signal(&Exit_cVar);
    pthread_mutex_unlock(&lock);
    std::cout << std::endl;
    }
}

void openGarEntryDoor(void)
{
    isEntryDoorOpen = true;
    std::cout<<"Garage Entry Door is open" << std::endl;
}

void openGarExitDoor(void)
{
    isExitDoorOpen = true;
    std::cout<<"Garage Exit Door is open" << std::endl;
}

void closeGarEntryDoor(void)
{
    isEntryDoorOpen = false;
    std::cout<<"Garage Entry Door is closed" << std::endl;
}

void closeGarExitDoor(void)
{
    isExitDoorOpen = false;
    std::cout<<"Garage Exit Door is close" << std::endl;
}

int main()
{
    pthread_t threads[2];
    pthread_t carThreads[NumOfCars];
    srand(time(NULL));

    int ids[NumOfCars];

    if(int error = pthread_create(&threads[0], NULL, PLCS_ENTRY_GUARD, (void *) NULL))
    {
        std::cout << "Error: unable to create thread: 1, error ID : " << error << std::endl;
        exit(-1);
    }
    if(int error = pthread_create(&threads[1], NULL, PLCS_EXIT_GUARD, (void *) NULL))
    {
        std::cout << "Error: unable to create thread: 2, error ID : " << error << std::endl;
        exit(-1);
    }
    
    for(size_t i = 0; i < NumOfCars; i++)
    {
        ids[i] = i;
         if(int error = pthread_create(&carThreads[i], NULL, carThread, (void *) &ids[i]))
        {
            std::cout << "Error: unable to create carthreadnr : " << i << " with error ID: " << error << std::endl;
            exit(-1);
        }
    }
    
        for(size_t i = 0; i < NumOfCars; i++)
    {
         if(int error = pthread_join(carThreads[i], NULL))
        {
            std::cout << "Error: unable to join carthreadnr : " << i << " with error ID: " << error << std::endl;
            exit(-1);
        }
    }

}