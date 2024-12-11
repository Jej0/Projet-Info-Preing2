#!/bin/bash

####################################
nom_executable="a.out"
fichier_lecture=""
fichier_cible_sation="tmp/station.dat"
fichier_cible_consomateurs="tmp/consomateurs.dat"
####################################



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
else
    if [[ "$2" = "hvb" ]]; then 
        arg2="2"
    elif [[ "$2" = "hva" ]]; then
        arg2="3"
    elif [[ "$2" = "lv" ]];then
        arg2="4"
    fi
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
touch tmp/consomateurs.dat



if [ -n "$4" ]; then
    awk -F';' -v col="$arg2" -v centrale="$4" '$col != "-" && $1 == centrale' "$nom_fichier_lecture" > "$fichier_cible_sation"

    if [[ "$3" = "comp" ]]; then
        awk -F';' -v col="$arg2" -v centrale="$4" '$5 != "-" && $col != "-" && $1 == centrale' "$nom_fichier_lecture" > "$fichier_cible_consomateurs"
    elif [[ "$3" = "indiv" ]]; then
        awk -F';' -v col="$arg2" -v centrale="$4" '$6 != "-" && $col != "-" && $1 == centrale' "$nom_fichier_lecture" > "$fichier_cible_consomateurs"
    elif [[ "$3" = "all" ]]; then
        awk -F';' -v col="$arg2" -v centrale="$4" '($5 != "-" || $6 != "-") && $col != "-" && $1 == centrale' "$nom_fichier_lecture" >> "$fichier_cible_consomateurs"
    fi
else
    awk -F';' -v col="$arg2" '$col != "-"' "$nom_fichier_lecture" > "$fichier_cible_sation"
    if [[ "$3" = "comp" ]]; then
        awk -F';' -v col="$arg2" '$5 != "-" && $col != "-"' "$nom_fichier_lecture" > "$fichier_cible_consomateurs"
    elif [[ "$3" = "indiv" ]]; then
        awk -F';' -v col="$arg2" '$6 != "-" && $col != "-"' "$nom_fichier_lecture" > "$fichier_cible_consomateurs"
    elif [[ "$3" = "all" ]]; then
        awk -F';' -v col="$arg2" '$5 != "-" || $6 != "-" && $col != "-"' "$nom_fichier_lecture" >> "$fichier_cible_consomateurs"
    fi
fi