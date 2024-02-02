CY-Truck Franco Alice et Thibeaudau Kevin

Bienvenue sur le projet CY-Truck. 

Ce projet consiste à traiter l’ensemble de la logistique d’une société national de transport routier. Cette 

application affichera a la fin des différentes demandes possibles des graphiques associés aux 

traitements.

Commencez par insérer le fichier data.csv ( le fichier a trier ) dans le dossier data.

Dans un premier temps vous devez mettre dans le terminal « chmod +rwx * » dans le dossier courant 

afin d’avoir les autorisations requises pour lancer ce programme. 

Pour exécuter le script, il vous suffit de mettre dans le terminal « make ». Cela lancera donc dans un 

premier temps le Makefile qui permet de compiler le programme. C puis de lancer le script Shell.

Par la suite, ce dernier demandera quel traitement vous souhaitez effectuer. 

Les différents traitements sont : 

-d1 : Donne les 10 conducteurs ayant fait le plus de trajet. 

-d2 : Donne les 10 conducteurs ayant parcouru la plus longue distance totale ordonné par ordre 

décroissant. 

-l : Donne les 10 trajets les plus longs, ordonné par le numero d’identifiant croissant. 

-t : Donne les 10 villes les plus traversées et le nombre de fois ou elles ont été villes de départ. 

Ces villes sont triées par ordre alphabétique.

-s : Donne les distances min, max, moyenne, et max-min pour chaque trajet.

-h : affiche toutes les informations nécessaires pour choisir votre traitement.

En cas de doute, choisissez -h. 

Faites bien attention a mettre le - . 

Enfin, une foi cela fait, le programme se compilera tout seul jusqu’à la fin. Pour observer le graphique, 

rendez vous dans le dossier dossier_images qui aura sauvegardé le dernier graphique crée. 
