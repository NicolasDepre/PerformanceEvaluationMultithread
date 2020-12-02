#include "headers/consumer-producer.h"

/*
 * Implémentation du problème des producteurs-consommateurs
 */

pthread_t *producers;
pthread_t * consumers;

sem_t full, empty,mutex;

int *buffer; // 8
int consumed = DATA_SIZE; //10 000
int produced = DATA_SIZE; //10 000
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
        sem_wait(&full); //Il y a une place de moins de disponible dans le buffer;
        sem_wait(&mutex);
        if(produced==0){
            sem_post(&full);
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
    while(1){
        sem_wait(&empty);
        sem_wait(&mutex);
        if(consumed==0){
            sem_post(&empty);
            sem_post(&full);
            sem_post(&mutex);
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
    while(rand()>RAND_MAX/10000);
}


int launch_threads(int prods, int cons){

    //Malloc les tableaux
    if(!(producers = malloc(sizeof(pthread_t)*prods)))return -1;
    if(!(consumers = malloc(sizeof(pthread_t)*cons)))return -1;
    if(!(buffer = malloc(sizeof(int)*BUFFER_SIZE)))return -1;

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

     //Destroy and free variable
     sem_destroy(&empty);
     sem_destroy(&full);
     free(producers);
     free(consumers);
     return 0;
}

int main(int argc, char *argv[]){
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    launch_threads(a,b);
}