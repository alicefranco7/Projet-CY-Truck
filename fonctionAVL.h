#ifndef fonctionsAVL_h
#define fonctionsAVL_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _n{ // C'est ma structure de base pour chaque noeud de mon AVL
    char* ville;
    int numT; // ID trajet
    int numE; // num Etape
    int nboccu; // nb de fois ou elle est traversé
    int compteur_depart; // nb de fois ou elle est ville de départ
    struct _n* gauche;
    struct _n* droite;
    int hauteur;
    int* tab; // stocke tous les id de trajets
    float moyenne;
    float min;  
    float max;
    float maxmin;
    float* tabdistance;// stocke toutes distances
    int compteur;
}Noeud;

int hauteur(Noeud *N);
int max(int a, int b);
Noeud *rotationDroite(Noeud *y);
Noeud *rotationGauche(Noeud *x); 
int facteurEquilibre(Noeud *N);
void libererMemoire(Noeud* a);

#endif
