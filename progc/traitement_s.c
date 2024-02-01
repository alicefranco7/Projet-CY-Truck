#include "fonctionAVL.h"
#include "traitement_s.h"



Noeud* insertion3(Noeud* noeud, float distance, int numerotrajet) { // c'est ma premiere insertion et je trie ici par  numero de trajet
    if (noeud == NULL)
        return (nouveauNoeuds(distance,numerotrajet));

    if (numerotrajet < noeud->numT)
        noeud->gauche = insertion3(noeud->gauche, distance, numerotrajet);
    else if (numerotrajet > noeud->numT)
        noeud->droite = insertion3(noeud->droite, distance, numerotrajet);
    else if (numerotrajet == noeud->numT) {
        int i = 0;
        while (noeud->tabdistance[i] != 0) { // tant qu'il y a des distance dans mon tableau je parcours jusqu'a arriver a la derniere case qui est 0
            i++;
        }
        noeud->compteur++; // j'augmente mon compteur qui permet de savoir combien de distance j'ai

        noeud->tabdistance = (float*)realloc(noeud->tabdistance,(noeud->compteur +2)*sizeof(float)); // je réalloue car j'aumente la taille
        if (noeud->tabdistance != NULL) {
            noeud->tabdistance[i] = distance; // j'ajoute ma nouvelle distance
            noeud->tabdistance[i + 1] = 0;  // je mets 0 a la prochaine case pour le prochain parcours
        }
	else {
            fprintf(stderr, "Erreur d'allocation pour le tableau du nœud existant.\n");
            free(noeud->tabdistance);
            free(noeud);  
            exit(2); // en cas d'erreur ( mauvaise reallocation) je sors
        }
    }
    noeud->hauteur = 1 + max(hauteur(noeud->gauche), hauteur(noeud->droite)); // mise a jour de la hauteur 

    int equilibre = facteurEquilibre(noeud); // mise a jour de l'equilibre et rééquilibrage de mon avl

    if (equilibre > 1 && numerotrajet < noeud->gauche->numT)
        return rotationDroite(noeud);

    if (equilibre < -1 && numerotrajet > noeud->droite->numT)
        return rotationGauche(noeud);

    if (equilibre > 1 && numerotrajet > noeud->gauche->numT) {
        noeud->gauche = rotationGauche(noeud->gauche);
        return rotationDroite(noeud);
    }

    if (equilibre < -1 && numerotrajet < noeud->droite->numT) {
        noeud->droite = rotationDroite(noeud->droite);
        return rotationGauche(noeud);
    }
    return noeud;
}

float moyenne(float* tab,int compteur){ // calcule la moyenne
  if (tab == NULL || compteur == 0) { // si mon tableau de distance est nul ou si mon compteur est null je sors 
        printf("Erreur dans la réception de l'argument\n");
        return 0;
    }
  float moy=0;
  int i;
  for (i=0; i < compteur; i++){
    moy=moy+tab[i];
  }
  moy=moy/compteur;
  return moy;
}

void minmax (float* tab, Noeud* noeud){ //calcule le min et le max
  if (tab==NULL){
    printf("erreur dans la reception ");
  }
  noeud->min=tab[0];
  noeud->max=tab[0];
  int i;
  for(i=0; i<noeud->compteur; i++){
    if(tab[i]<noeud->min){
      noeud->min=tab[i];
    }if (noeud->max<tab[i]){
      noeud->max=tab[i];
     }    
  }
}

Noeud* nouveauNoeuds(float distance, int numeroTrajet) { // nv noeud pour traitement -s
    Noeud* noeud = (Noeud*)malloc(sizeof(Noeud)); // alloc dynamique puis vérification en dessous
    if (noeud == NULL) {
fprintf(stderr, "Erreur d'allocation pour le nouveau nœud.\n");
        exit(1);
    }
    noeud->numT = numeroTrajet;
    noeud->gauche = NULL;
    noeud->droite = NULL;
    noeud->hauteur = 1;
    noeud->min=distance;
    noeud->max=distance;  
    noeud->moyenne=distance;
    noeud->tabdistance = (float*)malloc(sizeof(float)); // alloue estpace pour un tableau de distance
    if (noeud->tabdistance != NULL) {
    	noeud->tabdistance[0] = distance;
    	noeud->tabdistance[1] = 0;  // Initialiser la deuxième case à 0 pour ensuite pouvoir parcourir plus facilement
    	noeud->compteur = 1;
    } else { // en cas d'erreur
        fprintf(stderr, "Erreur d'allocation pour le tableau du nouveau nœud.\n");
        free(noeud);
        exit(1);
    }
    return noeud;
}


