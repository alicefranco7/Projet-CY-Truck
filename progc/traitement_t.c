#include "fonctionAVL.h"
#include "traitement_t.h"

Noeud* nouveauNoeud(char* nv, int numT, char da, int numE) { // creer un nouveau noeud
   Noeud* noeud = (Noeud*)malloc(sizeof(Noeud));
   
    if (noeud == NULL) {
        fprintf(stderr, "Erreur d'allocation pour le nouveau nœud.\n");
        exit(EXIT_FAILURE);
    }

    // Allocation et copie sécurisée de la chaîne de caractères "ville"
    if (nv != NULL) {
        noeud->ville = strdup(nv);
        if (noeud->ville == NULL) {
            fprintf(stderr, "Erreur d'allocation pour la ville du nouveau nœud.\n");
            free(noeud);
            exit(EXIT_FAILURE);
        }
    }
        noeud->numT = numT;
        noeud->tab =malloc(sizeof(int)); // Initialiser à NULL, l'allocation se fait dans insertion
	if(noeud->tab!=NULL){
		noeud->tab[0] = numT; // je mets mon numero de trajet dans mon tableau qui stocke ces numeros de trajets
		//noeud->tab[1]= 0;
	}else{// sinon je sors (exit)
  	    fprintf(stderr, "Erreur d'allocation pour le tableau du nouveau nœud.\n");
            free(noeud->ville);
            free(noeud);
            exit(EXIT_FAILURE);
	}
	if ( da == 'D' && numE==1){ // si ma ville est ville de depart et que je suis a la premiere etape de mon trajet
		noeud->compteur_depart=1; // alors j'augmente mon compteur de depart
	}else{
		noeud->compteur_depart=0;
	}
        noeud->gauche = NULL;
        noeud->droite = NULL;
        noeud->nboccu = 1; // compte combien de fois une ville a été traversée
        noeud->hauteur = 1;
	noeud->numE = numE;
	

    return noeud;
}

Noeud* insertion(Noeud* noeud, char* ville, int numT, char da, int numE) { // j'insere mes villes dans mon AVL en les triants par ordre alphabétique
    if (noeud == NULL) {
        return nouveauNoeud(ville, numT, da, numE);
    }
    if (strcmp(ville, noeud->ville) < 0) {
        noeud->gauche = insertion(noeud->gauche, ville, numT, da, numE);
    } else if (strcmp(ville, noeud->ville) > 0) {
        noeud->droite = insertion(noeud->droite, ville, numT, da, numE);
    } else if (strcmp(ville, noeud->ville) == 0) { // si la nouvelle ville est egale à un noeud déja éxitant
        int i = 0;
        while (noeud->tab[i] != 0) { // je parcours tout mes identifiants pour voir si j'ai deux numero de trajets identiques
            if (numT == noeud->tab[i]) {
                if (da == 'D' && numE == 1) { // si oui et que la ville est ville de départ et que je suis à la premiere étape alors j'augmente le compteur de départ
                    noeud->compteur_depart++;
                }
                return noeud;
            }
            i++;
        }
 // j'augmente le nombre d'occurence totale
        if (da == 'D' && numE == 1) { // si ma ville est ville de depart et que je suis a ma premiere étape ( et donc que c'est un nouveau numéro de trajet )j'augmente le compteur de départ
            noeud->compteur_depart++;
             // je réalloue de l'espace
           } 
int* temp = realloc(noeud->tab, (noeud->nboccu + 1) * sizeof(int));if (temp != NULL) {
                noeud->tab = temp;
   		noeud->tab[noeud->nboccu  -1 ] = numT;
		noeud->nboccu++; // je mets mon nouveau numero de trajet dans mon tabl
            } else { // si erreur d'allocation je sors
                fprintf(stderr, "Erreur au moment de la réallocation\n");
                exit(1);
            }
        

    } else {
        return noeud;
    }

    noeud->hauteur = 1 + max(hauteur(noeud->gauche), hauteur(noeud->droite)); // je mets a jour la hauteur 

    int equilibre = facteurEquilibre(noeud); // je calcule l'équilibre et équilibre mon avl en fonction de ca 

    if (equilibre > 1 && strcmp(ville, noeud->gauche->ville) < 0) {
        return rotationDroite(noeud);
    }

    if (equilibre < -1 && strcmp(ville, noeud->droite->ville) > 0) {
        return rotationGauche(noeud);
    }

    if (equilibre > 1 && strcmp(ville, noeud->gauche->ville) > 0) {
        noeud->gauche = rotationGauche(noeud->gauche);
        return rotationDroite(noeud);
    }

    if (equilibre < -1 && strcmp(ville, noeud->droite->ville) < 0) {
        noeud->droite = rotationDroite(noeud->droite);
        return rotationGauche(noeud);
    }
    return noeud;
}

