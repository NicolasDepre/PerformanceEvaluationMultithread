#ifndef PERFORMANCEEVALUATIONMULTITHREAD_MYSEM_H
#define PERFORMANCEEVALUATIONMULTITHREAD_MYSEM_H
typedef struct s mySem;
int mySem_init(mySem**,int);
void mySem_wait(mySem**);
void mySem_post(mySem** sem);
void mySem_destroy(mySem** sem);
#endif //PERFORMANCEEVALUATIONMULTITHREAD_MYSEM_H
