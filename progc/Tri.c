#include "Tri.h"


void TriSelection(Route* T, int n){
	int noEtape,noCase,indiceMin;
	Route temp;
	
	for(noEtape=0; noEtape<n-1;noEtape++){
		indiceMin=noEtape; 
		for(noCase=noEtape+1; noCase<n;noCase++){
			if(T[noCase].diff <= T[indiceMin].diff){
				indiceMin=noCase;
			}
		}
		if(indiceMin!=noEtape){
			temp=T[indiceMin];
			T[indiceMin]=T[noEtape];
			T[noEtape]=temp;
		}
	}
}

void max50(AVL* a, Route* R){
	a->r.diff=a->r.max-a->r.min;
	a->r.moyenne=(a->r.somme/a->r.trajet)/1000;
	if(R[0].diff<=a->r.diff){
		R[0]=a->r;
		TriSelection(R, 50);
	}
}





void parcoursInfixe( AVL* a, Route* R){
	if(a!=NULL){
		parcoursInfixe(a->fg,R);
		max50(a,R);
		parcoursInfixe(a->fd,R);
		free(a);
	}
}



void triVSelection(Ville * t, int n){
    int i, j, index_min;
    Ville temp;

    for (i = 0; i<n-1; i++){
        index_min = i;
        for (j = i+1; j<n; j++){
            if(t[j].nombreTrajets < t[index_min].nombreTrajets){
                index_min = j;
            }
        }if(index_min != i){
             temp = t[index_min];
             t[index_min] = t[i];
             t[i] = temp;
              
        }
    }

}

void max10(Ville * v, AVLvilles  * a){
	if (v[0].nombreTrajets <= a->nombreTrajets){
		v[0].nombreTrajets = a->nombreTrajets;
		strcpy(v[0].nom, a->nom);
		v[0].nbPremierEtape=a->nbPremierEtape;
		//rajouter trajets max;
		triVSelection(v, 10);
	}
}

void parcoursVinfixe(AVLvilles * a, Ville *  v){
	if (a != NULL){
		parcoursVinfixe(a->fg, v);
		max10(v, a);
		parcoursVinfixe(a->fd, v);
		free(a);
	}
}

