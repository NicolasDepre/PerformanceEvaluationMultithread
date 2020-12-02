#ifndef PERFORMANCEEVALUATIONMULTITHREAD_MYSEM_H
#define PERFORMANCEEVALUATIONMULTITHREAD_MYSEM_H

#include "TAS.h"
#include <stdlib.h>

typedef struct mySem{
    int queu;       //Valeur de la sémaphore
    spinLock  *l;   //Verrou
    spinLock *mod;
} mySem;

int mySem_init(mySem**,int);
void mySem_wait(mySem**);
void mySem_post(mySem**);
void mySem_destroy(mySem**);


#endif //PERFORMANCEEVALUATIONMULTITHREAD_MYSEM_H
