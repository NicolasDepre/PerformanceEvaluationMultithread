#include "headers/TATAS.h"

/*
 * Implémentation d'un verrou à attente active TEST AND TEST AND SET (TATAS)
 */

typedef struct sl{
    int val;        //Etat du verrou
} spinLock;

/*
 * Initiation d'un verrou à attente active
 * Malloc des variables nécessaires
 */
int spinlock_init(spinLock** lock){
    *lock = malloc(sizeof(spinLock));
    (*lock)->val=0;
    return 0;
}
/*
 * Verrouillage du verrou à attente active
 */
void spinlock_lock(spinLock** lock) {
    int i=1;
    while(i==1) {
        while((*lock)->val==1){};
        asm volatile (
        "movl $1, %%ecx\n"
        "xchgl %%ecx, %0\n"
        :"=m" ((*lock)->val),"=c" (i)
        :"m" ((*lock)->val)
        );
    }
}

/*
 * Deverrouillage du verrou à attente active
 */
void spinlock_unlock(spinLock** lock){
    int* p = &(*lock)->val;
    asm volatile (
    "movl $0, %%ecx\n"
    "xchgl %%ecx, %0\n"
    :"=m" ((*lock)->val)
    :"m" ((*lock)->val)
    :"%ecx"
    );
};


/*
 * Nettoie la structure en libérant la variable malloc
 */
void spinlock_destroy(spinLock** lock){
    free(*lock);
}
