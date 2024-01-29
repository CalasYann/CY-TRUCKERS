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
    struct AVLvilles * fg;
    struct AVLvilles * fd;
    Ville ville;
    int equilibre;
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
        scanf("%d", &c[i]);
        if((c[i] == ';') || (c[i] = '\n') || (c[i] == '\0')){
            c[i] = '\0';

            etat = 1;
        }
        i++;
    }while (etat == 0 && i<t);
    
}

int main(){
    while(e!=0){
        scanf("%c", &c);
        i = 0;
        while (c !=';' && c!='\n'){
            scanf("%c", &c);
            printf("%d\n", mega_i);
            s[i] = c;
            i++;
            mega_i++;
        }
        //printf("%s\n", s);
        if (s[0] == 'R' && s[1] == 'O' && s[2] == 'U'){
            e = 0;
        }
    }
}