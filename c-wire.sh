#!/bin/bash

####################################
nom_executable="codeC/prog"
chemin_makefile="codeC"
fichier_lecture=""
####################################




function afficher_aide {

    echo "Utilisation : $0 [-h | --help] <path> <hvb | hva | lv> <comp | indiv | all> [<value>]"
    echo
    echo "Options:"
    echo
    echo "(optionnel) [-h | --help] : Affiche le menu d'aide"
    echo
    echo "(obligatoire) <path> : Chemin vers le fichier de donnée"
    echo
    echo "(obligatoire) <hvb | hva | lv> : Le type de station séléctionnée ('hvb' : station haut voltage, 'hva' : station moyen  voltage, 'lv' : station bas voltage)"
    echo
    echo "(obligatoire) <comp | indiv | all> : Le type de client séléctionné ('comp' : les entreprises, 'indiv' : les particuliers, 'all' : tout le monde)"
    echo 
    echo "(optionnel) [<value>] : Valeur entre 1 et 5 pour séléctionner une centrale spécifique"
}

for arg in "$@"; do
    if [[ "$arg" == "-h" || "$arg" == "--help" ]]; then
        afficher_aide
        exit 0
    fi
done


if [ $# -lt 3 ]; then
    echo "Erreur : Vous devez fournir au moins 3 arguments."
    echo
    afficher_aide
    exit 1
fi

if [ -f "$1" ]; then
    echo "Le fichier '$1' existe"
    nom_fichier_lecture="$1"
else
    echo "Erreur : Le fichier '$1' n'existe pas"
    echo
    afficher_aide
    exit 1
fi

if [[ "$2" != "hvb" && "$2" != "hva" && "$2" != "lv" ]]; then
    echo "Erreur : Le 2eme paramètre doit être 'hvb', 'hva ou 'lv'."
    echo
    afficher_aide
    exit 1
fi

if [[ "$3" != "comp" && "$3" != "indiv" && "$3" != "all" ]]; then
    echo "Erreur : Le 3eme paramètre doit être 'comp', 'indv', 'all'."

    afficher_aide
    exit 1
fi

if [[ ("$2" = "hvb" && "$3" = "all") || ("$2" = "hvb" && "$3" = "indiv") || ("$2" = "hva" && "$3" = "all") || ("$2" = "hva" && "$3" = "indiv") ]]; then
    echo "Erreur : Les stations hvb et hva ne sont pas reliées aux particuliers"
    echo
    afficher_aide
    exit 1
fi

if [ -n "$4" ]; then
    if [ "$4" -ge 1 ] && [ "$4" -le 5 ]; then
        echo "arg 4 est entre 1 et 5"
    else
        echo "Erreur : Le paramètre 4 doit être entr 1 et 5"
        echo
        afficher_aide
        exit 1
    fi
else   
    echo "Il n'y a pas de 4e paramètre"
fi


if [ -f "$nom_executable" ]; then
    echo "existe"
else 
    echo "existe pas, création prog"

    if [ ! -f "$chemin_makefile/Makefile" ]; then
        echo "Erreur : Aucun fichier Makefile trouvé dans '$chemin_makefile'."
        exit 1
    fi

    make -f "Makefile" -C "$chemin_makefile"

    if [ $? -eq 0 ]; then
        echo "Makefile exécuté avec succès depuis '$chemin_makefile'."
        chmod 777 codeC/prog
    else
        echo "Erreur lors de l'exécution du Makefile."
        exit 1
    fi

fi

if [ -d "tmp" ]; then
    rm -r tmp #suppr
    mkdir tmp # Crée le dossier
else
    mkdir tmp # Crée le dossier
fi

if [ ! -d "graphs" ]; then
    mkdir graphs # Crée le dossier
fi

if [ ! -d "tests" ]; then
  mkdir tests  # Crée le dossier
fi



colonne_station=""
if [ -n "$4" ]; then
    echo "$2_$3_$4.csv" > tmp/nom
    if [[ "$2" = "hvb" ]]; then
        echo "Station HV-B" >> tmp/nom
        awk -F';' -v centrale="$4" '$2 != "-" && $3 == "-" && $4 == "-" && $1 == centrale && $7 != "-" {print $2 ";" $7}' "$nom_fichier_lecture" > tmp/stations
        colonne_station="2"
    elif [[ "$2" = "hva" ]]; then
    echo "Station HV-A" >> tmp/nom
        awk -F';' -v centrale="$4" '$3 != "-" && $4 == "-" && $1 == centrale && $7 != "-" {print $3 ";" $7}' "$nom_fichier_lecture" > tmp/stations
        colonne_station="3"
    elif [[ "$2" = "lv" ]]; then
        echo "Station LV" >> tmp/nom
        awk -F';' -v centrale="$4" '$4 != "-" && $1 == centrale && $7 != "-" {print $4 ";" $7}' "$nom_fichier_lecture" > tmp/stations
        colonne_station="4"
    fi

    if [[ "$3" = "comp" ]]; then
        echo "(entreprises)" >> tmp/nom
        awk -F';' -v col="$colonne_station" -v centrale="$4" '$col != "-" && $5 != "-" && $6 == "-" && $1 == centrale && $8 != "-" {print $col ";" $8}' "$nom_fichier_lecture" > tmp/consommateurs
    elif [[ "$3" = "indiv" ]]; then
        echo "(particuliers)" >> tmp/nom
        awk -F';' -v col="$colonne_station" -v centrale="$4" '$col != "-" && $5 == "-" && $6 != "-" && $1 == centrale && $8 != "-" {print $col ";" $8}' "$nom_fichier_lecture" > tmp/consommateurs
    elif [[ "$3" = "all" ]]; then
        echo "(tous)" >> tmp/nom
        awk -F';' -v col="$colonne_station" -v centrale="$4" '($5 != "-" || $6 != "-") && $col != "-" && $8 != "-" && $1 == centrale {print $col ";" $8}' "$nom_fichier_lecture" > tmp/consommateurs
    fi

else
    echo "$2_$3.csv" >> tmp/nom
    if [[ "$2" == "hvb" ]]; then
        echo "Station HV-B" >> tmp/nom
        awk -F';' '$2 != "-" && $3 == "-" && $4 == "-" && $7 != "-" {print $2 ";" $7}' "$nom_fichier_lecture" > tmp/stations
        colonne_station="2"
    elif [[ "$2" == "hva" ]]; then
        echo "Station HV-A" >> tmp/nom
        awk -F';' '$3 != "-" && $4 == "-" && $7 != "-" {print $3 ";" $7}' "$nom_fichier_lecture" > tmp/stations
        colonne_station="3"
    elif [[ "$2" == "lv" ]]; then
        echo "Station LV" >> tmp/nom
        awk -F';' '$4 != "-" && $7 != "-" {print $4 ";" $7}' "$nom_fichier_lecture" > tmp/stations
        colonne_station="4"
    fi

    if [[ "$3" = "comp" ]]; then
        echo "(entreprises)" >> tmp/nom
        awk -F';' -v col="$colonne_station" '$col != "-" && $5 != "-" && $6 == "-" && $8 != "-" {print $col ";" $8}' "$nom_fichier_lecture" > tmp/consommateurs
    elif [[ "$3" = "indiv" ]]; then
        echo "(particuliers)" >> tmp/nom
        awk -F';' -v col="$colonne_station" '$col != "-" && $6 != "-" && $5 == "-" && $8 != "-" {print $col ";" $8}' "$nom_fichier_lecture" > tmp/consommateurs
    elif [[ "$3" = "all" ]]; then
        echo "(tous)" >> tmp/nom
        awk -F';' -v col="$colonne_station" '($5 != "-" || $6 != "-") && $col != "-" && $8 != "-" {print $col ";" $8}' "$nom_fichier_lecture" > tmp/consommateurs
    fi

fi



cd codeC

(time ./prog) 2>&1