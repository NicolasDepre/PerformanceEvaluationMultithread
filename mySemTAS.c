#include "headers/mySemTAS.h"

/*
 * Sémaphore basée sur le verrou à attente active TEST AND SET (TAS.c)
 */

typedef struct s{
    int queu;       //Valeur de la sémaphore
    spinLock  *l;   //Verrou
    spinLock *mod;
}mySem;

/*
 * Initialisation de la sémamphore
 * Malloc des variables nécessaires
 */
int mySem_init(mySem** sem,int n){
    if(!(*sem = malloc(sizeof(mySem)))) return -1;
    (*sem)->queu = n;
    if(!(spinlock_init(&(*sem)->mod)) return -1;
    if(!(spinlock_init(&(*sem)->l)) return -1;
    return 0;
}

/*
 * Décremente queue de 1 et fait patienter le threads tant que queue <= 0
 */
void mySem_wait(mySem** sem){
    spinlock_lock(&(*sem)->l);
    while((*sem)->queu<=0){}
    spinlock_lock(&(*sem)->mod);
    (*sem)->queu --;
    spinlock_unlock(&(*sem)->mod);
    spinlock_unlock(&(*sem)->l);
}

/*
 * Libère la sémaphore de 1 (queue += 1)
 */
void mySem_Post(mySem** sem){
    spinlock_lock(&(*sem)->mod);
    (*sem)->queu++;
    spinlock_unlock(&(*sem)->mod);
}

/*
 * Free les variables utilisées
 */
void mySem_destroy(mySem** sem){
    spinlock_destroy((*sem)->mod);
    spinlock_destroy((*sem)->l);
    free(*sem);
}