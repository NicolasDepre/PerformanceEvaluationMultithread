//
// Created by Shadow on 11/22/2020.
//
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "headers/mySemTAS.h"
mySem* s;

void* test(){
    while(1) {
        mySem_wait(&s);
        printf("Thread en SC\n");
        sleep(2);
        printf("Thread hors SC\n");
        mySem_Post(&s);
    }
}

void launch_threads(int n){
    mySem_init(&s,1);
    pthread_t* threads = malloc(sizeof(pthread_t)*n);
    //Création des threads
    for(int i=0;i<n;i++){
        pthread_create(&threads[i],NULL,test,NULL);
    }
    //Join de l'ensemble des threads
    for(int i=0;i<n;i++){
        pthread_join(threads[i],NULL);
    }

}

int main(int argc, char *argv[]){
    int a = atoi(argv[1]);
    launch_threads(a);
    return 0;
}