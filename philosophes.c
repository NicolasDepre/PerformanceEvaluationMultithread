//
// Created by Shadow on 11/12/2020.
//

#include "philosophes.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ITTERATIONS 10000  //Nombre d'opérations manger/penser effectuées par chaque philosophe

//Structure qui reprend les 3 états possibles d'un philosophe
typedef enum st {THINKING=0, HUNGRY=1,EATING=2} state;

/*Structure qui représente un philosophe
 * @id: ID du philosophe
 * @counter: Nombre d'opérations effectuées par le philosophe
 * @State: Status dans lequel se trouve le philosophe
*/
typedef struct phil_struct{
    int id;
    int counter;
    state state;

} philosophe;

int n;              //@n: Nombre de philosophes
sem_t semaphore;    //@semaphore: Sémaphore globale
philosophe* phils;  //@phils: Tableau de type philosophe
sem_t* sems;        //Tableau de sémaphores


/*
 * Point d'entré des threads
 * @arg: Pointer vers l'id du philosophe
 * Le philosophe avec l'id défini par arg a effectué ITTERATIONS cycle
 */
void *philosophing(void *arg){
    int *i = (int*) arg;
    while((&phils[*i])->counter<=ITTERATIONS){
        take_forks(*i);
        put_forks(*i);
    }
}

/*
 * Fait manger le philosophe défini par avec l'id @I dès que ses deux fourchettes sont disponibles et met son state en EATING.
 * En attendant le state est mis en HUNGRY
 */
void take_forks(int i){
    sem_wait(&semaphore);
    (&phils[i])->state = HUNGRY;
    //printf("Philosopher %i a faim\n",i);
    check(i);
    sem_post(&semaphore);
    sem_wait(&sems[i]);
}

/*
 * Le philosophe défini avec l'id @i dépose ses fourchettes et commence à penser.
 * Son state est est changé en THINKING.
 * Le compteur du philosphe est incrémenté.
 */
void put_forks(int i){
    sem_wait(&semaphore);
    (&phils[i])->state = THINKING;
    //printf("Philosopher %i pense\n",i);
    check((i+1)%n); //On vérifie si le voisin de droite est maintenant capable de manger
    check((i-1)%n); //On vérifie si le voisin de gauche est maintenant capable de mander
    (&phils[i])->counter ++;
    sem_post(&semaphore);
}

/*
 * On vérifie si le philosophe défini par l'id @i est capable de manger.
 */
void check(int i){
    if((&phils[i])->state == HUNGRY && (&phils[(i-1)%n])->state != EATING &&  (&phils[(i+1)%n])->state != EATING){
        (&phils[i])->state = EATING;
        //printf("Philosopher %i mange \n",i);
        sem_post(&sems[i]); //Le philosophe est maintenant capable de manger
    }
}
/*
 * Fonction qui lance la simulation du problème des philosophes
 * @arg: nombre de threads(philosophes) utilisés
 */
int launch_threads(int arg){
    n = arg;                                           //Nombre de threads(philosophes) demandés
    phils = malloc(sizeof(struct phil_struct)*n); //Tableau contenant l'ensemble des philosophes
    sems = malloc(sizeof(sem_t)*n);               //Tableau contenant l'ensemble des sémaphores propres à chaque philosophe
    sem_init(&semaphore,0,1);

    //Initialisation des philosophes et des sémaphores
    for(int i=0;i<n;i++){
        philosophe p = {i,0,THINKING};
        phils[i] = p;
        sem_init(&sems[i],0,1);
    }

    //Création des threads
    pthread_t *threads = malloc(sizeof(pthread_t)*n);
    for(int i=0;i<n;i++){
        //printf("Create thread %i et id %i\n",i,(&phils[i])->id);
        pthread_create(&threads[i],NULL,philosophing,&(&phils[i])->id);
    }

    //Join de l'ensemble des threads
    for(int i=0;i<n;i++){
        pthread_join(threads[i],NULL);
    }
    //La mémoire qui a été malloc est libérée
    free(phils);
    free(sems);
    return 0;
}

int main(int argc, char *argv[]){
    int a = atoi(argv[1]);
    printf("%i",a);
    launch_threads(a);
}