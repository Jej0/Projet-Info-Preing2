#include "AVL.h"
#include "conso.h"
#include "header.h"

int main() {

    FILE *file = fopen("../tmp/stations", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    Arbre* racine = NULL;
    int h;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Supprimer le saut de ligne (si présent)
        // line[strcspn(line, "\n")] = '\0';

        int id;
        long cap;
        if (sscanf(line, "%d;%ld", &id, &cap) == 2) {
            // printf("%d, %ld\n", id, cap);
            racine = insertionAVL(racine, id, cap, &h);

        } else {
            printf("erreur");
        }
    }
    
    fclose(file);
    affichePrefixe(racine);


    ajouterConsommateursDepuisFichier(racine, consomateurs);
}