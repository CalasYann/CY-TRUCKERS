#ifndef AVL_H
	#define AVL_H
	
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	
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
	
	
	typedef struct IDTrajets{
    	//structure pour file dynamique de trajets
	    int id;
	    struct IDTrajets * fg;
    	    struct IDTrajets * fd;
	}IDTrajets;

	typedef struct Driver{
	    //structure pour file dynamique de conducteurs
	    char nom[35];
	    unsigned int id;
	    struct Driver * fg;
	    struct Driver * fd;
	}Driver;

	typedef struct Ville{
	    char nom[35];
	    IDTrajets * trajets; //tête de la file de trajets
	    Driver * drivers;
	    int nombreTrajets;
	    int nombreDrivers;
	    int nbPremierEtape;
	}Ville;

	typedef struct AVLvilles{
	    unsigned int id;
	    struct AVLvilles * fg;
	    struct AVLvilles * fd;
	    int equilibre;
	    char nom[35];
	    IDTrajets * trajets;
	    Driver * drivers;
	    int nombreTrajets;
	    int nombreDrivers;
	    int nbPremierEtape;
	}AVLvilles;
	
	unsigned int id_from_char(char * s);
	void afficherVille(Ville * v);
	Driver * creerDriver(char * Nom);
	IDTrajets * creerIdTrajets(int Id);
	Ville * creerVille(char * Nom, int id, char * nomDriver, Ville * v);
	AVLvilles * creerAVL (Ville * v, int etape);
	AVLvilles * RotationGauche(AVLvilles * a);
	AVLvilles * RotationDroite(AVLvilles * a);
	AVLvilles * DoubleRotationGauche(AVLvilles * a);
	AVLvilles * DoubleRotationDroite(AVLvilles * a);
	AVLvilles * EquilibrageAVL(AVLvilles * a);
	Driver * insererDriver(Driver * d, Driver * a);
	int rechercheDriver(Driver * d, int id);
	int rechercheID(IDTrajets * ArbreTrajets, int id);
	IDTrajets * insererTrajets(IDTrajets * ArbreTrajets, IDTrajets * nouveau_trajet);
	AVLvilles * actualisationAVLVilles(AVLvilles * a, int id, char * driver);
	AVLvilles * Insert(AVLvilles * a, Ville * v, int * h, unsigned int id, int idtrajet, char * driver, char * nom, int etape);
	
#endif
