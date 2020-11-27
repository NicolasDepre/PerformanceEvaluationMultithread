//
// Created by Shadow on 11/22/2020.
//
#include "mySem.h"
#include "testAndSet.h"
#include <stdlib.h>
typedef struct s{
    int queu;
    spinLock  *l;
    spinLock *mod;
}mySem;

void mySem_init(mySem** sem,int n){
    *sem = malloc(sizeof(mySem));
    (*sem)->queu = n;
    spinlock_init(&(*sem)->mod);
    spinlock_init(&(*sem)->l);
}

void mySem_wait(mySem** sem){
    spinlock_lock(&(*sem)->l);
    while((*sem)->queu<=0){}
    spinlock_lock(&(*sem)->mod);
    (*sem)->queu --;
    spinlock_unlock(&(*sem)->mod);
    spinlock_unlock(&(*sem)->l);
}

void mySem_Post(mySem** sem){
    spinlock_lock(&(*sem)->mod);
    (*sem)->queu++;
    spinlock_unlock(&(*sem)->mod);
}