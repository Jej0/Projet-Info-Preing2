#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


typedef struct Arbre{
  int identifiant;
  long capacite;
  long consommation;
  int consommations;
  int equilibre;
  int hauteur;
  struct Arbre *fils_gauche;
  struct Arbre *fils_droit;

}Arbre;


void afficherAVL(Arbre* a);
Arbre* creerNoeud(int id, long cap);
Arbre* equilibrerAVL(Arbre* a);

Arbre * insertionAVL(Arbre* a,int id,long cap , int* h);