#include "headers/mySemTATAS.h"

/*
 * Sémaphore basée sur le verrou à attente active TEST AND TEST ABD SET (TATAS.c)
 */



/*
 * Initialisation de la sémamphore
 * Malloc des variables nécessaires
 */
int mySem_init(mySem** sem,int n){
    *sem = malloc(sizeof(mySem));
    (*sem)->queu = n;
    spinlock_init(&(*sem)->mod);
    spinlock_init(&(*sem)->l);
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
void mySem_post(mySem** sem){
    spinlock_lock(&(*sem)->mod);
    (*sem)->queu++;
    spinlock_unlock(&(*sem)->mod);
}

/*
 * Free les variables utilisées
 */
void mySem_destroy(mySem** sem){
    spinlock_destroy(&(*sem)->mod);
    spinlock_destroy(&(*sem)->l);
    free(*sem);
}