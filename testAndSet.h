//
// Created by Shadow on 11/20/2020.
//

#ifndef PERFORMANCEEVALUATIONMULTITHREAD_TESTANDSET_H
#define PERFORMANCEEVALUATIONMULTITHREAD_TESTANDSET_H
typedef struct sl spinLock;
void spinlock_init(spinLock**);
void spinlock_lock(spinLock** lock);
void spinlock_unlock(spinLock** lock);

#endif //PERFORMANCEEVALUATIONMULTITHREAD_TESTANDSET_H
