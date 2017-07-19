#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include "function.h"
#include <termios.h>
#include <assert.h>
#include <curses.h>

#define BUFLEN 1
#define PORT 6666

void thread(void);

int client(void)
{
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(errno);
    }else
        printf("socket create success!\n");



    memset(&s_addr,0,sizeof(s_addr));
    s_addr.sin_family = AF_INET;
     s_addr.sin_port = htons(PORT);
    if (inet_aton("127.0.0.1", (struct in_addr *)&s_addr.sin_addr.s_addr) == 0) {
        perror("port");
        exit(errno);
    }

    if(connect(sockfd,(struct sockaddr*)&s_addr,sizeof(struct sockaddr)) == -1){
        perror("connect");
        exit(errno);
    }else
        printf("conncet success!\n");

//    pthread_t id;
//    int i, ret;
//    ret = pthread_create(&id, NULL, (void *) thread, NULL);
	init();
	draw(0);
	draw(1);

   initscr();

    while(1){
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        maxfd = 0;
        FD_SET(sockfd, &rfds);
        if(maxfd < sockfd)
            maxfd = sockfd;
        tv.tv_sec = 6;
        tv.tv_usec = 0;
        retval = select(maxfd+1, &rfds, NULL, NULL, &tv);
        if(retval == -1){

            break;
        }else if(retval == 0){
            //printf("waiting...\n");
            continue;
        }else{

                bzero(buf,1);
                if((buf[0] = getch()) > 0){
                if (buf[0] == 'W' || buf[0] == 'S' || buf[0] == 'A' || buf[0] == 'D'
                    || buf[0] == 'U' || buf[0] == 'H' || buf[0] == 'J' || buf[0] == 'K')
                {
                    len = send(sockfd,buf,strlen(buf),0);
                    //if(len > 0)
                    //printf("success%s\n",buf);
//                else{
//                    printf("failed!\n");
//                    break;
//                }
                }



            }
        }

    }
    endwin();
    close(sockfd);

    return 0;
}
