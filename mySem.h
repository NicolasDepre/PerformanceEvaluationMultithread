//
// Created by Shadow on 11/22/2020.
//

#ifndef PERFORMANCEEVALUATIONMULTITHREAD_MYSEM_H
#define PERFORMANCEEVALUATIONMULTITHREAD_MYSEM_H
typedef struct s mySem;
void mySem_init(mySem**,int);
void mySem_wait(mySem**);
void mySem_Post(mySem** sem);
#endif //PERFORMANCEEVALUATIONMULTITHREAD_MYSEM_H
