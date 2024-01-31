#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

char s[MAX];
char c;
char dump;
int e = 1;
int i = 0;
int mega_i = 0;

typedef struct IDTrajets{
    //structure pour file dynamique de trajets
    int id;
    struct IDTrajets * next;
}IDTrajets;

typedef struct Driver{
    //structure pour file dynamique de conducteurs
    char nom[35]; //le nom de conducteur le plus long fait 32 caractères
    struct Driver * next;
}Driver;

typedef struct Ville{
    char nom[35];
    IDTrajets * trajets; //tête de la file de trajets
    Driver * drivers;
    int nombreTrajets;
    int nombreDrivers;
}Ville;

typedef struct AVLvilles{
    unsigned int id;
    struct AVLvilles * fg;
    struct AVLvilles * fd;
    int equilibre;
    char nom[35];
    IDTrajets * trajets;
    Driver * drivers;
    int nombreTrajets;
    int nombreDrivers;
}AVLvilles;

void recupVille(char * c, int t){
    int i = 0;
    int etat = 0;
    do{
        scanf("%c", &c[i]);
        if(c[i] == ';'){
            c[i] = '\0';

            etat = 1;
        }
        i++;
    }while(etat == 0 && i<t);
}

void recupID(char* c, int t){
	
	int i=0;
	int etat=0;
	do{
		scanf("%c",&c[i]);

		if(c[i]==';'){
			c[i]='\0';
			
			etat=1;
		}
		i++;
	}while(etat == 0 && i<t);
}

void recupDriver(char * c, int t){
    int i = 0;
    int etat = 0;
    do{
        scanf("%c", &c[i]);
        if((c[i] == '\n' || c[i] == '\0')){
            c[i] = '\0';

            etat = 1;
        }
        i++;
    }while (etat == 0 && i<t);
}

unsigned int id_from_char(char * s){
    //créée un int unique à partir d'une chaine de caractères (pour faire un AVL)
    unsigned int id = 0;
    int i = 0;
    while (*(s+i) != '\0' && i<30){
        id = id*27 + *(s+i); 
        i++;
    }

    return id;
}

void afficherVille(Ville * v){
    
}

Driver * creerDriver(char * Nom){
    Driver * d = NULL;
    d = malloc(sizeof(Driver));
    if (d == NULL){
        printf("erreur pendant l'allocation d'espace pour un driver %s\n", Nom);
        exit(1);
    }
    strcpy(Nom,d->nom);
    d->next = NULL;

    return d;
}

IDTrajets * creerIdTrajets(int Id){
    IDTrajets * id = malloc(sizeof(IDTrajets));
    if(id == NULL){
        printf("erreur pendant l'allocation d'espace pour un IDTrajet %d\n", Id);
        exit(1);
    }
    id->id = Id;
    id->next = NULL;

    return id;
}



Ville * creerVille(char * Nom, int id, char * nomDriver, Ville * v){
    strcpy(v->nom, Nom);
    v->drivers = creerDriver(nomDriver);
    v->nombreDrivers = 1;

    v->trajets = creerIdTrajets(id);
    v->nombreTrajets = 1;

    return v;
}

AVLvilles * creerAVL (Ville * v){
    AVLvilles * a = NULL;
    a = malloc(sizeof(AVLvilles));
    if(a==NULL){
        printf("mémoire non allouée pendant de la création du noeud correspondant à la ville suivante\n");
        afficherVille(v);
        exit(3);
    }
    a->fg=NULL;
    a->fd=NULL;
    a->id = id_from_char(v->nom);
    a->equilibre = 0;
    strcpy(a->nom, v->nom);
    a->drivers = v->drivers;
    a->nombreDrivers = v->nombreDrivers;
    a->trajets = v->trajets;
    a->nombreTrajets = v->nombreTrajets;

    return a;
}

int maxf( int a, int b){
	if (a>b){
		return a;
	}
	return b;
}

int max3(int a, int b, int c){
	if(a>b){
		if(a>c){
			return a;
		}
		return c;
	}else {
		if(b>c){
			return b;
		}
		return c;
	}
}


int minf(int a, int b, int c){
	if(a<b){
		if(a<c){
			return a;
		}
		return c;
	}else {
		if(b<c){
			return b;
		}
		return c;
	}
}

