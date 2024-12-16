#include "header.h"
#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Arbre *insererConsommation(Arbre *a, int id, long capacite, long consommation, int *h) {
    a = insertionAVL(a, id, capacite, h); 
    if (a->identifiant == id) {
        a->consommation += consommation; 
    }
    return a;
}

Arbre *lireFichierEtConstruireAVL(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }

    Arbre *root = NULL;
    char line[256];
    int h = 0;

    
    while (fgets(line, sizeof(line), file)) {
        int id;
        long capacite;
        long consommation = 0;

        
        if (sscanf(line, "%d;%ld;%ld", &id, &capacite, &consommation) == 3) {
            root = insererConsommation(root, id, capacite, consommation, &h);
        }
    }

    fclose(file);
    return root;
}

