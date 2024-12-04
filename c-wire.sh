#!/bin/bash


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

if [[ ("$2" = "hvb" && "$3" = "all") || () ]]; then
    echo "Le 3eme paramètre doit être différent de 'hvb all', 'hvb indv', 'hva all', 'hva indiv'."
    exit 1
fi