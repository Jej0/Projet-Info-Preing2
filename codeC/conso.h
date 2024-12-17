#include "header.h"
//#include "AVL.h"

void affichePrefixe(Arbre *abr){
    if (abr != NULL) {
        printf("Identifiant: %d, Capacité: %ld, Consommateurs: %d, Consommation: %ld\n", abr->identifiant, abr->capacite, abr->consommateurs, abr->consommation);
        affichePrefixe(abr->fils_gauche);
        affichePrefixe(abr->fils_droit);
    }
}


Arbre *creerNoeud(int id, long capacite) {
    Arbre *noeud = malloc(sizeof(Arbre));
    if (noeud == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    noeud->identifiant = id;
    noeud->capacite = capacite;
    noeud->consommation = 0;    // Initialisé à 0
    noeud->consommateurs = 0;   // Initialisé à 0
    noeud->equilibre = 0;       // Facteur d'équilibre initialisé à 0
    noeud->hauteur = 1;         // Hauteur initiale
    noeud->fils_gauche = NULL;
    noeud->fils_droit = NULL;

    return noeud;
}

int hauteur(Arbre *noeud) {
    return noeud ? noeud->hauteur : 0;
}
int calculerEquilibre(Arbre *noeud) {
    return noeud ? hauteur(noeud->fils_gauche) - hauteur(noeud->fils_droit) : 0;
}
void mettreAJour(Arbre *noeud) {
    noeud->hauteur = 1 + (hauteur(noeud->fils_gauche) > hauteur(noeud->fils_droit) ? hauteur(noeud->fils_gauche) : hauteur(noeud->fils_droit));
    noeud->equilibre = calculerEquilibre(noeud);
}
Arbre *rotationGauche(Arbre *noeud) {
    Arbre *pivot = noeud->fils_droit;
    noeud->fils_droit = pivot->fils_gauche;
    pivot->fils_gauche = noeud;

    mettreAJour(noeud);
    mettreAJour(pivot);

    return pivot;
}
Arbre *rotationDroite(Arbre *noeud) {
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

    if (noeud->equilibre > 1) { // Sous-arbre gauche plus profond
        if (noeud->fils_gauche->equilibre < 0) { // Rotation gauche-droite nécessaire
            return doubleRotationGaucheDroite(noeud);
        }
        return rotationDroite(noeud); // Rotation droite simple
    }

    if (noeud->equilibre < -1) { // Sous-arbre droit plus profond
        if (noeud->fils_droit->equilibre > 0) { // Rotation droite-gauche nécessaire
            return doubleRotationDroiteGauche(noeud);
        }
        return rotationGauche(noeud); // Rotation gauche simple
    }

    return noeud; // Aucun déséquilibre
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
        return noeud; // ID déjà présent, pas d'insertion
    }

    return equilibrer(noeud); // Rééquilibrer après insertion
}
Arbre *construireAVLDepuisFichier(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier stations.txt");
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

    char line[300]; // Buffer pour lire chaque ligne

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

void exporterAVLDansCSV(Arbre *root, const char *nomFichier) {
    if (!root) return; // Si l'arbre est vide, rien à écrire

    FILE *file = fopen(nomFichier, "w");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        return;
    }

    // Écrire les en-têtes des colonnes
    fprintf(file, "Identifiant:Capacite:Consommation\n");

    // Fonction récursive pour parcourir l'arbre en parcours infixe
    void parcoursInfixe(Arbre *node) {
        if (node) {
            parcoursInfixe(node->fils_gauche);
            fprintf(file, "%d:%ld:%ld\n", node->identifiant, node->capacite, node->consommation);
            parcoursInfixe(node->fils_droit);
        }
    }

    // Lancer le parcours à partir de la racine
    parcoursInfixe(root);

    fclose(file); // Fermer le fichier après écriture
}





