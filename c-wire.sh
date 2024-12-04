#!/bin/bash


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
    echo "(optionnel) [<value>] : Valeur positive (>0) pour séléctionner une centrale spécifique"
}

for arg in "$@"; do
    if [[ "$arg" == "-h" || "$arg" == "--help" ]]; then
        afficher_aide
        exit 0
    fi
done


if [ $# -lt 3 ]; then
    echo "Erreur : Vous devez fournir au moins 3 arguments."
    exit 1
fi

if [ -f "$1" ]; then
    echo "Le fichier '$1' existe"
else
    echo "Le fichier '$1' n'existe pas"
    exit 1
fi

if [[ "$2" != "hvb" && "$2" != "hva" && "$2" != "lv" ]]; then
    echo "Le 2eme paramètre doit être 'hvb', 'hva ou 'lv'."
    exit 1
fi

if [[ "$3" != "comp" && "$3" != "indiv" && "$3" != "all" ]]; then
    echo "Le 3eme paramètre doit être 'comp', 'indv', 'all'."
    exit 1
fi

if [[ ("$2" = "hvb" && "$3" = "all") || ("$2" = "hvb" && "$3" = "indiv") || ("$2" = "hva" && "$3" = "all") || ("$2" = "hva" && "$3" = "indiv") ]]; then
    echo "Les stations hvb et hva ne sont pas reliées aux particuliers"
    exit 1
fi

if [ -n "$4" ]; then
    if [[ "$4" -gt 0 ]]; then
        echo "arg 4 est positif"
    else
        echo "mauvais arg 4"
        exit 1
    fi
else   
    echo "Il n'y a pas de 4e paramètre"
fi


