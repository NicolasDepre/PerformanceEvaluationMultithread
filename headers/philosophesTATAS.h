#ifndef PERFORMANCEEVALUATIONMULTITHREAD_PHILOSOPHESTATAS_H
#define PERFORMANCEEVALUATIONMULTITHREAD_PHILOSOPHESTATAS_H

#include <pthread.h>
#include "mySemTATAS.h"
#include <stdlib.h>

int launch_threads(int);
void take_forks(int);
void put_forks(int);
void check(int);
#endif //PERFORMANCEEVALUATIONMULTITHREAD_PHILOSOPHESTATAS_H
