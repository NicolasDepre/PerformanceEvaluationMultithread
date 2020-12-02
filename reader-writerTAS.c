#include "headers/reader-writerTAS.h"

/*
 * Implémentation du problème des lecteurs-écrivains sur base des verrous TAS.c (basé sur le code du TP)
 */
int readcount = 0;
int writecount = 0;

int rcounter=0;
int wcounter=0;

spinLock* rc;
spinLock* wc;

mySem* rsem;
mySem* wsem;

void work(){
    while (rand() > RAND_MAX/10000);
}

void* write(){
    while (1){

        spinlock_lock(&wc);
        wcounter++;
        if(wcounter > 640){
            spinlock_unlock(&wc);
            break;
        }
        writecount++;
        if (writecount == 1){
            mySem_wait(&rsem);
        }
        spinlock_unlock(&wc);

        mySem_wait(&wsem);
        work();

        mySem_post(&wsem);
        spinlock_lock(&wc);
        writecount--;
        if (writecount == 0){
            mySem_post(&rsem);
        }
        spinlock_unlock(&wc);
    }
}

void* read(){
    while (1){
        mySem_wait(&rsem);
        spinlock_lock(&rc);
        rcounter++;
        if(rcounter > 2560){
            mySem_post(&rsem);
            spinlock_unlock(&rc);
            break;
        }
        readcount++;
        if (readcount == 1){
            mySem_wait(&wsem);
        }
        spinlock_unlock(&rc);

        mySem_post(&rsem);
        work();

        spinlock_lock(&rc);
        readcount--;
        if (readcount == 0){
            mySem_post(&wsem);
        }
        spinlock_unlock(&rc);
    }
}

int launch_threads(int r, int w){

    //Initialisation mutex et semaphores
    spinlock_init(&rc);
    spinlock_init(&wc);
    mySem_init(&rsem,1);
    mySem_init(&wsem,1);

    pthread_t writers[w];
    //Création des threads
    for (int i = 0; i < w; i++){
        pthread_create(&(writers[i]),NULL, (void *) write,NULL);
    }

    pthread_t readers[r];
    for (int i = 0; i < w; i++){
        pthread_create(&(readers[i]),NULL, (void *) read,NULL);
    }

    //Join des threads
    for (int i = 0; i < r; i++){
        pthread_join((writers[i]),NULL);
    }

    for (int i = 0; i < r; i++){
        pthread_join((readers[i]),NULL);
    }

    //Destruction sémaphores et mutex
    spinlock_destroy(&wc);
    spinlock_destroy(&rc);

    mySem_destroy(&wsem);
    mySem_destroy(&rsem);
    return 0;

}

int main(int argc, char *argv[]){
    if(argc != 3) return -1;
    int r = atoi((const char*) argv[1]);
    int w = atoi((const char*) argv[2]);
    return launch_threads(r,w);
}