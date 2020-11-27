//
// Created by Shadow on 11/22/2020.
//

#ifndef PERFORMANCEEVALUATIONMULTITHREAD_TESTANDTESTANDSET_H
#define PERFORMANCEEVALUATIONMULTITHREAD_TESTANDTESTANDSET_H
typedef struct sl spinLock;
void spinlock_init(spinLock**);
void spinlock_lock(spinLock** lock);
void spinlock_unlock(spinLock** lock);
#endif //PERFORMANCEEVALUATIONMULTITHREAD_TESTANDTESTANDSET_H
