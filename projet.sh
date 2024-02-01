#/bin/bash

dossier_temp="temp"
dossier_images="images"
projet="projet"
fichier_csv="$1"
mon_programme="mon_programme"


if [ ! -d "$dossier_temp" ]; then # si il n'existe pas de dossier temp on le créer
    mkdir -p "$dossier_temp" #creation de dossier
        echo "le dossier temp a été créer"
else # si il esite on le vide
    rm -rf "$dossier_temp"/* #suppression du dossier avec tous les fichiers contenus ( le /* sert justement a spécifiés les fichier je crois )
    echo "Le dossier temp existe déja, on le vide avant l'exécution"
fi


if [ ! -d "$dossier_images" ]; then #si il n'existe pas de dossier images on le créer
    mkdir "$dossier_images"
    echo "le dossier images a été créer"
else #si il existe un dossier image on le vide
    rm -rf "$dossier_images"/*
    echo "Le dossier images existe déja, on le vide avant l'exécution"
fi


# Vérifie si l'exécutable existe
if ! [ -x "$mon_programme" ]; then
    echo "L'exécutable C n'a pas été trouvé. Compilation en cours..."

    # Compile le programme
    make build

    # Vérifie si la compilation s'est bien passée
    if [ $? -eq 0 ]; then
        echo "La compilation a réussi. L'exécutable a été créé."
    else
        echo "Erreur lors de la compilation. Veuillez corriger les erreurs avant de continuer."
        exit 1
    fi
else
    echo "L'exécutable $programme existe déjà."
fi


read -p "Entrez le traitement (-d1, -d2, -l, -t, -s) : " traitement #la valeur entrée par l'utilisateur sera stockée dans traitement


case $traitement in

-h)
    cat help.txt
;;


-d1)
debut_temps=$(date +%s)  # Enregistrez le temps de début

echo "recupération de la liste des chauffeurs"

awk -F ';' '!seen[$6,$1]++ { conducteurs[$6]++ } END { for (driver in conducteurs) print conducteurs[driver], driver }' $fichier_csv | sort -k1,1nr | head -n 10 | awk '{print $1";" $2" "$3}' > "$dossier_temp/traitement1.txt" # Fusionnez la deuxième et la troisième colonne avec un espace1 et 6 doivent être différentes et je compte ensuite combien de fois il y a chaque conducteurs et je garde que les 10 premiers dans un fichier

fin_temps=$(date +%s)  # Enregistrez le temps de fin
temps_parcourus=$((fin_temps - debut_temps))  # Calculez le temps écoulé en secondes
echo "Temps d'exécution : $temps_parcourus secondes"


# Utiliser Gnuplot pour créer un histogramme horizontal
gnuplot <<GPLOT
    set terminal png
    set output "$dossier_images/traitement_d1.png"
    set xlabel "DRIVER NAMES" rotate by 180 offset 0, -4.5
    set y2label "ROUTE ID"
    set ylabel "Option -d1: Nb Route = f(Driver)"
    set ylabel offset 2,-2
    set boxwidth 0.5 absolute
    set style fill solid
    set xrange [0.5:*]
    set y2range [0:250]
    set y2tics mirror
    set xtics nomirror rotate by 90 font "Arial,8.5"
    set y2tics nomirror rotate by 90

    set xtics offset  0,-6
    set ytics offset -8, 0
    set origin 0, 0.035
    set key off


    set key off
    set style data impulses
    set datafile separator ";"
    plot "$dossier_temp/traitement1.txt" using 1:xtic(2) with boxes title "Distance" axes x1y2
GPLOT


# Rotation de l'image à 90 degrés dans le sens des aiguilles d'une montre avec ImageMagick
convert "$dossier_images/traitement_d1.png" -rotate 90 "$dossier_images/traitement_d1_rotated.png"

;;



-d2)
debut_temps=$(date +%s)

echo "recupération de la liste des chauffeurs"

awk -F ';' '{distances[$6]+=$5} END {for (driver in distances) printf("%.6f %s\n", distances[driver], driver)}' $fichier_csv | sort -nrk1 | head -n 10 | awk '{print $1";" $2" "$3}'> "$dossier_temp/traitement2.txt"


# On effiche les 10 distances les plus grandes classées par ordre décroissant avec le chauffeur associé
fin_temps=$(date +%s)
temps_total=$((fin_temps - debut_temps))
echo "Temps d'exécution : $temps_total secondes"

gnuplot <<GPLOT
    set terminal png
    set output "$dossier_images/traitement_d2.png"
    set xlabel "DRIVER NAMES" rotate by 180 offset 0, -4.5 font "Arial,10"
    set y2label "DISTANCE (Km)"
    set ylabel "Option -d2: Distance = f(Driver)" offset 2, -5
    set ylabel offset 2,-3
    set y2tics offset 0,-1
    set boxwidth 0.5 absolute
    set style fill solid
    set xrange [0.5:*]
    set y2range [0.5:160000]
    set y2tics 20000
    set y2tics mirror
    set xtics nomirror rotate by 90 font "Arial,8.5"
    set y2tics nomirror rotate by 90 font "Arial,7.5"

    set xtics offset  0,-6
    set ytics offset -11, 0
    set origin 0, 0.005
    set key off


    set key off
    set style data impulses
    set datafile separator ";"
    plot "$dossier_temp/traitement2.txt" using 1:xtic(2) with boxes title "Distance" axes x1y2
GPLOT


# Rotation de l'image à 90 degrés dans le sens des aiguilles d'une montre avec ImageMagick
convert "$dossier_images/traitement_d2.png" -rotate 90 "$dossier_images/traitement_d2_rotated.png"
 ;;


-l)
debut_temps=$(date +%s)

echo "récuperation de la liste des plus longs trajets"

awk -F ';' '{distances[$1]+=$5} END {for (driver in distances) printf("%.6f %s\n", distances[driver], driver)}' $fichier_csv | sort -k1,1nr | head -n 10 | sort -k2,2n > "$dossier_temp/traitementl.txt"


fin_temps=$(date +%s)
temps_parcourus=$((fin_temps - debut_temps))
echo "Temps d'exécution : $temps_parcourus secondes"


# Utiliser Gnuplot pour créer le graphique
gnuplot <<GPLOT
    set terminal png
    set output "$dossier_images/traitementl.png"
    set xlabel "ROUTE ID"
    set ylabel "DISTANCE (KM)"
    set title "Traitement -l : Distance = f(Route)"
    set style data histograms
    set style fill solid
    set boxwidth 0.5
    set datafile separator " "
    set yrange[0:*]  # Utilisez set yrange pour spécifier l'intervalle des abscisses
    set ytics 500
    set ytics font "Arial,8"
    set xtics font "Arial,8" rotate by -45
    set key off
    plot "$dossier_temp/traitementl.txt" using 1:xtic(2) with boxes title "Distance"
GPLOT
;;



-t)
    touch traitement_t.txt
    ./mon_programme "$fichier_csv" -t "$dossier_temp/traitement_t.txt"

   
gnuplot <<GPLOT 
	set terminal png
	set output "$dossier_images/traitementh.png"
	set xlabel "TOWN NAMES"
	set ylabel "NB ROUTES"
	set title "Option -t: Nb routes = f(Towns)"
	set style data histograms
	set style fill solid border -1
	set boxwidth 0.5
	set xtics out rotate by -45
	set datafile separator ";"
	plot "$dossier_temp/traitement_t.txt" using 2:xticlabels(1) with histograms title "Colonne 2", '' using 3:xtic(1) with histograms title "Colonne 3"
GPLOT
;;


-s)
    touch traitement_s.txt
    ./mon_programme "$fichier_csv" -s "$dossier_temp/traitement_s.txt"

gnuplot <<GPLOT

    set terminal png
    set output "$dossier_images/traitement_s.png"
    set xlabel "ROUTE ID" font "Arial,7"
    set ylabel "DISTANCE (Km)" font "Arial,7"
    set title "Option -s : Distance = f(Route)" font "Arial,8"
    set style data lines
    set boxwidth 0.5
    SkyBlue = "#87CEEB"
    DarkBlue = "#00008B"
    set datafile separator ";"
    set xrange [*:*]
    set yrange [0:*]
    set ytics font "Arial,7"
    set xtics font "Arial,6"
    set ytics 100
    set xtics rotate by -45  # Incliner les étiquettes sur l'axe x de 45 degrés
    set key font "Arial,8"  # Changer la taille de la légende
    plot "$dossier_temp/traitements.txt" using 0:3:5:xticlabels(2) with filledcurves fc rgb SkyBlue title "Distances Max/Min (Km)", \
         '' using 0:4:xticlabels(2) with lines linestyle 4 lc rgb DarkBlue title 'Distance average(Km)'


GPLOT
;;

*)
    echo "Erreur dans la demande de traitement, il  n'existe pas veuillez réessayer" ;; #si le traitement demandé n'est pas le bon

esac
