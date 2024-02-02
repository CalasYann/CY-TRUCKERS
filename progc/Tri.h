#ifndef TRI_H

	#define TRI_H
	#include <stdlib.h>
	#include <stdio.h>
	#include "AVL.h"
	
	void TriSelection(Route* T, int n);
	void max50(AVL* a, Route* R);
	void parcoursInfixe( AVL* a, Route* R);
	void triVSelection(Ville * t, int n);
	void max10(Ville * v, AVLvilles  * a);
	void parcoursVinfixe(AVLvilles * a, Ville *  v);
	
#endif
