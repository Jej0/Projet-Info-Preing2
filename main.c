#include <stdio.h>
#include<stdlib.h>




typedef struct arbre{
  int identifiant;
  int capacite;
  int consomateur;
  int eq;
  struct arbre *fils_gauche;
  struct arbre *fils_droit;

}arbre;

arbre* creerAVL(int e)
{
    // Alloue de la mémoire pour un nouveau nœud
    AVL* new = (AVL* )malloc(sizeof(AVL));
    if (new == NULL)
    {
        exit(EXIT_FAILURE); // Arrêt immédiat en cas d'erreur d'allocation
    }
    new->identifiant = e; // Initialisation de la valeur
    new->fils_gauche = NULL; // Pas de fils gauche
    new->fils_droit = NULL; // Pas de fils droit
    new->eq = 0;    // Facteur d'équilibre initialisé à 0
    return new;
}



int main(void) {
  printf("Hello Axel\n");
  return 0;
}
