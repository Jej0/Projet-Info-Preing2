#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>



typedef struct Arbre{
  int identifiant;
  long capacite;
  long consomateur;
  int equilibre;
  int hauteur;
  struct Arbre *fils_gauche;
  struct Arbre *fils_droit;

}Arbre;



int max(int a, int b){
    if(b>a){
        return b;
    }else{
        return a;
    }
}

int min(int a, int b){
    if(b>a){
        return a;
    }else{
        return b;
    }
}

void afficherAVL(Arbre* a) {

    if (a == NULL)
        return;


    printf("%d ", a->identifiant);
    // Affiche les éléments à gauche
    afficherAVL(a->fils_gauche);

    // Affiche la racine


    // Affiche les éléments à droite
    afficherAVL(a->fils_droit);

}

Arbre* creerNoeud(int id, long cap)
{
    // Alloue de la mémoire pour un nouveau nœud
    Arbre* noeud = malloc(sizeof(Arbre));
    if (noeud == NULL)
    {
        exit(EXIT_FAILURE); // Arrêt immédiat en cas d'erreur d'allocation
    }
    noeud->identifiant = id; // Initialisation de la valeur
    noeud->fils_gauche = NULL; // Pas de fils gauche
    noeud->fils_droit = NULL; // Pas de fils droit
    noeud->capacite = cap;
    noeud->equilibre = 0;    // Facteur d'équilibre initialisé à 0
    return noeud;
}
Arbre * rotationGauche(Arbre* a){//si le facteur d'équilibre de la racine =2 => pb à droite donc rotation gauche
    Arbre* pivot;
    int eq_a;
    int eq_p;
    pivot=a->fils_droit;//le pivot est le fils droit de a
    a->fils_droit=pivot->fils_gauche;//le fils gauche du pivot devient le fils droit de a (une valeur ou NULL)
    pivot->fils_gauche=a;//a devient le fils gauche de pivot
    eq_a=a->equilibre;
    eq_p=pivot->equilibre;
    a->equilibre=eq_a - max(eq_p,0)-1;
    pivot->equilibre= min(min(eq_a-2,eq_a+eq_p-2),eq_p-1);
    a=pivot;//pivot devient racine
    return a;
}
Arbre * rotationDroite(Arbre* a){//si le facteur d'équilibre de la racine =-2 => pb à gauche donc rotation droite
    Arbre* pivot;
    int eq_a;
    int eq_p;
    pivot=a->fils_gauche;//le pivot est le fils droit de a
    a->fils_gauche=pivot->fils_droit;//le fils gauche du pivot devient le fils droit de a (une valeur ou NULL)
    pivot->fils_droit=a;//a devient le fils gauche de pivot
    eq_a=a->equilibre;
    eq_p=pivot->equilibre;
    a->equilibre=eq_a - max(eq_p,0) + 1;
    pivot->equilibre= min(min(eq_a+2,eq_a+eq_p+2),eq_p+1);
    a=pivot;//pivot devient racine
    return a;
}

Arbre* doubleRotationGauche(Arbre* a){//si le facteur d'équilibre du fd de la racine >= 0 alors rotation simple SINON rotation double
    a->fils_droit=rotationDroite(a->fils_droit);
    return rotationGauche(a);
}
Arbre* doubleRotationDroite(Arbre* a){//si le facteur d'équilibre du fg de la racine <= 0 alors rotation simple SINON rotation double
    a->fils_gauche=rotationGauche(a->fils_gauche);
    return rotationDroite(a);
}


Arbre* equilibrerAVL(Arbre* a){
    if (a->equilibre>=2){// sous-arbre droit plus profond
        if(a->fils_droit->equilibre>=0){
            return rotationGauche(a);
        }
        else{
            return doubleRotationGauche(a);
        }
    }
    else if (a->equilibre<=-2){// sous-arbre gauche plus profond
        if(a->fils_gauche->equilibre<=0){
            return rotationDroite(a);
        }
        else{
            return doubleRotationDroite(a);
        }       
    }
    return a;
}


Arbre* insertionAVL(Arbre* racine, int id, long cap) {
    // Si l'arbre est vide, créer un nouveau nœud
    if (racine == NULL) {
        return creerNoeud(id, cap);
    }

    // Insertion dans le sous-arbre gauche
    if (id < racine->identifiant) {
        racine->fils_gauche = insertionAVL(racine->fils_gauche, id, cap);
    }
    // Insertion dans le sous-arbre droit
    else if (id > racine->identifiant) {
        racine->fils_droit = insertionAVL(racine->fils_droit, id, cap);
    } else {
        // Si l'identifiant existe déjà, ne pas insérer (pas de doublons dans l'arbre AVL)
        return racine;
    }

    // Mise à jour du facteur d'équilibre
    int hauteur_gauche = racine->fils_gauche ? racine->fils_gauche->equilibre : -1;
    int hauteur_droite = racine->fils_droit ? racine->fils_droit->equilibre : -1;
    racine->equilibre = hauteur_droite - hauteur_gauche;
    afficherAVL(racine);
    printf("\n");
    // Équilibrer l'arbre si nécessaire
    return equilibrerAVL(racine);
}






// long taille_fichier(FILE *fichier) {
//     fseek(fichier, 0, SEEK_END);       // Aller à la fin du fichier
//     long taille = ftell(fichier);       // Obtenir la position (taille en octets)
//     fseek(fichier, 0, SEEK_SET);      // Revenir au début du fichier
//     return taille;
// }





// Arbre * onlitpuisonconstruit(const char *fichier, Arbre *abr) {
//     FILE *fichier = fopen(fichier, "r");
//     if (!fichier) {
//         printf("Erreur lors de l'ouverture du fichier");
//         exit(EXIT_FAILURE);
//     }
// char buffer[256];
// while(fgets(buffer , sizeof(buffer), file)){
//    fichier[strcspn(line, "\n")] = '\0';

//         // Extraire les valeurs id et cap
//         int id;
//         long cap;
//         if (sscanf(line, "%d;%ld", &id, &cap) == 2) {
//             if(abr == NULL){
//                 abr = creerNoeud(id,cap);
//             }else{
//                 abr = insererAVL
//             }
// }



