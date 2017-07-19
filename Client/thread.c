#include "queue.h"

void thread(int sockfd, linkqueue_st *queue)
{
    char buf[1];
    int len;
    while (1)
    {
        bzero(buf,1);
        len = recv(sockfd,buf,1,0);
        if(len > 0)
        {
            linkqueue_enqueue(queue, buf[0]);
        }
        else{
            if(len < 0 )
                printf("failed\n");
            else

        break;
        }
    }
}

void snake(void)
{
    while (1)
    {
        play();
        sleep(0.5);
    }
}
