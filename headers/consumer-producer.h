//
// Created by Shadow on 11/13/2020.
//

#ifndef PERFORMANCEEVALUATIONMULTITHREAD_CONSUMER_PRODUCER_H
#define PERFORMANCEEVALUATIONMULTITHREAD_CONSUMER_PRODUCER_H

#endif //PERFORMANCEEVALUATIONMULTITHREAD_CONSUMER_PRODUCER_H
int get_random();
void *insertItem(int);
void *produce();
void *consume();
void work();
int launch_threads(int,int);
