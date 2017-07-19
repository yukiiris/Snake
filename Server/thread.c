#include <stdio.h>
#include "queue.h"
#include <pthread.h>
#include "snake.h"
#include "function.h"

void thread(linkqueue_st* queue)
{
    while(1)
    {
        pthread_mutex_lock(&mut);
        int value = 0;
        int *p = &value;
        //printf("%d", linkqueue_isempty(queue));
        if (linkqueue_isempty(queue) != 1)
        {
            linkqueue_dequeue(queue, p);
            key_input(value);
        }
        //sleep(1);
        pthread_mutex_unlock(&mut);
    }
}

void snake(void)
{
    while (1)
    {
        play();
        sleep(2);
    }
}
