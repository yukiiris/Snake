#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <curses.h>
#include <sys/time.h>
#include "function.h"
#include "queue.h"
#include "snake.h"

#define BUFLEN 1024
#define PORT 6666
#define LISTNUM 20


int server(void)
{
    int sockfd, newfd;
    struct sockaddr_in s_addr, c_addr;
    char buf[BUFLEN];
    socklen_t len;
    unsigned int port, listnum;
    fd_set rfds;
    struct timeval tv;
    int retval,maxfd;
    linkqueue_st *queue = linkqueue_init(100);
    if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(errno);
    }else
        printf("socket create success!\n");
    memset(&s_addr,0,sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = htons(INADDR_ANY);


    if((bind(sockfd, (struct sockaddr*) &s_addr,sizeof(struct sockaddr))) == -1){
        perror("bind");
        exit(errno);
    }else
        printf("bind success!\n");

    if(listen(sockfd,listnum) == -1){
        perror("listen");
        exit(errno);
    }else
        printf("the server is listening!\n");

    pthread_t id1, id2;
    int i, ret;
    ret = pthread_create(&id1, NULL, (void *) thread, queue);
    //pthread_create(&id2, NULL, (void *) snake, NULL);
    initscr();

    while(1){
        printf("start\n");
        len = sizeof(struct sockaddr);

        if((newfd = accept(sockfd,(struct sockaddr*) &c_addr, &len)) == -1){
            perror("accept");
            exit(errno);
        }else
        {
            pthread_create(&id2, NULL, (void *) snake, NULL);
        }

        while(1){
            FD_ZERO(&rfds);
            FD_SET(0, &rfds);
            maxfd = 0;
            FD_SET(newfd, &rfds);
            if(maxfd < newfd)
                maxfd = newfd;

            tv.tv_sec = 6;
            tv.tv_usec = 0;

            retval = select(maxfd+1, &rfds, NULL, NULL, &tv);
            if(retval == -1){
                //break;
            }else if(retval == 0){
                //continue;
            }else{

                bzero(buf,1);
                if((buf[0] = getch()) > 0){
                if (buf[0] == 'W' || buf[0] == 'S' || buf[0] == 'A' || buf[0] == 'D')
                {
                    //
                    //if(len > 0)
                    //printf("success%s\n",buf);
//                else{
//                    printf("failed!\n");
//                    break;
//                }
                }
                else if (buf[0] == 'U' || buf[0] == 'J' || buf[0] == 'K' || buf[0] == 'H')
                {
                    key_input(buf[0]);
                    len = send(newfd,buf,1,0);
//                    if (len > 0)
//                    {
//                        printf("111");
//                    }
                }



            }
                if(FD_ISSET(newfd, &rfds)){
                    memset(buf,0,sizeof(buf));
                    len = recv(newfd,buf,BUFLEN,0);
                    if(len > 0)
                    {
                        //printf("msg:%s\n",buf);
                        linkqueue_enqueue(queue, buf[0]);
                        //send(newfd, server, strlen(server), 0);
                        //send(newfd, buf, strlen(buf), 0);
                    }

                    else{
                        if(len < 0 )
                            printf("failed\n");
                        else
                        break;
                    }
                }
            }
        }
        close(newfd);

    }
    endwin();
    close(sockfd);
    return 0;
}