Noeud* noeudequi(char* ville, int nboccu, int compteur_depart){ // pour mon nouveau noeud qui sera inseré dans mon deuxieme avl 
    Noeud* noeud = malloc(sizeof(Noeud));
    if(noeud!=NULL){
        noeud->ville=strdup(ville);
        noeud->nboccu = nboccu;
        noeud->compteur_depart=compteur_depart;
        noeud->gauche = NULL;
        noeud->droite = NULL;
        noeud->hauteur = 1;
    }
    return noeud;
}



Noeud* insertion2(Noeud* noeud, char* ville, int nboccu, int compteur_depart) { // deuxieme insertion cette fois ci par nombre d'occurence ( nombre de parcours)
     if (noeud == NULL) {
        return noeudequi(ville,nboccu,compteur_depart);
    }

    if (noeud->nboccu<nboccu) {
        noeud->gauche = insertion2(noeud->gauche, ville, nboccu, compteur_depart );
    } else if (noeud->nboccu >nboccu) {
        noeud->droite = insertion2(noeud->droite, ville, nboccu, compteur_depart);
    } else if (noeud->nboccu == nboccu ){ // si les nombres d'occurences sont égales je trie par ordre alphabétique
	if( strcmp(ville, noeud->ville) < 0 ){
		noeud->gauche = insertion2(noeud->gauche, ville, nboccu, compteur_depart);
	}else {
		noeud->droite = insertion2(noeud->droite, ville, nboccu, compteur_depart);
	}
    } else {
	return noeud;
    }


    noeud->hauteur = 1 + max(hauteur(noeud->gauche), hauteur(noeud->droite)); // je calcule la hauteur;

    int equilibre = facteurEquilibre(noeud); // je calcule l'équilibre et équilibre mon avl en foncion de cet équilibre

   if (equilibre > 1 && nboccu < noeud->gauche->nboccu) {
        return rotationDroite(noeud);

    }
    if (equilibre < -1 && nboccu > noeud->gauche->nboccu ) {
        return rotationGauche(noeud);
    }
    if (equilibre > 1 && nboccu < noeud->gauche->nboccu ) {
        noeud->gauche = rotationGauche(noeud->gauche);
        return rotationDroite(noeud);
    }

    if (equilibre < -1 && nboccu > noeud->gauche->nboccu ) {
        noeud->droite = rotationDroite(noeud->droite);
        return rotationGauche(noeud);
    }

    return noeud;
}

Noeud* transfertAVL(Noeud* ancienAVL, Noeud* nouveauAVL){ // grace a un parcours préfixe je prends chaque noeud de l'ancien avl et l'insère dans le nouveau avl
    if(ancienAVL != NULL){

        nouveauAVL = insertion2(nouveauAVL, ancienAVL->ville, ancienAVL->nboccu, ancienAVL->compteur_depart);

        nouveauAVL = transfertAVL(ancienAVL->gauche, nouveauAVL);
        nouveauAVL = transfertAVL(ancienAVL->droite, nouveauAVL);
    }
    return nouveauAVL;
}

void selection10identifiants(Noeud* racine, int* compteur, Noeud** tab){  // je prends les 10 villes avec le plus de trajets grace a un pourcours infixe inverse
	if(racine !=NULL && *compteur<10){
		selection10identifiants(racine->droite,compteur,tab);
		tab[*compteur]=racine;
		(*compteur)++;
		selection10identifiants(racine->gauche,compteur,tab);
	}
}

int comparerVilles(const void* a, const void* b){ // permet de savoir l'ordre alphabétique entre deux villes
    Noeud* villeA = *((Noeud**)a);
    Noeud* villeB = *((Noeud**)b);
    return strcmp(villeA->ville, villeB->ville);
}

void parcoursinfixeinverse(Noeud* racine,FILE* traitementt){
	if (racine == NULL ){
		return ;
	}	
	int compteur;
	Noeud* tab[10];
	selection10identifiants(racine, &compteur,tab); // je selectionne les 10 villes les plus traversées
	qsort(tab, compteur, sizeof(Noeud*), comparerVilles); // je les compare pour savoir l'ordre alphabétique
    
    	for (int i = 0; i < compteur; i++) {
        	fprintf(traitementt, "%s;%d;%d\n", tab[i]->ville, tab[i]->nboccu, tab[i]->compteur_depart); // j'écris ces villes et les informations nécéssaire dans mon fichier
    	}

}
