//
// Created by Shadow on 11/21/2020.
//
#include "TestAndTestAndSet.h"
#include <stdlib.h>
#include <pthread.h>
int counter = 6400;
spinLock* l;
typedef struct{
    pthread_t thread;
    int counter;
    int id;
}ThreadC;
ThreadC* threads;
void work(){
    while(rand()>RAND_MAX/10000);
}
void* test(void* i){
    ThreadC t = threads[*((int*)i)];
    while(1){
        spinlock_lock(&l);
        if(t.counter==0){
            spinlock_unlock(&l);
            break;
        }
        work();
        t.counter--;
        spinlock_unlock(&l);

    }
}
void launch_threads(int n){
    spinlock_init(&l);
    threads = malloc(sizeof(ThreadC)*n);
    //Création des threads
    for(int i=0;i<n;i++){
        pthread_create(&(threads[i].thread),NULL,test,&(threads[i].id));
        threads[i].counter= 6400/n;
        threads[i].id = i;
    }
    //Join de l'ensemble des threads
    for(int i=0;i<n;i++){
        pthread_join(threads[i].thread,NULL);
    }

}

int main(int argc, char *argv[]){
    int a = atoi(argv[1]);
    launch_threads(a);
    return 0;
}