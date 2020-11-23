//
// Created by Shadow on 11/20/2020.
//

#include "testAndSet.h"
#include <stdlib.h>
typedef struct sl{
    int val;
} spinLock;

void spinlock_init(spinLock** lock){
    *lock = malloc(sizeof(spinLock));
    (*lock)->val=0;
}
void spinlock_lock(spinLock** lock) {
    int i=1;
    while(i==1) {
        asm volatile (
             "movl $1, %%ecx\n"
             "xchgl %%ecx, %0\n"
        :"=m" ((*lock)->val),"=c" (i)
        :"m" ((*lock)->val)
        );
    }

}
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
