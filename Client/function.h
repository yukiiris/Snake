#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>

#define BUFLEN 1024
#define PORT 6666

int sockfd;
struct sockaddr_in s_addr;
socklen_t len;
unsigned int port;
char buf[BUFLEN];
fd_set rfds;
struct timeval tv;
int retval, maxfd;

//void thread(void);
void init_keyboard(void);
int kbhit();
int client(void);
int readch();
#endif // FUNCTION_H_INCLUDED