void parcourspref(Noeud* racine) {
    if (racine != NULL) {
        racine->moyenne = moyenne(racine->tabdistance, racine->compteur); // je calcule la moyenne pour mon noeud
        minmax(racine->tabdistance, racine); // je calcule le min et le max 
	racine->maxmin=racine->max-racine->min; // je calcule la difference entre max et min
        parcourspref(racine->gauche); // j'effectue un parcours prefixe pour associé les valeurs a chaque noeud
        parcourspref(racine->droite);
    }
}

Noeud* copierNvAVL(float moyenne, float min, float max, int numt){ // nouvelle fonction pour creer un nouveau noeud pour le second avl
	Noeud* avl=malloc(sizeof(Noeud));
	if(avl==NULL){
		exit(1);
	}else{
		avl->moyenne=moyenne;
		avl->min=min;
		avl->max=max;
		avl->maxmin=max-min;
		avl->numT=numt;
		avl->gauche=NULL;
		avl->droite=NULL;
		avl->hauteur=1;
	}

	return avl;
}


Noeud* avlTrie(Noeud* avl, float min, float moyenne, float maxi, int numT){ // deuxieme insertion: Ici on trie par le max-min
    if (avl == NULL){
       return copierNvAVL(moyenne, min ,maxi ,numT);
    }
    float diff = maxi-min;
    if (diff < avl->maxmin){
        avl->gauche = avlTrie(avl->gauche, min, moyenne, maxi , numT);
    }else if (diff > avl->maxmin){
        avl->droite = avlTrie(avl->droite, min, moyenne, maxi , numT);
    }else if (diff == avl->maxmin) { // si j'ai la meme difference alors je compare en fonction du numéro de trajet
       if(avl->numT>numT){
            avl->gauche = avlTrie(avl->gauche,min,moyenne,maxi,numT);
        }
        else if(avl->numT<numT){
            avl->droite = avlTrie(avl->droite,min,moyenne,maxi,numT);
        }
    }
    avl->hauteur = 1 + max(hauteur(avl->gauche), hauteur(avl->droite)); // mise a jour de la hauteur

    int equilibre = facteurEquilibre(avl); // on calcule l'quilibre puis on rééquilibre l'avl en fonction de celui ci

    if (equilibre > 1 && diff < avl->gauche->maxmin)
        return rotationDroite(avl);

    if (equilibre < -1 && diff > avl->droite->maxmin)
        return rotationGauche(avl);

    if (equilibre > 1 && diff > avl->gauche->maxmin) {
        avl->gauche = rotationGauche(avl->gauche);
        return rotationDroite(avl);
    }

    if (equilibre < -1 && diff < avl->droite->maxmin) {
        avl->droite = rotationDroite(avl->droite);
        return rotationGauche(avl);
    }
    return avl;
}

Noeud* trisavl(Noeud* noeud, Noeud** nv){ // fonction qui permet d'inserer chaque ancien noeud dans un nouvel avl
    if (noeud != NULL) {
            *nv = avlTrie(*nv, noeud->min, noeud->moyenne, noeud->max, noeud->numT);

        if (noeud->gauche != NULL) { // on parcours toujours via un parcours prefixe pour prendre tous les noeuds et les inserer
            trisavl(noeud->gauche, nv);
        }

        if (noeud->droite != NULL) {
            trisavl(noeud->droite, nv);
        }
    }
    return *nv;
}

void selection(Noeud* avl, char* mode, FILE* fichierSortie,int*  i){
	if(avl!=NULL && *i<50){
		selection(avl->droite, mode, fichierSortie, i); // je vais un parcours infixe inverse car je prends les plus grands 
		if (*i >= 50) {
          		return;
      		}
		fprintf(fichierSortie, "%d;%d;%.3f;%.3f;%.3f;%.3f\n",  *i+1, avl->numT, avl->min, avl->max, avl->moyenne, avl->maxmin); // j'imprime dans mon fichier toutes les informations des noeuds 
		(*i)++; // j'ai un compteur pour prendre seulement mes 50 valeurs
		selection(avl->gauche, mode, fichierSortie, i);
	}
}


