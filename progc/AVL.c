#include "AVL.h"


AVL* creerarbre(Route e){ //creer un arbre.
	AVL* a=NULL;
	a=malloc(sizeof(AVL));
	if(a==NULL){
		printf("pointeur pas attribué");
		exit(2);
	}
	a->fg=NULL;
	a->fd=NULL;
	a->r.id=e.id;
	a->r.somme=e.somme;
	a->r.max=e.max;
	a->r.min=e.min;
	a->r.trajet=1;
	a->r.moyenne=0;
	a->r.diff=0;
	a->equilibre=0;
	return a;
}


int maxf( int a, int b){ //max entre 2 valeur.
	if (a>b){
		return a;
	}
	return b;
}

int max3(int a, int b, int c){//max entre 3 valeurs.
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


int minf(int a, int b, int c){ min entre 2 valeurs
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

AVL * rotationGauche(AVL * a){ //rotation simple à gauche dans un AVL 
	AVL * p=a->fd;
	a->fd = p->fg; 
	p->fg = a; 
	int eq_a = a->equilibre; 
	int eq_p = p->equilibre; 
	a->equilibre = eq_a - maxf(eq_p, 0) - 1;
	p->equilibre = minf(eq_a - 2, eq_a+eq_p-2, eq_p-1); 
	a = p; 
	return a; 
} 

AVL * rotationDroite(AVL * a){ // rotation simple à droite dans un AVL 
	AVL * p=a->fg; 
	a->fg = p->fd; 
	p->fd = a; 
	int eq_a = a->equilibre; 
	int eq_p = p->equilibre; 
	a->equilibre = eq_a - minf(eq_p, 0, 0) + 1; 
	p->equilibre = max3(eq_a+2, eq_a+eq_p+2, eq_p+1); 
	a = p; 
	return a; 
} 

AVL * doubleRotationGauche(AVL * a){ // double rotation gauche d'un AVL
	a->fd = rotationDroite(a->fd); 
	return rotationGauche(a); 
} 

AVL * doubleRotationDroite(AVL * a){ //double rotation droite d'un AVL
	a->fg = rotationGauche(a->fg); 
	return rotationDroite(a); 
} 

AVL * equilibrageAVL(AVL * a){ //Equilibrage d'un AVL
	if (a->equilibre >= 2){ 
		if(a->fd->equilibre >= 0){ 
			return rotationGauche(a); 
		}else{ 
			return doubleRotationGauche(a); 
		} 
		
	}if (a->equilibre <= -2){ 
		if(a->fg->equilibre <= 0){ 
			return rotationDroite(a); 
		}else{ 
			return doubleRotationDroite(a); 
		} 
	}
	return a; 
	
}
	 


	
AVL* insert(AVL* a, Route e, int* h){ //Insertion d'un élement dans un AVL
	if(a==NULL){
		*h=1;
		return creerarbre(e);
	}
	else if(e.id < a->r.id){
		a->fg=insert(a->fg, e, h);
		*h=-(*h);
	}
	else if(e.id > a->r.id){
		a->fd=insert(a->fd, e, h);
	}else {
		*h=0;
		return a;
	}
	
	if (*h!=0){
		a->equilibre=a->equilibre + *h;
		a=equilibrageAVL(a);
		if (a->equilibre==0){
			*h=0;
		}else{
			*h=1;
		}
	}
	
	return a;
}


int recherche_et_ajout( AVL* a, Route e){ // Ajoute la distance a la bonne route si elle est déjà dans l'AVL
	if (a==NULL){
		return 0;
	}else if (e.id==a->r.id){
		a->r.somme=a->r.somme+e.somme;
		a->r.trajet+=1;
		if(a->r.max<e.max){
			a->r.max=e.max;
		}
		if(a->r.min>e.min){
			a->r.min=e.min;
		}
		return 1;
	}else if (e.id < a->r.id){
		return recherche_et_ajout(a->fg, e);
	}else if (e.id > a->r.id){
		return recherche_et_ajout(a->fd, e);
	}
	
}


AVL* ajout (AVL* a, Route e,int* h){ //Augmente la route déjà existante ou créer un nouvel arbre si la route n'est pas dans l'AVL
	int i=recherche_et_ajout(a, e);
	
	if (i==0){
		a=insert (a, e, h);
	}
	return a;
}

Route creerRoute(Route r, int dist, int i){ //Créer une nouvelle route.
	
	r.trajet=1;
	r.id=i;
	r.max=dist;
	r.min=dist;
	r.somme=dist;
	return r;
	
}



