//
// Created by Shadow on 12/2/2020.
//

#ifndef PERFORMANCEEVALUATIONMULTITHREAD_READER_WRITERSTATAS_H
#define PERFORMANCEEVALUATIONMULTITHREAD_READER_WRITERSTATAS_H

#include <stdlib.h>
#include <pthread.h>
#include "mySemTATAS.h"
#include "TATAS.h"

void work();
void* write();
void* read();
int launch_thread(int,int);

#endif //PERFORMANCEEVALUATIONMULTITHREAD_READER_WRITERSTATAS_H
