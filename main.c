#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <pthread.h> 
#include <assert.h> 
#include <string.h>

#include "threadpool.h"


void * thread_1(void * arg);
void * thread_2(void * arg);
void * thread_3(void * arg);
void DisplayPoolStatus(CThread_pool_t * pPool);

int nKillThread = 0;
static int nCount = 0;

int main()
{
    CThread_pool_t * pThreadPool = NULL;
    
    pThreadPool = ThreadPoolConstruct(5, 1);
    int nNumInput = 5;
    char LogInput[] = "OK!";

    DisplayPoolStatus(pThreadPool);

    while(1)
    {
    	pThreadPool->AddWorkUnlimit((void *)pThreadPool, (void *)thread_1, (void *)NULL);
        sleep(4);
    	DisplayPoolStatus(pThreadPool);
    }

    pThreadPool->Destroy((void*)pThreadPool);
    return 0;
}

void * 
thread_1(void * arg)
{
    printf("Thread %d is running !\n", nCount++);
    sleep(5);
    printf("sleep 5");

    return NULL;
}

void * 
thread_2(void * arg)
{
    int nNum = (int)arg;
    
    printf("Thread 2 is running !\n");
    printf("Get Number %d\n", nNum);
    while(nKillThread != 2)
        usleep(10);
    return NULL;
}

void * 
thread_3(void * arg)
{
    char * pLog = (char *)arg;
    
    printf("Thread 3 is running !\n");
    printf("Get String %s\n", pLog);
    while(nKillThread != 3)
        usleep(10);
    return NULL;
}

void 
DisplayPoolStatus(CThread_pool_t * pPool)
{
    static int nCount = 1;
    
    printf("****************************\n");
    printf("nCount = %d\n", nCount++);
    printf("max_thread_num = %d\n", pPool->GetThreadMaxNum((void *)pPool));
    printf("current_pthread_num = %d\n", pPool->GetCurrentThreadNum((void *)pPool));
    printf("current_pthread_task_num = %d\n", pPool->GetCurrentTaskThreadNum((void *)pPool));
    printf("current_wait_queue_num = %d\n", pPool->GetCurrentWaitTaskNum((void *)pPool));
    printf("****************************\n");
}
