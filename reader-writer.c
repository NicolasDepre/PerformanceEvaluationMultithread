#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_rwlock_t rwlock;
pthread_mutex_t mutex;
pthread_t* readers;
pthread_t* writers;
int value = 5;
int read = 0;
int written = 0;
void *work(){
    while(rand()<RAND_MAX/10000);
}
void *writing(){
    while(written<624){
        pthread_rwlock_wrlock(&rwlock);
        written++;
        pthread_rwlock_unlock(&rwlock);
        work();
    }
}
void *reading(){
    while(read<2560){
        pthread_rwlock_rdlock(&rwlock);
        read++;
        pthread_rwlock_unlock(&rwlock);
        work();
    }
}



void launch_threads(int r, int w){
    readers = malloc(sizeof(pthread_t)*r);
    writers = malloc(sizeof(pthread_t)*w);
    pthread_rwlock_init(&rwlock,NULL);
    //Launching readers
    printf("%i %i\n",r,w);
    printf("Launching writers\n");
    for(int i = 0; i<w;i++){
        pthread_create(&writers[i],NULL,writing,NULL);
        printf("Thread launched\n");
    }
    printf("Launching threads\n");
    for(int i = 0; i<r;i++){
        pthread_create(&readers[i],NULL,reading,NULL);
    }
    for(int i=0;i<w;i++){
        pthread_join(writers[i],NULL);
    }
    for(int i=0;i<r;i++){
        pthread_join(readers[r],NULL);
    }
    printf("Joined");

    //Joining threads
}

int main(int argc, char *argv[]){
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    launch_threads(a,b);
}