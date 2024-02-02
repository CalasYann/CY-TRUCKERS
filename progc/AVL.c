#include "AVL.h"


AVL* creerarbre(Route e){
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

AVL * doubleRotationGauche(AVL * a){ 
	a->fd = rotationDroite(a->fd); 
	return rotationGauche(a); 
} 

AVL * doubleRotationDroite(AVL * a){ 
	a->fg = rotationGauche(a->fg); 
	return rotationDroite(a); 
} 

AVL * equilibrageAVL(AVL * a){ 
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
	 


	
AVL* insert(AVL* a, Route e, int* h){
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


int recherche_et_ajout( AVL* a, Route e){
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


AVL* ajout (AVL* a, Route e,int* h){
	int i=recherche_et_ajout(a, e);
	
	if (i==0){
		a=insert (a, e, h);
	}
	return a;
}

Route creerRoute(Route r, int dist, int i){
	
	r.trajet=1;
	r.id=i;
	r.max=dist;
	r.min=dist;
	r.somme=dist;
	return r;
	
}







unsigned int id_from_char(char * s){
    //créée un int unique à partir d'une chaine de caractères (pour faire un AVL)
    unsigned int id = 0;
    int i = 0;
    while (*(s+i) != '\0' && i<35){
        id = id*27 + *(s+i); 
        i++;
    }

    return id;
}

void afficherVille(Ville * v){
    if(v== NULL){
        printf("erreur : afficherVille(NULL)\n");
        exit(5);
    }
    printf("Ville %s\n", v->nom);
}

Driver * creerDriver(char * Nom){
    Driver * d = NULL;
    d = malloc(sizeof(Driver));
    if (d == NULL){
        printf("erreur pendant l'allocation d'espace pour un driver %s\n", Nom);
        exit(1);
    }
    strcpy(d->nom, Nom);
    d->id = id_from_char(d->nom);
    d->fg = NULL;
    d->fd = NULL;

    return d;
}

IDTrajets * creerIdTrajets(int Id){
    IDTrajets * id = malloc(sizeof(IDTrajets));
    if(id == NULL){
        printf("erreur pendant l'allocation d'espace pour un IDTrajet %d\n", Id);
        exit(1);
    }
    id->id = Id;
    id->fg = NULL;
    id->fd = NULL;

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

AVLvilles * creerAVL (Ville * v, int etape){
    AVLvilles * a = NULL;
    a = malloc(sizeof(AVLvilles));
    //printf("1\n");
    if(a==NULL){
        printf("mémoire non allouée pendant de la création du noeud correspondant à la ville suivante\n");
        afficherVille(v);
        exit(3);
    }
    //printf("2\n");
    a->fg=NULL;
    a->fd=NULL;
    a->id = id_from_char(v->nom);
    a->equilibre = 0;
    strcpy(a->nom, v->nom);
    //printf("3\n");
    a->drivers = v->drivers;
    a->nombreDrivers = v->nombreDrivers;
    a->trajets = v->trajets;
    a->nombreTrajets = v->nombreTrajets;
    
    a->nbPremierEtape=0;
    if(etape==1){
    	a->nbPremierEtape=1;
    }
    //printf("4\n");

    return a;
}


AVLvilles * RotationGauche(AVLvilles * a){ //rotation simple à gauche dans un AVL 
    if(a->fg==NULL){
        //printf("salut la team\n");
        //exit(7);
    }
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

AVLvilles * RotationDroite(AVLvilles * a){ // rotation simple à droite dans un AVL 
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

AVLvilles * DoubleRotationGauche(AVLvilles * a){ 
	a->fd = RotationDroite(a->fd); 
	return RotationGauche(a); 
} 

AVLvilles * DoubleRotationDroite(AVLvilles * a){ 
	a->fg = RotationGauche(a->fg); 
	return RotationDroite(a); 
}

AVLvilles * EquilibrageAVL(AVLvilles * a){
    if(a==NULL){
        printf("erreur equilibrageAVL(NULL)\n");
        exit(6);
    }
	if (a->equilibre >= 2){ 
		if(a->fd->equilibre >= 0){ 
			return RotationGauche(a);
		}else{ 
			return DoubleRotationGauche(a); 
		}
    } 
	if (a->equilibre <= -2){ 
		if(a->fg->equilibre <= 0){ 
			return RotationDroite(a); 
	    }else{ 
			return DoubleRotationDroite(a); 
		} 
	} 
	
	return a; 
	
}


Driver * insererDriver(Driver * d, Driver * a){
    if (d == NULL){
        return a;
    }
    if (a->id < d->id){
        d->fg = insererDriver(d->fg, a);
    }
    else if (a->id > d->id){
        d->fd = insererDriver(d->fd, a);
    }
    return d;
    
}



int rechercheDriver(Driver * d, int id){
    if (d==NULL){
        return 0;
    }
    else if (d->id == id){
        return 1;
    }
    if(id < d->id){
        return rechercheDriver(d->fg, id);
    }
    else {
        return rechercheDriver(d->fd, id);
    }
    
    
}


int rechercheID(IDTrajets * ArbreTrajets, int id){
    if (ArbreTrajets == NULL){
        return 0;
    }
    else if (ArbreTrajets->id == id){
        return 1;
    }
    else if (id < ArbreTrajets->id){
        return rechercheID(ArbreTrajets->fg, id);
    }
    else if (id > ArbreTrajets->id){
        return rechercheID(ArbreTrajets->fd, id);
    }
}


IDTrajets * insererTrajets(IDTrajets * ArbreTrajets, IDTrajets * nouveau_trajet){
    if (ArbreTrajets == NULL){
        return nouveau_trajet;
    }
    else if (nouveau_trajet->id < ArbreTrajets->id){
        ArbreTrajets->fg = insererTrajets(ArbreTrajets->fg, nouveau_trajet);
    }
    else if (nouveau_trajet->id > ArbreTrajets->id){
        ArbreTrajets->fd = insererTrajets(ArbreTrajets->fd, nouveau_trajet);
    }
    return ArbreTrajets;
}

AVLvilles * actualisationAVLVilles(AVLvilles * a, int id, char * driver){
    //actualise un noeud de l'AVL Villes en rajoutant l'id du trajet et le nom du driver dans leurs listes chainées respectives
    
    if (rechercheDriver(a->drivers, id_from_char(driver)) == 0){
        a->drivers = insererDriver(a->drivers, creerDriver(driver));
        a->nombreDrivers++;
    }

    if (rechercheID(a->trajets, id) == 0){
        a->trajets = insererTrajets(a->trajets, creerIdTrajets(id));
        a->nombreTrajets++;
    }

    return a;
}

AVLvilles * Insert(AVLvilles * a, Ville * v, int * h, unsigned int id, int idtrajet, char * driver, char * nom, int etape){
    if(a==NULL){
        
        *h=1;
      
        return creerAVL(v,etape);
    }
    else if(a->id > id){
        
        a->fg=Insert(a->fg, v, h, id, idtrajet, driver, nom,etape);
        *h=-(*h);
    }
    else if(a->id < id){
        
        a->fd=Insert(a->fd, v, h, id, idtrajet, driver, nom,etape);
    }
    else{
        
        *h=0;
        a = actualisationAVLVilles(a, idtrajet, driver);
        if(etape==1){
        	a->nbPremierEtape+=1;
        }
        return a;
    }
    if(*h != 0){
        a->equilibre = a->equilibre + *h;
        a=EquilibrageAVL(a);
        if (a->equilibre==0){
            *h=0;
        }
        else{
            *h=1;
        }
    }
   
    return a;
}










