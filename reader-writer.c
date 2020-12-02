#include "headers/reader-writer.h"

/*
 * Implémentation du problème des lecteurs-écrivains (basé sur le code du TP)
 */
int readcount = 0;
int writecount = 0;

int rcounter=0;
int wcounter=0;

pthread_mutex_t rc;
pthread_mutex_t wc;

sem_t rsem;
sem_t wsem;

void work(){
    while (rand() > RAND_MAX/10000);
}

void* write(){
    while (1){

        pthread_mutex_lock(&wc);
        wcounter++;
        if(wcounter > 640){
            pthread_mutex_unlock(&wc);
            break;
        }
        writecount++;
        if (writecount == 1){
            sem_wait(&rsem);
        }
        pthread_mutex_unlock(&wc);

        sem_wait(&wsem);
        work();

        sem_post(&wsem);
        pthread_mutex_lock(&wc);
        writecount--;
        if (writecount == 0){
            sem_post(&rsem);
        }
        pthread_mutex_unlock(&wc);
    }
}

void* read(){
    while (1){
        sem_wait(&rsem);
        pthread_mutex_lock(&rc);
        rcounter++;
        if(rcounter > 2560){
            sem_post(&rsem);
            pthread_mutex_unlock(&rc);
            break;
        }
        readcount++;
        if (readcount == 1){
            sem_wait(&wsem);
        }
        pthread_mutex_unlock(&rc);

        sem_post(&rsem);
        work();

        pthread_mutex_lock(&rc);
        readcount--;
        if (readcount == 0){
            sem_post(&wsem);
        }
        pthread_mutex_unlock(&rc);
    }
}

int launch_threads(int r, int w){

    //Initialisation mutex et semaphores
    pthread_mutex_init(&rc,NULL);
    pthread_mutex_init(&wc, NULL);
    sem_init(&rsem, 0, 1);
    sem_init(&wsem, 0, 1);

    pthread_t writers[w];
    //Création des threads
    for (int i = 0; i < w; i++){
        pthread_create(&(writers[i]),NULL, (void *) write,NULL);
    }

    pthread_t readers[r];
    for (int i = 0; i < r; i++){
        pthread_create(&(readers[i]),NULL, (void *) read,NULL);
    }

    //Join des threads
    for (int i = 0; i < w; i++){
        pthread_join((writers[i]),NULL);
    }

    for (int i = 0; i < r; i++){
        pthread_join((readers[i]),NULL);
    }

    //Destruction sémaphores et mutex
    pthread_mutex_destroy(&wc);
    pthread_mutex_destroy(&rc);
    sem_destroy(&wsem);
    sem_destroy(&rsem);
    return 0;

}

int main(int argc, char *argv[]){
    if(argc != 3) return -1;
    int r = atoi((const char*) argv[1]);
    int w = atoi((const char*) argv[2]);
    return launch_threads(r,w);
}