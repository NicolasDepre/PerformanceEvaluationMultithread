#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

//=== INITIALISATION DES VARIABLES GLOBALES ===

int R;
int W;
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
int init(){
    
    if (pthread_mutex_init(&rc,NULL) != 0) return -1;
    if (pthread_mutex_init(&wc, NULL) != 0) return -1;


    if (sem_init(&rsem, 0, 1) != 0) return -1;
    if (sem_init(&wsem, 0, 1) != 0) return -1;
    return 0;
}


void write(){
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

void read(){
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

int main(int argc, char *argv[]){


    if (argc != 3){
        return -1;}

    if (init() != 0){
        return -2;}

    int number_writer = atoi((const char*) argv[1]);
    int number_reader = atoi((const char*) argv[2]);
    
    W = number_writer;
    R = number_reader;

    pthread_t writer[number_writer];
    for (int i = 0; i < number_writer; i++){
        if (pthread_create(&(writer[i]),NULL, (void *) &write,NULL) != 0) return -3;
    }

    pthread_t reader[number_reader];
    for (int i = 0; i < number_reader; i++){
        if (pthread_create(&(reader[i]),NULL, (void *) &read,NULL) != 0) return -3;
    }

    for (int i = 0; i < number_writer; i++){
        if (pthread_join((writer[i]),NULL) != 0) return -4;
    }

    for (int i = 0; i < number_reader; i++){
        if (pthread_join((reader[i]),NULL) != 0) return -4;
    }
    if (pthread_mutex_destroy(&wc) != 0) return -5;
    if (pthread_mutex_destroy(&rc) != 0) return -5;

    if (sem_destroy(&wsem) != 0) return -6;
    if (sem_destroy(&rsem) != 0) return -6;
    return 0;

}