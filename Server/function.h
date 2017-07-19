#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED
#include "queue.h"
int server(void);
void snake(void);
void thread(linkqueue_st* queue);
pthread_mutex_t mut;
#endif // FUNCTION_H_INCLUDED
