#include "headers/reader-writersTATAS.h"


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
            sem_post(&wsem);
        }
        spinlock_unlock(&rc);
    }
}

int launch_threads(int r, int w){

    //Initialisation mutex et semaphores
    if (!(spinlock_init(&rc))) return -1;
    if (!(spinlock_init(&wc))) return -1;
    if (!(mySem_init(&rsem,1))) return -1;
    if (!(mySem_init(&wsem,1))) return -1;

    pthread_t writers[w];
    //Création des threads
    for (int i = 0; i < w; i++){
        if (pthread_create(&(writers[i]),NULL, (void *) write,NULL) != 0) return -3;
    }

    pthread_t readers[r];
    for (int i = 0; i < r; i++){
        if (pthread_create(&(readers[i]),NULL, (void *) read,NULL) != 0) return -3;
    }

    //Join des threads
    for (int i = 0; i < w; i++){
        if (pthread_join((writers[i]),NULL) != 0) return -4;
    }

    for (int i = 0; i < r; i++){
        if (pthread_join((readers[i]),NULL) != 0) return -4;
    }

    //Destruction sémaphores et mutex
    if (!(spinlock_destroy(&wc)))return -1;
    if (!(spinlock_destroy(&rc))) return -1;

    if (!(mySem_destroy(&wsem))) return -1;
    if (!(mySem_destroy(&rsem))) return -1;
    return 0;

}

int main(int argc, char *argv[]){
    if(argc != 3) return -1;
    int r = atoi((const char*) argv[1]);
    int w = atoi((const char*) argv[2]);
    return launch_threads(r,w);
}