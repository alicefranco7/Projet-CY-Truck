DOSSIER_DATA = data
DOSSIER_C = progc
FICHIER_DATA = $(DOSSIER_DATA)/data.csv
FICHIER_EXECUTABLE = mon_programme

all :	script

clean :  
	rm $(FICHIER_EXECUTABLE)

build : 
	gcc $(DOSSIER_C)/main.c $(DOSSIER_C)/fonctionAVL.c $(DOSSIER_C)/traitement_t.c $(DOSSIER_C)/traitement_s.c -o $(FICHIER_EXECUTABLE)

run : 
	./$(FICHIER_EXECUTABLE)

script :
	sh projet.sh $(FICHIER_DATA)


#commande pour afficher les options du projet
help :
	sh projet.sh $(FICHIER_DATA) -h

