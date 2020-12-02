//
// Created by Shadow on 11/20/2020.
//

#ifndef PERFORMANCEEVALUATIONMULTITHREAD_TESTANDSET_H
#define PERFORMANCEEVALUATIONMULTITHREAD_TESTANDSET_H
#include <stdlib.h>
typedef struct sl spinLock;
int spinlock_init(spinLock**);
void spinlock_lock(spinLock**);
void spinlock_unlock(spinLock**);
void spinlock_destroy(spinLock**);

#endif //PERFORMANCEEVALUATIONMULTITHREAD_TESTANDSET_H
