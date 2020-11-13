//
// Created by Shadow on 11/13/2020.
//

#include "consumer-producer.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BUFFER_SIZE  8
#define DATA_SIZE    1024

pthread_mutex_t mutex;
sem_t full, empty;
pthread_t *producers;
pthread_t * consumers;
int buffer[BUFFER_SIZE];
int consumed = DATA_SIZE;
int produced = DATA_SIZE;
int iIndex =0;
int rIndex =0;

/*
 * Génère des entiers aléatoires compris entre MIN_INT et MAX_INT
 * Les nombres générés sont les mêmes à chaque éxécution
 */
int get_random(){
    if(rand()%2){
        return rand()*-1;
    }return rand();
}

void insertItem(int item){
    buffer[iIndex%BUFFER_SIZE]=item;
    iIndex++;

}
void delete(){
    buffer[rIndex%BUFFER_SIZE]=0;
    rIndex++;
}


void produce(){
    while(produced!=0) {
        int item = get_random();
        sem_wait(&full); //Il y a une place de moins de disponible dans le buffer;
        pthread_mutex_lock(&mutex);
        //INSERT ITEM
        produced--;
        pthread_mutex_unlock(&mutex);
        sem_post(full); //Les consommateurs ont des données à consomer
        work();
    }
}


void consume(){

    while(consumed!=0){
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        //Proceed Value;
        consumed--;
        pthread_mutex_unlock(&mutex):
        work();
    }


}

/*
 * Simule un traitement utilisant le CPU
 */
void work(){
    while(rand() > RAND_MAX/10000);
}


 int launch_threads(int prods, int cons){

    //Malloc les tableaux
    producers = malloc(sizeof(pthread_t)*prods);
    consumers = malloc(sizeof(pthread_t)*cons);

    //Initiation des mutex et sémaphores
    pthread_mutex_init(&mutex,NULL);
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

    //Join les threads
     for(int i=0;i<prods;i++){
         pthread_join(producers[i],NULL);
     }
     for(int i=0;i<cons;i++){
         pthread_join(consumers[i],NULL);
     }
     //Free les malloc
     free(producers);
     free(consumers);
     return 0;

}

int main(int argc, char *argv[]){
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    launch_threads(a,b);
}