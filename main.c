#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>



typedef struct arbre{
  int identifiant;
  long capacite;
  long consomateur;
  int equilibre;
  struct arbre *fils_gauche;
  struct arbre *fils_droit;

}arbre;

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

arbre* creerAVL(int e)
{
    // Alloue de la mémoire pour un nouveau nœud
    arbre* new = (AVL* )malloc(sizeof(AVL));
    if (new == NULL)
    {
        exit(EXIT_FAILURE); // Arrêt immédiat en cas d'erreur d'allocation
    }
    new->identifiant = e; // Initialisation de la valeur
    new->fils_gauche = NULL; // Pas de fils gauche
    new->fils_droit = NULL; // Pas de fils droit
    new->equilibre = 0;    // Facteur d'équilibre initialisé à 0
    return new;
}
arbre * rotationGauche(arbre* a){//si le facteur d'équilibre de la racine =2 => pb à droite donc rotation gauche
    arbre* pivot;
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
arbre * rotationDroite(arbre* a){//si le facteur d'équilibre de la racine =-2 => pb à gauche donc rotation droite
    arbre* pivot;
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

arbre* doubleRotationGauche(arbre* a){//si le facteur d'équilibre du fd de la racine >= 0 alors rotation simple SINON rotation double
    a->fils_droit=rotationDroite(a->droit);
    return rotationGauche(a);
}
arbre* doubleRotationDroite(arbre* a){//si le facteur d'équilibre du fg de la racine <= 0 alors rotation simple SINON rotation double
    a->fils_gauche=rotationGauche(a->gauche);
    return rotationDroite(a);
}


arbre* equilibrerAVL(NoeudAVL* a){
    if (a->eq>=2){// sous-arbre droit plus profond
        if(a->fils_droit->eq>=0){
            return rotationGauche(a);
        }
        else{
            return doubleRotationGauche(a);
        }
    }
    else if (a->eq<=-2){// sous-arbre gauche plus profond
        if(a->fils_gauche->eq<=0){
            return rotationDroite(a);
        }
        else{
            return doubleRotationDroite(a);
        }       
    }
    return a;
}

long taille_fichier(FILE *fichier) {
    fseek(fichier, 0, SEEK_END);       // Aller à la fin du fichier
    long taille = ftell(fichier);       // Obtenir la position (taille en octets)
    fseek(fichier, 0, SEEK_SET);      // Revenir au début du fichier
    return taille;
}





void lire_premiere_ligne(const char *fichier, arbre *abr) {
    FILE *fichier = fopen(fichier, "r");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
char * buffer = malloc((char)*(sizeof(taille_fichier(fichier)))+1);
if(buffer == NULL){
    printf("erreur d'allocation de la mémoire")
    exit(EXIT_FAILURE);
}
int n_ligne = 0;
arbre *racine = NULL;
while(fgets(buffer , sizeof(buffer), file)){
    buffer[strcspn(buffer, "\n")] = '\0';
    n_ligne++;
}





int main(void) {
  printf("Hello Axel\n");
  return 0;
}
