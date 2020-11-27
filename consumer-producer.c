//
// Created by Shadow on 11/13/2020.
//
#include "consumer-producer.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE  8
#define DATA_SIZE    10000

//pthread_mutex_t mutex;
pthread_t *producers;
pthread_t * consumers;

sem_t full, empty,mutex;

int buffer[BUFFER_SIZE];            
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

//Insère @item dans le buffer 
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
    while(consumed!=0) {
        int item = get_random();
        sem_wait(&full); //Il y a une place de moins de disponible dans le buffer;
        sem_wait(&mutex);
        if(produced==0){
            sem_post(&empty);
            sem_post(&mutex);
            break;
        }
        insertItem(item);
        produced--;
        //printf("Prod: %i\n",produced);
         //Les consumers ont des données à consomer
        sem_post(&mutex);
        sem_post(&empty); 
       
        work();
    }
}

//Point d'entrée pour les threads consumers
void *consume(){
    while(consumed!=0){
        sem_wait(&empty);
        sem_wait(&mutex);
        if(consumed==0){
            sem_post(&mutex);
            sem_post(&full);
            break;
        }
        //printf("Cons: %i\n",consumed);
        consumed--;
        delete();
        sem_post(&full);
        sem_post(&mutex);
        work();
    }
}

//Simule un traitement utilisant le CPU
void work(){
    //printf("WORKKKK\n");
    while(rand()>RAND_MAX/10000);
    //sleep(1);
    //printf("END WORKING\n");
}


int launch_threads(int prods, int cons){

    //Malloc les tableaux
    producers = malloc(sizeof(pthread_t)*prods);
    consumers = malloc(sizeof(pthread_t)*cons);
    //buffer = malloc(sizeof(int)*BUFFER_SIZE);

    //Initiation des mutex et sémaphores
    sem_init(&mutex,0,1);
    sem_init(&empty,0,0);       //Opposé aux slides mais me semble plus logique
    sem_init(&full,0,BUFFER_SIZE);

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
         pthread_join(producers[i],NULL);
     }
     for(int i=0;i<cons;i++){
         pthread_join(consumers[i],NULL);

     }

     //TODO Clean mutex and semaphores
     sem_destroy(&empty);
     sem_destroy(&full);
     free(producers);
     free(consumers);
     printf("Exécution terminée avec %i données consommées et %i données produites\n",DATA_SIZE-consumed,DATA_SIZE-produced);
     return 0;
}

int main(int argc, char *argv[]){
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    launch_threads(a,b);
}