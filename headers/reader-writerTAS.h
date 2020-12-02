#ifndef PERFORMANCEEVALUATIONMULTITHREAD_READER_WRITERTAS_H
#define PERFORMANCEEVALUATIONMULTITHREAD_READER_WRITERTAS_H

#include <stdlib.h>
#include <pthread.h>
#include "mySemTAS.h"
#include "TAS.h"

void work();
void* write();
void* read();
int launch_thread(int,int);
#endif //PERFORMANCEEVALUATIONMULTITHREAD_READER_WRITERTAS_H
