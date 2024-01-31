#ifndef AVL_H
	#define AVL_H
	
	#include <stdlib.h>
	#include <stdio.h>
	
	typedef struct {
		int id;
		int somme;
		int max;
		int min;
		int trajet;
		int moyenne;
		int diff;
	}Route;

	typedef struct AVL{
		struct AVL* fg;
		struct AVL* fd;
		Route r;
		int equilibre;
	}AVL;

	
	
	AVL* creerarbre(Route e);
	int maxf( int a, int b);
	int max3(int a, int b, int c);
	int minf(int a, int b, int c);
	AVL * rotationGauche(AVL * a);
	AVL * rotationDroite(AVL * a);
	AVL * doubleRotationGauche(AVL * a);
	AVL * doubleRotationDroite(AVL * a);
	AVL * equilibrageAVL(AVL * a);
	AVL* insert(AVL* a, Route e, int* h);
	int recherche_et_ajout( AVL* a, Route e);
	AVL* ajout (AVL* a, Route e, int* h);
	Route creerRoute(Route r, int dist, int i);
	
#endif
