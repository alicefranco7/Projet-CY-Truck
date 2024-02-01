#include "fonctionAVL.h"

int hauteur(Noeud *N) { // retourne la hauteur d'un noeud
    if (N == NULL)
        return 0;
    return N->hauteur;
}


int max(int a, int b) { // cherche le max entre deux entiers
    return (a > b) ? b : a;
}


Noeud *rotationDroite(Noeud *y) { // fonction de rotation a droite
    Noeud *x = y->gauche;
    Noeud *T2 = x->droite;

    x->droite = y;
    y->gauche = T2;

    y->hauteur = max(hauteur(y->gauche), hauteur(y->droite)) + 1;
    x->hauteur = max(hauteur(x->gauche), hauteur(x->droite)) + 1;

    return x;
}

Noeud *rotationGauche(Noeud *x) { // fonction de rotation a gauche
    Noeud *y = x->droite;
    Noeud *T2 = y->gauche;

    y->gauche = x;
    x->droite = T2;

    x->hauteur = max(hauteur(x->gauche), hauteur(x->droite)) + 1;
    y->hauteur = max(hauteur(y->gauche), hauteur(y->droite)) + 1;

    return y;
}

int facteurEquilibre(Noeud *N) { // fonction qui calcule l'équilibre
    if (N == NULL)
        return 0;
    return hauteur(N->gauche) - hauteur(N->droite);
}


void libererMemoire(Noeud* a){ // fonction qui libère la mémoire
    if(a!=NULL){
        libererMemoire(a->gauche);
        libererMemoire(a->droite);
        free(a);
    }
}



