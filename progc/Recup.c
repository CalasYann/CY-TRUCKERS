#include "Recup.h"

void recupID(char* c, int t){ //Récupère L'ID de la route passée en entrée standard
	
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


void recupDist(char* c, int t){ //Récupère la distance du trajet passée en entrée standard.
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
