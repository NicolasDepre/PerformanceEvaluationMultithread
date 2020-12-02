#ifndef PERFORMANCEEVALUATIONMULTITHREAD_TESTANDTESTANDSET_H
#define PERFORMANCEEVALUATIONMULTITHREAD_TESTANDTESTANDSET_H
#include <stdlib.h>
typedef struct sl spinLock;
int spinlock_init(spinLock**);
void spinlock_lock(spinLock** lock);
void spinlock_unlock(spinLock** lock);
void spinlock_destroy(spinLock** lock);
#endif //PERFORMANCEEVALUATIONMULTITHREAD_TESTANDTESTANDSET_H
