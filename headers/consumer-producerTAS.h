#ifndef PERFORMANCEEVALUATIONMULTITHREAD_CONSUMER_PRODUCERTAS_H
#define PERFORMANCEEVALUATIONMULTITHREAD_CONSUMER_PRODUCERTAS_H
#include <pthread.h>
#include "mySemTAS.h"
#include <stdlib.h>

#define BUFFER_SIZE  8
#define DATA_SIZE    10000

int get_random();
void *insertItem(int);
void *produce();
void *consume();
void work();
int launch_threads(int,int);
#endif //PERFORMANCEEVALUATIONMULTITHREAD_CONSUMER_PRODUCERTAS_H
