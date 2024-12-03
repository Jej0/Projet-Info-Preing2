#!/bin/bash


if [ -z "$1" ]; then
    echo "Erreur : Vous devez fournir le chemin d'un fichier .csv en paramètre."
    exit 1
fi

if [[ -f "$csv_file" && "$csv_file" == *.csv ]]; then
    echo "Le fichier CSV fourni est : $csv_file"
else
    echo "Erreur : Le fichier fourni n'existe pas ou n'est pas un fichier .csv."
    exit 1
fi