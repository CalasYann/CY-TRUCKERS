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
