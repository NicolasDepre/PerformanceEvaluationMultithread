#ifndef PERFORMANCEEVALUATIONMULTITHREAD_READER_WRITER_H
#define PERFORMANCEEVALUATIONMULTITHREAD_READER_WRITER_H

#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

void work();
void* write();
void* read();
int launch_thread(int,int);

#endif //PERFORMANCEEVALUATIONMULTITHREAD_READER_WRITER_H
