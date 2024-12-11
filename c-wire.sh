#!/bin/bash

####################################

nom_executable="a.out"
nom_fichier_lecture="c-wire_v00.dat"
fichier_cible_sation="tmp/station.dat"
fichier_cible_fils="tmp/fils.dat"
####################################


arg1=""
arg2=""
arg3=""
arg4=""

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
    echo
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
    echo "existe pas"
fi

if [ -d "tmp" ]; then

    rm -r tmp
    mkdir tmp
else
    mkdir tmp
fi

if [ ! -d "graphs" ]; then
    mkdir graphs
fi

touch tmp/station.dat
touch tmp/fils.dat



awk -F';' '2 != "-"'
tmp/c-wire_v00.dat > 
tmp/station.dat 
