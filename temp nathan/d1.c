#include <stdio.h>
#include <stdlib.h>

#define MAX 30

typedef struct AVL{
    unsigned int id;
    //char * nom;      (je sais pas si on met le nom du conducteur dans l'AVL)
    int nbr_trajets;
    int equilibre;
    struct AVL * fg;
    struct AVL * fd;
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



int recherche(AVL * Arbre, int id){ //renvoie 1 si un arbre avec l'id passé en argument existe dans l'arbre passé en argument, 0 sinon
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

AVL * equilibrageAVL(AVL * a){
    //je fais après je vais manger là
}

AVL * insertionAVL(AVL * a, int id, int * h){
    if (a==NULL){
        *h = 1;
        return creerAVL(id);
    }
    else if (id < a->id){
        *h= -*h;
        a->fg = insertionAVL(a->fg, id, h);
    }
    else if (id > a->id){
        a->fd = insertionAVL(a->fd, id, h);
    }
    else{
        *h=0;
        return a;
    }

    if ( *h != 0){
        a->equilibre = a->equilibre + *h;
        if (a->equilibre == 0){
            *h = 0;
        }
        else{
            *h = 1;
        }
    }
    return a;
}

int id_from_char(char * s){
    //créée un int unique à partir d'une chaine de caractères (pour faire un AVL)
    unsigned int id = 0;
    int i = 0;
    while (*(s+i) != '\0' && i<30){
        id = id*27 + *(s+i); //je sais pas mdr
        i++;
    }

    return id;
}

int main(){

    /*while (scanf("%d;%s", id_trajet, nom ) == 2){
        
    }*/

    char bonjour[] = "Hello World!";

    printf("%u\n", id_from_char(bonjour));
    printf("%d\n", id_from_char("Hfllo World!"));
    printf("%d", (id_from_char(bonjour) == id_from_char("Hfllo World!")));
}