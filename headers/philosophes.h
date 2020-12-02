#ifndef PERFORMANCEEVALUATIONMULTITHREAD_PHILOSOPHES_H
#define PERFORMANCEEVALUATIONMULTITHREAD_PHILOSOPHES_H
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>


int launch_threads(int);
void take_forks(int);
void put_forks(int);
void check(int);
#endif //PERFORMANCEEVALUATIONMULTITHREAD_PHILOSOPHES_H


