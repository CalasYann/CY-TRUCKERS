
#include "Tri.h"
#include "AVL.h"
#include "Recup.h"


int main(){
	AVL* a=NULL;

	char id[30];
	char dist[30];
	recupID(id,30);
	recupDist(dist, 30);
	float kil;
	int* h=malloc(sizeof(int));
	int ID;
	int kili;
	Route r;
	int i=0;	
	Route *R=malloc(50*sizeof(Route));
	for(int i=0;i<50;i++){
		R[i].diff=0;
	}
	
	while (id[0]!='R' && dist[0]!='D'){
		i+=1;
		
		ID=atoi(id);
		kil=atof(dist);
		kili=kil*1000;
	
		r=creerRoute(r,kili,ID);
		
		a=ajout(a,r,h);
		
		
		recupID(id,30);
		recupDist(dist, 30);
		
	}
	
	parcoursInfixe(a,R);
	
	FILE *f;
	f=fopen("temp/temps.dat","w");
	
	if(f==NULL){
		printf("Erreur dans la création du fichier\n");
		exit(4);
	}
	for(int i=0; i<50; i++){
		R[49-i].max=R[49-i].max/1000;
		R[49-i].min=R[49-i].min/1000;
		fprintf(f, "%d; %d; %d; %d \n",R[49-i].id,R[49-i].min,R[49-i].moyenne,R[49-i].max);
	}
	
	fclose(f);
	
	
	
	
	return 0;
}

