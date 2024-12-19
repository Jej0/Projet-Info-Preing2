#include "conso.h"


int main() {

    Arbre * racine = construireAVLDepuisFichier("../tmp/stations");
    //affichePrefixe(racine);
    //printf("\n");
    ajouterConsommateursDepuisFichier(racine, "../tmp/consommateurs");

    // affichePrefixe(racine);


    FILE* nom_fichier = fopen("../tmp/nom", "r"); // Ouvre le fichier en mode lecture
    if (nom_fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1; // Retourne une erreur si le fichier ne peut pas être ouvert
    }

    char ligne[256]; // Buffer pour stocker la ligne
    fgets(ligne, sizeof(ligne), nom_fichier);

    fclose(nom_fichier);


    char chemin[300] = "../tests/";
    



    exporterAVLDansCSV(racine, strcat(chemin, ligne));


}