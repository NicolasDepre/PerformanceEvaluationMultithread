#ifndef PERFORMANCEEVALUATIONMULTITHREAD_PHILOSOPHESTAS_H
#define PERFORMANCEEVALUATIONMULTITHREAD_PHILOSOPHESTAS_H
#include "mySemTAS.h"
#include <pthread.h>
#include <stdlib.h>

int launch_threads(int);
void take_forks(int);
void put_forks(int);
void check(int);
#endif //PERFORMANCEEVALUATIONMULTITHREAD_PHILOSOPHESTAS_H
