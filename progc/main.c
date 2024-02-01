#include "fonctionAVL.h"
#include "traitement_t.h"
#include "traitement_s.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 4) { // je verifie qu'il y a bien ce fichier la (.c) le data.csv et mon traitement et le fichier pour récuperer mes données donc 4 arguments
        printf("Erreur, pas le bon nombre d'arguments\n");
        return 1;
    }

    const char *nom_fichier_csv = argv[1]; // accède au dossier data.csv
    printf("Nom de l'argument : %s \n", nom_fichier_csv); // juste pour verifier le bon déroulé du code

    FILE *fichier_a_trier = fopen(nom_fichier_csv, "r"); // j'ouvre mon fichier ( en lecture seule ) et renvoie un pointeur ( avec fopen )
    if (fichier_a_trier == NULL) { // si ce pointeur est null il y a eu un soucis lors de l'ouverture
        printf("Erreur d'ouverture du fichier.\n");
        return 1;
    }
    FILE* fichierSortie = NULL;
    fichierSortie = fopen(argv[3], "w");


    if (strcmp(argv[2], "-t") == 0) { // si argument t ( on compare la chaine de carcatère entre le troisieme argument et -t
 

    Noeud* racine=NULL; // Je déclare la racine de mon futur arbre
       
    char ligne[7000000]; // Je déclare plus de ligne que nécéssaire car je ne connais pas proprement le nombre exact


    while(fgets(ligne,sizeof(ligne),fichier_a_trier) != NULL){ // permet de lire ligne par ligne le dossier csv jusqu'a ce qu'il n'y en ai plus
	// je déclare les variables de base pour récuperer ces données puis les envoyer dans mon avl
	char* villeD = malloc(51 * sizeof(char)); // 50 caractères + le caractère nul
	char* villeA = malloc(51 * sizeof(char)); // 50 caractères + le caractère nul

	int numT;
	int numE;
	float distance;
	char *token = strtok(ligne, ";"); // defini le séparateur



	if (token != NULL){ // on recupere la première variable et on la stocke
		if (sscanf(token, "%d", &numT) !=1){
			continue;
		}

		token = strtok (NULL, ";");

		if (token != NULL){ // on recupère la seconde variable et on la stocke
			if (sscanf(token , "%d", &numE) != 1){
				fprintf(stderr, "erreur de lecture du numéro de l'étape\n");
				continue;
			}

			token =strtok (NULL, ";");

			if (token != NULL){ // on recupère la 3eme variable et on la stocke
				strncpy(villeD, token, sizeof(villeD) - 1);
				villeD[sizeof(villeD)-1]= '\0';

				token =strtok (NULL, ";");
				if (token != NULL){ // on recupère la 4eme variable et on la stocke
					strncpy (villeA, token, sizeof(villeA)-1);
					villeA[sizeof(villeA)-1] = '\0';

					// on ne récupere pas les deux dernières colones car elles ne sont pas nécéssaire pour ce traitement					


//printf("Longueur de villeD : %zu\n", strlen(villeD));
//printf("Longueur de villeA : %zu\n", strlen(villeA));


  					// Insérer les villes et les information dans l'arbre AVL
  					// ici je trie par ordre alphabétique
					if (villeD != NULL) {
    						racine = insertion(racine, villeD, numT, 'D', numE);
					}

					if (villeA != NULL) {
    						racine = insertion(racine, villeA, numT, 'A', numE);
 
					}
					free(villeA);
					free(villeD);

				}
			}
		}
	}
}
// je sors ici de la boucle while
    Noeud* AVL=NULL;
    AVL=transfertAVL( AVL , racine ); // je trie par ordre croissant

    // j'affiche mes 10 villes les plus traversées grâce a un parcours infixe inverse
    parcoursinfixeinverse(AVL,fichierSortie);
	libererMemoire(racine);
        //Fermeture des fichiers d'entrée et de sortie
        fclose(fichier_a_trier);
        fclose(fichierSortie);
}

    else if (strcmp(argv[2], "-s") == 0) {

  Noeud* racine=NULL; // Je déclare la racine ( qui est un Noeud, structure déclaré au debut du code ) de mon futur arbre

  char ligne[7000000]; // Je déclare plus de ligne que nécéssaire car je ne connais pas proprement le nombre exact


  while(fgets(ligne,sizeof(ligne),fichier_a_trier) != NULL){ // permet de lire ligne par ligne le dossier csv jusqu'a ce qu'il n'y en ai plus
    // je déclare les variables de base pour récuperer ces données puis les envoyer dans mon avl
    char villeD[50];
    char villeA[50];
    int numT;
    int numE;
    float distance;
    char nom[50];
    char *token = strtok(ligne, ";"); // defini le séparateur

    if (token != NULL){ // on recupere la première variable et on la stocke
      if (sscanf(token, "%d", &numT) !=1){

        continue;
      }

      token = strtok (NULL, ";");

      if (token != NULL){ // on recupère la seconde variable et on la stocke
        if (sscanf(token , "%d", &numE) != 1){
        fprintf(stderr, "erreur de lecture du numéro de l'étape\n");
        continue;
        }

        token =strtok (NULL, ";");

        if (token != NULL){ // on recupère la 3eme variable et on la stocke
          strncpy (villeD, token, sizeof(villeD)-1);
          villeD[sizeof(villeD)-1]= '\0';

          token =strtok (NULL, ";");

          if (token != NULL){ // on recupère la 4eme variable et on la stocke
            strncpy (villeA, token, sizeof(villeA)-1);
            villeA[sizeof(villeA)-1] = '\0';

          token =strtok (NULL, ";");

            if (token != NULL){ // on recupère la distance et on la stocke
              if (sscanf(token , "%f", &distance) != 1){
              fprintf(stderr, "erreur de lecture de la distance\n");
              continue;
              }

              token =strtok (NULL, ";");

              if (token != NULL){ // on recupère le nom et on le stocke
                strncpy (nom, token, sizeof(nom));
                nom[sizeof(nom) -1] = '\0';

              token =strtok (NULL, ";");

              }
            }
          }
        }
      }
    }

       //Insérer les noeuds dans l'ordre croissant en fonction du num de trajet
            racine = insertion3(racine,distance,numT);
      // je fais un parcours prefixe et a chaque fois je calcule la moyenne le min et le max

    }
// je sors ici de la boucle while
    int i=0;
    parcourspref(racine); // pour chaque noeuds j'associe le max le min la moyenne et le max-min en faisant un parcours prefixe 
    Noeud* avl=NULL;
    avl=trisavl(racine,&avl); // la fonction prend chaque noeud et insere dans un nouveau avl qui lui sera trié avec le max-min

    selection(avl, argv[2], fichierSortie, &i);// je selectionne les 50 trajets en prenant les 50 plus grandes valeurs de max-min
    libererMemoire(racine); // je libère la mémoire
    printf("Le traitement est fini !");
}
    else {
        printf("Erreur dans la demande de traitement. Veuillez réessayer.\n");
        return 1;
    }

    fclose(fichier_a_trier); // je ferme les fichiers que j'avais ouverts au debut 
    fclose(fichierSortie);

    return 0;
}

