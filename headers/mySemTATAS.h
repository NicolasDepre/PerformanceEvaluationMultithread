#ifndef PERFORMANCEEVALUATIONMULTITHREAD_MYSEMTATAS_H
#define PERFORMANCEEVALUATIONMULTITHREAD_MYSEMTATAS_H

#include "TATAS.h"
#include <stdlib.h>

typedef struct mySem{
    int queu;       //Valeur de la sémaphore
    spinLock  *l;   //Verrou
    spinLock *mod;
}mySem;
int mySem_init(mySem**,int);
void mySem_wait(mySem**);
void mySem_post(mySem** sem);
void mySem_destroy(mySem** sem);
#endif //PERFORMANCEEVALUATIONMULTITHREAD_MYSEMTATAS_H
