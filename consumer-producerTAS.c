#include "headers/consumer-producerTAS.h"
#include <stdio.h>
/*
 * Implémentation du problème des producteurs-consommateurs avec verrous TAS
 */

//pthread_mutex_t mutex;
pthread_t *producers;
pthread_t * consumers;

mySem* full, *empty,*mutex;

int *buffer;
int consumed = DATA_SIZE;
int produced = DATA_SIZE;
int iIndex =0;
int rIndex =0;

//Return un random entre -MAX_INT et MAX_INT
int get_random(){
    int i = rand();
    if(i%2){
        return i-1;
    }return i;
}

//Insère item dans le buffer à un place libre
void *insertItem(int item){
    buffer[iIndex%BUFFER_SIZE]=item;
    iIndex++;
}

//Supprime un élément du buffer
void delete(){
    buffer[rIndex%BUFFER_SIZE]=0;
    rIndex++;
}

//Point d'entrée pour les threads producers
void *produce(){
    while(1) {
        int item = get_random();
        mySem_wait(&full); //Il y a une place de moins de disponible dans le buffer;
        mySem_wait(&mutex);
        if(produced==0){
            mySem_post(&full);
            mySem_post(&empty);
            mySem_post(&mutex);
            break;
        }
        insertItem(item);
        produced--;
        //printf("Prod: %i\n",produced);
        //Les consumers ont des données à consomer
        mySem_post(&mutex);
        mySem_post(&empty);

        work();
    }
}

//Point d'entrée pour les threads consumers
void *consume(){
    while(1){
        mySem_wait(&empty);
        mySem_wait(&mutex);
        if(consumed==0){
            mySem_post(&empty);
            mySem_post(&full);
            mySem_post(&mutex);
            break;
        }
        //printf("Cons: %i\n",consumed);
        consumed--;
        delete();
        mySem_post(&full);
        mySem_post(&mutex);
        work();
    }
}

//Simule un traitement utilisant le CPU
void work(){
    while(rand()>RAND_MAX/10000);
}


int launch_threads(int prods, int cons){

    //Malloc les tableaux
    if(!(producers = malloc(sizeof(pthread_t)*prods)))return -1;
    if(!(consumers = malloc(sizeof(pthread_t)*cons)))return -1;
    if(!(buffer = malloc(sizeof(int)*BUFFER_SIZE)))return -1;

    //Initiation des mutex et sémaphores
    mySem_init(&mutex,1);
    mySem_init(&empty,0);
    mySem_init(&full,BUFFER_SIZE);

    //Producers Threads
    for(int i=0;i<prods;i++){
        pthread_create(&producers[i],NULL,produce,NULL);
    }
    //Consumers Threads
    for(int i=0;i<cons;i++){
        pthread_create(&consumers[i],NULL,consume,NULL);
    }

    //Join threads
    for(int i=0;i<prods;i++){
        printf("Joined 1\n");
        pthread_join(producers[i],NULL);
    }
    for(int i=0;i<cons;i++){
        printf("Joined 2\n");
        pthread_join(consumers[i],NULL);

    }

    //Destroy and free variable
    mySem_destroy(&empty);
    mySem_destroy(&full);
    free(producers);
    free(consumers);
    return 0;
}

int main(int argc, char *argv[]){
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    launch_threads(a,b);
    return 0;
}