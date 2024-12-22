#include "header.h"
//#include "AVL.h"

void affichePrefixe(Arbre *abr){
    if (abr != NULL) {
        printf("Identifiant: %d, Capacité: %ld, Consommateurs: %d, Consommation: %ld\n", abr->identifiant, abr->capacite, abr->consommateurs, abr->consommation);
        affichePrefixe(abr->fils_gauche);
        affichePrefixe(abr->fils_droit);
    }
}


Arbre *creerNoeud(int id, long capacite) {//fonction qui crée le noeud
    Arbre *noeud = malloc(sizeof(Arbre));
    if (noeud == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    noeud->identifiant = id;
    noeud->capacite = capacite;
    noeud->consommation = 0;    // Initialise à 0
    noeud->consommateurs = 0;   // Initialise à 0
    noeud->equilibre = 0;       // Facteur d'équilibre initialisé à 0
    noeud->hauteur = 1;         // Hauteur initiale
    noeud->fils_gauche = NULL;
    noeud->fils_droit = NULL;

    return noeud;
}

int hauteur(Arbre *noeud) {//fonction qui calcule la hauteur
    return noeud ? noeud->hauteur : 0;
}
int calculerEquilibre(Arbre *noeud) {//fonction qui calcule l'équilibre
    return noeud ? hauteur(noeud->fils_gauche) - hauteur(noeud->fils_droit) : 0;
}
void mettreAJour(Arbre *noeud) {//va nous servir pour les rotations
    noeud->hauteur = 1 + (hauteur(noeud->fils_gauche) > hauteur(noeud->fils_droit) ? hauteur(noeud->fils_gauche) : hauteur(noeud->fils_droit));
    noeud->equilibre = calculerEquilibre(noeud);
}
Arbre *rotationGauche(Arbre *noeud) {//fonction rotation gauche qui permet de rééquilibrer l'arbre
    Arbre *pivot = noeud->fils_droit;
    noeud->fils_droit = pivot->fils_gauche;
    pivot->fils_gauche = noeud;

    mettreAJour(noeud);
    mettreAJour(pivot);

    return pivot;
}
Arbre *rotationDroite(Arbre *noeud) {//fonction rotation gauche qui permet de rééquilibrer l'arbre
    Arbre *pivot = noeud->fils_gauche;
    noeud->fils_gauche = pivot->fils_droit;
    pivot->fils_droit = noeud;

    mettreAJour(noeud);
    mettreAJour(pivot);

    return pivot;
}
Arbre *doubleRotationGaucheDroite(Arbre *noeud) {
    noeud->fils_gauche = rotationGauche(noeud->fils_gauche);
    return rotationDroite(noeud);
}
Arbre *doubleRotationDroiteGauche(Arbre *noeud) {
    noeud->fils_droit = rotationDroite(noeud->fils_droit);
    return rotationGauche(noeud);
}
Arbre *equilibrer(Arbre *noeud) {
    mettreAJour(noeud);

    if (noeud->equilibre > 1) { // Sous-arbre gauche le plus profond
        if (noeud->fils_gauche->equilibre < 0) { // Rotation gauche-droite nécessaire
            return doubleRotationGaucheDroite(noeud);
        }
        return rotationDroite(noeud); // Rotation droite simple
    }

    if (noeud->equilibre < -1) { // Sous-arbre droit le plus profond
        if (noeud->fils_droit->equilibre > 0) { // Rotation droite-gauche nécessaire
            return doubleRotationDroiteGauche(noeud);
        }
        return rotationGauche(noeud); // Rotation gauche simple
    }

    return noeud; // aucun déséquilibre
}
Arbre *insererStation(Arbre *noeud, int id, long capacite) {
    if (noeud == NULL) {
        return creerNoeud(id, capacite); // Créer un nouveau nœud si l'arbre est vide
    }

    if (id < noeud->identifiant) {
        noeud->fils_gauche = insererStation(noeud->fils_gauche, id, capacite);
    } else if (id > noeud->identifiant) {
        noeud->fils_droit = insererStation(noeud->fils_droit, id, capacite);
    } else {
        printf("Erreur : La station avec l'ID %d existe déjà.\n", id);
        return noeud; // ID déjà présent donc pas d'insertion
    }

    return equilibrer(noeud); // Rééquilibrer après l'insertion
}
Arbre *construireAVLDepuisFichier(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier stations");
        return NULL;
    }

    Arbre *root = NULL;
    char line[300];

    while (fgets(line, sizeof(line), file)) {
        int id;
        long capacite;

        if (sscanf(line, "%d;%ld", &id, &capacite) == 2) {
            root = insererStation(root, id, capacite);
        }
    }

    fclose(file);
    return root;
}


Arbre *insererConsommation(Arbre *a, int id, long consommation) {
    if (a == NULL) {
        // Si la station n'existe pas, afficher une erreur et retourner NULL
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
        // Si la station est trouvée, mettre à jour ses données
        a->consommation += consommation; // Ajouter la consommation
        a->consommateurs += 1;           // Incrémenter le nombre de consommateurs
        return a;
    }
}



void ajouterConsommateursDepuisFichier(Arbre *root, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier des consommateurs");
        return;
    }

    char line[300]; // pour lire chaque ligne

    while (fgets(line, sizeof(line), file)) {
        int id;
        long consommation;

        // Extraire l'ID de la station et la consommation
        if (sscanf(line, "%d;%ld", &id, &consommation) == 2) {
            // Mettre à jour la station correspondante
            if (insererConsommation(root, id, consommation) == NULL) {
                // Si la station n'existe pas, afficher un message d'erreur (géré dans insererConsommation)
                continue;
            }
        }
    }

    fclose(file);
}

