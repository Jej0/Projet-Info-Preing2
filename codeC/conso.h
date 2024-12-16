#include "header.h"
#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Arbre *insererConsommation(Arbre *a, int id, long consommation) {
    if (a == NULL) {
        // Si l'arbre est vide ou la station n'est pas trouvée, retourne NULL
        printf("Erreur : La station avec l'ID %d n'existe pas.\n", id);
        return NULL;
    }

    if (id < a->identifiant) {
        // Parcours du sous-arbre gauche
        return insererConsommation(a->fils_gauche, id, consommation);
    } else if (id > a->identifiant) {
        // Parcours du sous-arbre droit
        return insererConsommation(a->fils_droit, id, consommation);
    } else {
        // Si la station est trouvée, on ajoute la consommation
        a->consommation += consommation;
        return a;
    }
}



void ajouterConsommateursDepuisFichier(Arbre *root, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier des consommateurs");
        return;
    }

    char line[300];

    while (fgets(line, sizeof(line), file)) {
        int id;
        long consommation;

        // Lire l'ID de la station et la consommation
        if (sscanf(line, "%d;%ld", &id, &consommation) == 2) {
            if (insererConsommation(root, id, consommation) == NULL) {
                // Si la station n'existe pas, l'erreur est déjà affichée
                continue;
            }
        }
    }

    fclose(file);
}


