#include "Tri.h"
#include "AVL.h"
#include "Recup.h"


int main(int argc, char* argv[]){
	
	if(*argv[1]=='1'){
	
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
	}else if(*argv[1]=='2'){
	    
	    char id[30];
	    char Etape[5];
	    char ville1[35];
	    char ville2[35];
	    char driver[35];
 	    AVLvilles * AVL = NULL;
	    int ID;
	    int etape;
	    int i = 0;
	    int * h = malloc(sizeof(int));

	    Ville * v = malloc(sizeof(Ville));
	    Ville * v2 = malloc(sizeof(Ville));
	    Ville * ListeVilles = malloc(10*sizeof(Ville)); //liste des 10 villes les plus traversées
	    

	    AVLvilles ** tab = malloc(10*sizeof(AVLvilles *));
	    
	    Ville* tabv=malloc(10*sizeof(Ville));
	    
	    for (int i = 0; i<10; i++){
	    	tabv[i].nombreTrajets =0;
	    }

	    recupID(id, 10);
	    recupEtape(Etape, 5);
	    recupVille(ville1, 35);
	    recupVille(ville2,35);
	    recupDriver(driver, 35);


	    while (id[0]!='R'){
		i++;

		ID = atoi(id);
		etape=atoi(Etape);
		v = creerVille(ville1, ID, driver, v);
		v2 = creerVille(ville2, ID, driver, v2);


		AVL = Insert(AVL, v, h, id_from_char(ville1), ID, driver, ville1,etape);
		AVL = Insert(AVL, v2, h, id_from_char(ville2), ID, driver, ville2,0);
		    
		recupID(id, 10);
		recupEtape(Etape,5);
		recupVille(ville1, 35);
		recupVille(ville2,35);
		recupDriver(driver, 35);
	    }
	    
	    parcoursVinfixe(AVL, tabv);
	    
	    FILE *f;
		f=fopen("temp/tempt.dat","w");
			
		if(f==NULL){
			printf("Erreur dans la création du fichier\n");
			exit(4);
		}
		for(int j=0; j<10; j++){
			fprintf(f, "%s; %d ; %d \n", tabv[j].nom , tabv[j].nombreTrajets, tabv[j].nbPremierEtape);
		}
			
			fclose(f);
			
    
    
	}else{
		return 1;
	}
}
