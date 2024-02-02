#include "Recup.h"

void recupID(char* c, int t){
	
	int i=0;
	int j=0;
	do{
		scanf("%c",&c[i]);

		if(c[i]==';'){
			c[i]='\0';
			
			j=1;
		}
		i++;
	}while(j==0 && i<t);
}


void recupDist(char* c, int t){
	int i=0;
	int j=0;
	do{
		scanf("%c", &c[i]);
		
		if(c[i]=='\n'){
			c[i]='\0';
			j=1;
		}
		i++;
	}while(j==0 && i<t);
	
	
}



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


void recupEtape(char* c, int t){
	
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