AVLvilles * rotationGauche(AVLvilles * a){ //rotation simple à gauche dans un AVL 
	AVLvilles * p;
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

AVLvilles * rotationDroite(AVLvilles * a){ // rotation simple à droite dans un AVL 
	AVLvilles * p; 
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

AVLvilles * doubleRotationGauche(AVLvilles * a){ 
	a->fd = rotationDroite(a->fd); 
	return rotationGauche(a); 
} 

AVLvilles * doubleRotationDroite(AVLvilles * a){ 
	a->fg = rotationGauche(a->fg); 
	return rotationDroite(a); 
}

AVLvilles * equilibrageAVL(AVLvilles * a){ 
	if (a->equilibre >= 2){ 
		if(a->fd->equilibre >= 0){ 
			return rotationGauche(a); 
		}else{ 
			return doubleRotationGauche(a); 
		} 
		if (a->equilibre <= -2){ 
			if(a->fg->equilibre <= 0){ 
				return rotationDroite(a); 
			}else{ 
				return doubleRotationDroite(a); 
			} 
		} 
	}
	return a; 
	
}

Driver * insererDriver(Driver * d, Driver * a){
    if(d == NULL){
        return a;
    }
    if(a == NULL){
        printf("erreur insererDriver : driver a ajouter non existant\n");
        exit(1);
    }
    Driver * i;
    i = d;
    while(i->next != NULL){
        i = i->next;
    }
    i->next = a;

    return d;
}

int rechercheDriver(Driver * d, char * nom){
    //vérifie si le nom du conducteur passé en argument est présent, renvoie 1 alors et 0 sinon
    if(d==NULL){
        printf("erreur rechercheDriver() : Driver non alloué\n");
        return 0;
    }
    Driver * a;
    a = d;
    while (a->next != NULL){
        if (strncmp(a->nom, nom, maxf(strlen(a->nom), strlen(nom)))){
            return 1;
        }
        else{
            a = a->next;
        }
    }
    return 0; 
}

int rechercheID(IDTrajets * ListeTrajets, int id){
    if (ListeTrajets == NULL){
        printf("erreur rechercheID() : ListeTrajets non allouée\n");
        return 0;
    }
    IDTrajets * a;
    a = ListeTrajets;
    while (a->next != NULL){
        if(a->id == id){
            return 1;
        }
        else{
            a = a->next;
        }
    }
    return 0;
}

IDTrajets * insererTrajets(IDTrajets * ListeTrajets, IDTrajets * nouveau_trajet){
    IDTrajets * a = ListeTrajets;
    while (a->next != NULL){
        a = a->next;
    }
    a->next = nouveau_trajet;

    return ListeTrajets;
}

AVLvilles * actualisationAVLVilles(AVLvilles * a, int id, char * driver){
    //actualise un noeud de l'AVL Villes en rajoutant l'id du trajet et le nom du driver dans leurs listes chainées respectives
    if (rechercheDriver(a->drivers, driver) == 0){
        a->drivers = (a->drivers, creerDriver(driver));
        a->nombreDrivers++;
    }

    if (rechercheID == 0){
        a->trajets = insererTrajets(a->trajets, creerIdTrajets(id));
        a->nombreTrajets++;
    }

    return a;
}

AVLvilles * insert(AVLvilles * a, Ville * v, int * h, unsigned int id, int idtrajet, char * driver, char * nom){
    if(a==NULL){
        *h=1;
        v = creerVille(nom, id, driver, v);
        return creerAVL(v);
    }
    else if(a->id < id){
        a->fg=insert(a->fg, v, h, id, idtrajet, driver, nom);
        *h=-(*h);
    }
    else if(a->id > id){
        a->fd=insert(a->fd, v, h, id, idtrajet, driver, nom);
    }
    else{
        *h=0;
        a = actualisationAVLVilles(a, idtrajet, driver);
        return a;
    }
    if(*h != 0){
        a->equilibre = a->equilibre + *h;
        a=equilibrageAVL(a);
        if (a->equilibre==0){
            *h=0;
        }
        else{
            *h=1;
        }
    }

    return a;
}

void afficherNoeudAVL(AVLvilles * a){
    printf("id : %d\n", a->id);
    printf("nom : %s\n",a->nom);
    printf("nombre trajets : %d\n", a->nombreTrajets);
    printf("nombre drivers : %d\n", a->nombreDrivers);
}

int afficherTailleAVL(AVLvilles * a){
    if (a != NULL){
        return 1 + afficherTailleAVL(a->fg) + afficherTailleAVL(a->fd);
    }
    else if (a==NULL){
        return 0;
    }
}

int main(){
    char id[30];
    char ville1[35];
    char ville2[35];
    char driver[35];

    int ID;

    Ville * v = malloc(sizeof(Ville));
    Ville * v2 = malloc(sizeof(Ville));
    Ville * ListeVilles = malloc(10*sizeof(Ville)); //liste des 10 villes les plus traversées
    

    AVLvilles * AVL = NULL;

    int i = 0;

    int h = 0;

    recupID(id, 10);
    recupVille(ville1, 35);
    recupVille(ville2,35);
    recupDriver(driver, 35);

    printf("id = %s\n", id);
    printf("ville1 = %s\n", ville1);
    printf("ville2 = %s\n", ville2);
    printf("driver = %s\n", driver);

    while (id[0]!='R' || ville1[0]!='T' || ville2[0]!='T' || driver[0]!='D'){
        i++;
        if (i>46000 && i<48000){
            printf("%d\n", i);
            printf("taille avl : %d\n", afficherTailleAVL(AVL));
        }
        if(i%100000 == 0){
            printf("%d\n", i);
            printf("taille AVL : %d\n", afficherTailleAVL(AVL));
        }

        //check si driver est vide
        
        ID = atoi(id);

        v = creerVille(ville1, ID, driver, v);
        if (i>46000 && i<48000){
            printf("v1 = creerVille() passe\n");
            printf("ID = %d\n", id);
            printf("nom : %s\n", ville1);
            printf("driver : %s\n", driver);
        }
        v2 = creerVille(ville2, ID, driver, v2);
        if (i>46000 && i<48000){
            printf("v2 = creerVille() passe\n");
            printf("id from char1 : %u\n", id_from_char(ville1));
            printf("id from char2 : %u\n", id_from_char(ville2));
        }

        AVL = insert(AVL, v, &h, id_from_char(ville1), ID, driver, ville1);
        if (i>46000 && i<48000){
            printf("insert v passe\n");
        }
        h = 0;
        AVL = insert(AVL, v2, &h, id_from_char(ville2), ID, driver, ville2);
        if (i>46000 && i<48000){
            printf("insert v2 passe\n");
        }


        recupID(id, 10);
        recupVille(ville1, 35);
        recupVille(ville2,35);
        recupDriver(driver, 35);
    }

    afficherNoeudAVL(AVL);
    
    printf("done\n");

}