void ajouterDansListeMin(Arbre *liste_min[], Arbre *station) {
    for (int i = 0; i < 10; i++) {
        if (liste_min[i] == NULL || (station->capacite - station->consommation) < (liste_min[i]->capacite - liste_min[i]->consommation)) {
            // Décaler les éléments pour insérer la station
            for (int j = 9; j > i; j--) {
                liste_min[j] = liste_min[j - 1];
            }
            liste_min[i] = station;
            return;
        }
    }
}

void ajouterDansListeMax(Arbre *liste_max[], Arbre *station) {
    for (int i = 0; i < 10; i++) {
        if (liste_max[i] == NULL || (station->capacite - station->consommation) > (liste_max[i]->capacite - liste_max[i]->consommation)) {
            // Décaler les éléments pour insérer la station
            for (int j = 9; j > i; j--) {
                liste_max[j] = liste_max[j - 1];
            }
            liste_max[i] = station;
            return;
        }
    }
}

void parcoursInfixePourMinMax(Arbre *racine, Arbre *liste_min[], Arbre *liste_max[]) {
    if (!racine) return;

    // Parcours du sous-arbre gauche
    parcoursInfixePourMinMax(racine->fils_gauche, liste_min, liste_max);

    // Ajout dans les listes min et max
    ajouterDansListeMin(liste_min, racine);
    ajouterDansListeMax(liste_max, racine);

    // Parcours du sous-arbre droit
    parcoursInfixePourMinMax(racine->fils_droit, liste_min, liste_max);
}


void exporterExtremeStations(Arbre **liste_min, Arbre **liste_max, const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "w");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier pour l'exportation");
        return;
    }

    // En-têtes
    fprintf(fichier, "Min and Max 'capacity-load' extreme nodes\n");
    fprintf(fichier, "Station LV:Capacité:Consommation (tous)\n");


    // Écrire les nœuds de la liste_max
    for (int i = 0; i < 10; i++) {
        if (liste_max[i]) {
            fprintf(fichier, "%d:%ld:%ld\n", liste_max[i]->identifiant, liste_max[i]->capacite, liste_max[i]->consommation);
        }
    }

    // Écrire les nœuds de la liste_min
    for (int i = 0; i < 10; i++) {
        if (liste_min[i]) {
            fprintf(fichier, "%d:%ld:%ld\n", liste_min[i]->identifiant, liste_min[i]->capacite, liste_min[i]->consommation);
        }
    }



    fclose(fichier);
    printf("Exportation réussie dans le fichier %s\n", nomFichier);
}

void minMaxStationLV(Arbre *racine, char * nomFichier) {
    Arbre *liste_min[10] = {NULL}; // Initialiser la liste des 10 plus petites consommations
    Arbre *liste_max[10] = {NULL}; // Initialiser la liste des 10 plus grandes consommations

    // Parcours de l'arbre pour remplir les listes
    parcoursInfixePourMinMax(racine, liste_min, liste_max);

    char chemin[300] = "../tests/";
    strcat(chemin, nomFichier);
    strcat(chemin, "_minmax.csv");

    printf("%s", chemin);
    exporterExtremeStations(liste_min, liste_max, chemin);
}
// Fonction récursive pour parcourir l'arbre en parcours infixe
 void parcoursInfixe(Arbre *abr , FILE * fichier_CSV){
        if (abr) {
            parcoursInfixe(abr->fils_gauche , fichier_CSV);
            fprintf(fichier_CSV, "%d:%ld:%ld\n", abr->identifiant, abr->capacite, abr->consommation);
            parcoursInfixe(abr->fils_droit , fichier_CSV);
        }
    }


void exporterAVLDansCSV(Arbre *racine, char *nomFichier) {
    if (!racine) return; // Si l'arbre est vide, rien à écrire

    FILE *fichier_CSV = fopen(nomFichier, "w"); // crée le fichier CSV que l'on rend
    if (!fichier_CSV) {
        perror("Erreur lors de l'ouverture du fichier CSV");
        return;
    }

    FILE *fichier_info = fopen("../tmp/nom", "r"); 
    if (!fichier_info) {
        perror("Erreur lors de l'ouverture du fichier nom");
        return;
    }

    char nom_station[300];
    char info_conso[300];


    fgets(nom_station, sizeof(nom_station), fichier_info);
    fgets(nom_station, sizeof(nom_station), fichier_info);
    nom_station[strcspn(nom_station, "\n")] = '\0';

    fgets(info_conso, sizeof(info_conso), fichier_info);
    info_conso[strcspn(info_conso, "\n")] = '\0';

    fclose(fichier_info);

    // Écrire les en-têtes des colonnes
    fprintf(fichier_CSV, "%s:Capacité:Consommation %s\n", nom_station, info_conso);


    // Lancer le parcours à partir de la racine
    parcoursInfixe(racine , fichier_CSV);

    fclose(fichier_CSV); // Fermer le fichier après écriture

    if (strcmp(nom_station, "Station LV") == 0 && strcmp(info_conso, "(tous)") == 0) {

        nomFichier[strlen(nomFichier) - 4] = '\0';
        minMaxStationLV(racine, nomFichier);
    }

}





