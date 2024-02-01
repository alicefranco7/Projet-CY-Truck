#ifndef traitement_t_h
#define traitement_t_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Noeud* nouveauNoeud(char* nv, int numT, char da, int numE);
Noeud* insertion(Noeud* noeud, char* ville, int numT, char da, int numE); 
Noeud* noeudequi(char* ville, int nboccu, int compteur_depart);
Noeud* insertion2(Noeud* noeud, char* ville, int nboccu, int compteur_depart);
Noeud* transfertAVL(Noeud* ancienAVL, Noeud* nouveauAVL);
void selection10identifiants(Noeud* racine, int* compteur, Noeud** tab);
int comparerVilles(const void* a, const void* b);
void parcoursinfixeinverse(Noeud* racine,FILE* traitementt);

#endif
