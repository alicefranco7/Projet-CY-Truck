#ifndef traitement_s_h
#define traitement_s_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Noeud* insertion3(Noeud* noeud, float distance, int numerotrajet);
float moyenne(float* tab,int compteur);
void minmax (float* tab, Noeud* noeud);
Noeud* nouveauNoeuds(float distance, int numeroTrajet); 
void parcourspref(Noeud* racine); 
Noeud* copierNvAVL(float moyenne, float min, float max, int numt);
Noeud* avlTrie(Noeud* avl, float min, float moyenne, float maxi, int numT);
Noeud* trisavl(Noeud* noeud, Noeud** nv);
void selection(Noeud* avl, char* mode, FILE* fichierSortie,int*  i);


#endif
