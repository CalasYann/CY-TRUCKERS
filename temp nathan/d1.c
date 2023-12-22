#include <stdio.h>
#include <stdlib.h>

#define MAX 30

typedef struct AVL{
    int id;
    //char * nom;      (je sais pas si on met le nom du conducteur dans l'AVL)
    int nbr_trajets;
    int equilibre;
    AVL * fg;
    AVL * fd;
}AVL;

char * nom;
int id_trajet;

AVL * creerAVL(int idn){
    AVL * a = malloc(sizeof(AVL));
    a->id = idn;
    a->equilibre = 0;
    a->nbr_trajets = 1;
    a->fg = NULL;
    a->fd = NULL;

    return a;
}



int recherche(AVL * Arbre, int id){
    if (Arbre == NULL){
        return 0;
    }
    if (id > Arbre->id){
        return recherche(Arbre->fd, id);
    }
    else if (id < Arbre->id){
        return recherche(Arbre->fg, id);
    }
    else{
        return 1;
    }
}

int id_from_char(char * s){
    //créée un int unique à partir d'une chaine de caractères (pour faire un AVL)
    int id = 0;
    int i = 0;
    while (*(s+i) != '\0' && i<30){
        id = id + 31 + *(s+i); //je sais pas mdr
    }
}

int main(){

    while (scanf("%d;%s", id_trajet, nom ) == 2){
        
    }

}