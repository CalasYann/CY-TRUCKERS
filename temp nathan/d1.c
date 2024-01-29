#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 30

typedef struct AVL{
    unsigned int id;
    char nom[MAXLEN];      //(je sais pas si on met le nom du conducteur dans l'AVL)
    int nbr_trajets;
    int equilibre;
    int trajets[50];
    struct AVL * fg;
    struct AVL * fd;
}AVL;



AVL * creerAVL(int idn, char * str){
    AVL * a = malloc(sizeof(AVL));
    int i = 0;

    a->id = idn;
    a->equilibre = 0;
    a->nbr_trajets = 1;
    a->fg = NULL;
    a->fd = NULL;
    
    /*while (i<MAXLEN && (*(str+i) != '\0' && *(str+i) != '\n')){
        a->nom[i] = *(str+i);
        i++;
    }*/

    strcpy(a->nom, str);

    return a;
}

int maxf(int a, int b){
    if (a > b){
        return a;
    }
    else{
        return b;
    }
}

int max3(int a, int b, int c){
    int temp;
    if (a>b){
        temp = a;
    }
    else{
        temp = b;
    }

    if (c>temp){
        temp = c;
    }
    return temp;
}

int minf(int a, int b, int c){
    int temp;
    if (a<b){
        temp = a;
    }
    else{
        temp = b;
    }

    if (c < temp){
        temp = c;
    }
    return temp;
}

void traiter(AVL * a){
    printf("%d\n", a->id);
    printf("%s\n", a->nom);
}

void parcoursPrefixe(AVL * a){
    if (a != NULL){
        traiter(a);
        parcoursPrefixe(a->fg);
        parcoursPrefixe(a->fd);
    }
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

int existeFilsDroit(AVL * a){
    if (a->fd != NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int existeFilsGauche(AVL * a){
    if (a->fg != NULL){
        return 1;
    }
    else{
        return 0;
    }
}

AVL * suppMinAVL(AVL * a, int * h, unsigned int * pe){
    AVL * temp;

    if (a->fg == NULL){
        *pe = a->id;
        *h = -1;
        temp = a;
        a = a->fd;
        free(temp);
        return a;
    }
    else{
        a->fg = suppMinAVL(a->fg, h, pe);
        *h = -*h;
    }

    if (*h != 0){
        a->equilibre = a->equilibre + *h;
        if (a->equilibre == 0){
            *h = -1;
        }
        else{
            *h = 0;
        }
    }
    return a;
}

AVL * rotationGauche(AVL * a){ //rotation simple à gauche dans un AVL
    AVL * p;
    int eq_p, eq_a;

    p = a->fd;
    a->fd = p->fg;
    p->fg = a;
    eq_a = a->equilibre;
    eq_p = p->equilibre;
    a->equilibre = eq_a - maxf(eq_p, 0) - 1;
    p->equilibre = minf(eq_a - 2, eq_a+eq_p-2, eq_p-1);
    a = p;

    return a;
}

AVL * rotationDroite(AVL * a){ // rotation simple à droite dans un AVL
    AVL * p;
    int eq_p, eq_a;

    p = a->fg;
    a->fg = p->fd;
    p->fd = a;
    eq_a = a->equilibre;
    eq_p = p->equilibre;
    a->equilibre = eq_a - minf(eq_p, 0, 0) + 1;
    p->equilibre = max3(eq_a+2, eq_a+eq_p+2, eq_p+1);
    a = p;
    return a;
}

AVL * doubleRotationGauche(AVL * a){
    a->fd = rotationDroite(a->fd);
    return rotationGauche(a);
}

AVL * doubleRotationDroite(AVL * a){
    a->fg = rotationGauche(a->fg);
    return rotationDroite(a);
}

AVL * equilibrageAVL(AVL * a){
    if (a->equilibre >= 2){
        if(a->fd->equilibre >= 0){
            return rotationGauche(a);
        }
        else{
            return doubleRotationGauche(a);
        }
    }
    if (a->equilibre <= -2){
        if(a->fg->equilibre <= 0){
            return rotationDroite(a);
        }
        else{
            return doubleRotationDroite(a);
        }
    }
    return a;
}

int present(int * l, int a){
    int i = 0;
    while (l+i != NULL){
        if ( *(l+i) == a){
            return 1;
        }
        i++;
    }
    return 0;
}

AVL * insertionAVL(AVL * a, unsigned int id, int * h, char * nom, int id_t){
    //printf("%s", nom);
    if (a==NULL){
        //printf("a = NULL\n");
        *h = 1;
        //printf("ça a marché avec h chef\n");
        return creerAVL(id, nom);
    }
    else if (id < a->id){
        *h= -*h;
        a->fg = insertionAVL(a->fg, id, h, nom, id_t);
    }
    else if (id > a->id){
        a->fd = insertionAVL(a->fd, id, h, nom, id_t);
    }
    else{
        if (present(a->trajets, id_t) == 0){
            //rajoute l'id du nouveau trajet dans la liste des trajets
            a->trajets[a->nbr_trajets] = id_t;
            a->nbr_trajets++;
        }
        *h=0;
        return a;
    }

    if ( *h != 0){
        a->equilibre = a->equilibre + *h;
        a = equilibrageAVL(a);
        if (a->equilibre == 0){
            *h = 0;
        }
        else{
            *h = 1;
        }
    }
    return a;
}

AVL * suppressionAVL(AVL * a, unsigned int id, int * h){
    AVL * temp;
    if(a == NULL){
        *h = 1;
        return a;
    }
    else if (id > a->id){
        a->fd = suppressionAVL(a->fd, id, h);
    }
    else if (id < a->id){
        a->fg = suppressionAVL(a->fd, id, h);
        *h = -*h;
    }
    else if (existeFilsDroit(a)){
        a->fg = suppMinAVL(a->fd, h, &(a->id));
    }
    else{
        temp = a;
        a = a->fg;
        free(temp);
        *h = -1;
    }

    if (a == NULL){
        *h = 0;
    }
    a = equilibrageAVL(a);
    if (*h != 0){
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

    char buffer[100];
    char * data;

    int id_trajet;
    char * nom;
    AVL * a = NULL;
    int  h;
    h = 0;
    int j = 0;

    nom = malloc(sizeof(char)*MAXLEN);

    /*while (fgets(buffer, sizeof(buffer), stdin) != NULL){
        j = 0;
        data = strtok(buffer,";");
        
        id_trajet = atoi(data);
        printf("%d;", id_trajet);
            

        data = strtok(NULL,";");
        
        //nom = data;
        while ((data[j] != '\0') && (data[j] != '\n')){
            nom[j] = data[j];
            j++;
        }
        printf("%s\n", nom);

        a = insertionAVL(a, id_from_char(nom), &h, nom);

        
        //parcoursPrefixe(a);
        
    }*/

    while (fgets(buffer, sizeof(buffer), stdin)){
        j = 0;
        data = strtok(buffer, ";\n");
        
        id_trajet = atoi(data);
        printf("%d;", id_trajet);

        data = strtok(NULL,";\n");
        //printf("data : %s\n", data);
        /*while( data[j] != '\0'){
            printf("%c", data[j]);
            j++;
        }*/
        printf("\n");
        strcpy(nom, data);
        //nom = data;
        //printf("nom : %s\n", nom);

        a = insertionAVL(a, id_from_char(nom), &h, nom, id_trajet);
    }

    printf("===========\n");

    parcoursPrefixe(a);
    

    
}