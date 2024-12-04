#!/bin/bash


if [ $# -eq 0 ]; then
    echo "Erreur : Vous devez fournir le chemin d'un fichier en paramètre."
    exit 1
fi

if [ -e "$1" ]; then
    echo "Le fichier '$1' existe"
else
    echo "Le fichier '$1' n'existe pas"
fi
