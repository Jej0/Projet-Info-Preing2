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

arbre* creerAVL(int id, int cap){
    // Alloue de la mémoire pour un nouveau nœud
    arbre* new = (malloc(sizeof(arbre)));
    if (new == NULL){
        exit(EXIT_FAILURE); // Arrêt immédiat en cas d'erreur d'allocation
    }
    new->identifiant = id; // Initialisation de la valeur
    new->fils_gauche = NULL; // Pas de fils gauche
    new->fils_droit = NULL; // Pas de fils droit
    new->capacite = cap;
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
    a->fils_droit=rotationDroite(a->fils_droit);
    return rotationGauche(a);
}
arbre* doubleRotationDroite(arbre* a){//si le facteur d'équilibre du fg de la racine <= 0 alors rotation simple SINON rotation double
    a->fils_gauche=rotationGauche(a->fils_gauche);
    return rotationDroite(a);
}

arbre* equilibrerAVL(arbre* a){
    if (a->equilibre=2){// sous-arbre droit plus profond
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

arbre * insertionAVL(arbre* a,int id,int cap , int* h){
    if(a==NULL){//l'arbre est vide
        *h=1;//la hauteur vaut 1
        return creerAVL(id,cap);//on crée un noeud
    }
    else if(id<a->identifiant){
        a->fils_gauche=insertionAVL(a->fils_gauche,id,cap,h);//parcours récursif sous-arbre gauche
        *h=-*h;//on est à gauche donc si déséquilibre, nécessairement négatif {-2}
    }
    else if(id>a->identifiant){
         a->fils_droit=insertionAVL(a->fils_droit,id,cap,h);//parcours récursif sous-arbre droit, on est à droite donc si déséquilibre, nécessairement positif {2}
    }
    else{
        *h=0;//on a pas touché à l'arbre, du moins à sa hauteur
        return a;
    }
    if(*h!=0){//h différent de 0 = on a modifié l'arbre donc déséquilibré (gauche ou droite)
       a->equilibre += *h;
       a= equilibrerAVL(a);
       if(a->equilibre== 0){
        *h = 0;
       }else{
        *h = 1;
       }
    }
    return a;
}



long taille_fichier(FILE * fichier) {
    fseek(fichier, 0, SEEK_END);       // Aller à la fin du fichier
    long taille = ftell(fichier);       // Obtenir la position (taille en octets)
    fseek(fichier, 0, SEEK_SET);      // Revenir au début du fichier
    return taille;
}





arbre * lire_construire(FILE * fichier, arbre *abr) {
    fichier = fopen(fichier, "r");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    char buffer[256];
    while(fgets(buffer , sizeof(buffer), fichier)){
    fichier[strcspn(buffer, "\n")] = '\0';

            // Extraire les valeurs id et cap
            int id;
            long cap;
            if (sscanf(buffer, "%d;%ld", &id, &cap) == 2) {
            abr = insertionAVL(abr,id,cap,*h);
        }
    }
    return abr;
}

void affiche_prefixe(arbre *abr){
    if (abr != NULL) {
        printf("Identifiant: %d, Capacité: %d, Consommation: %ld\n", abr->identifiant, abr->capacite, abr->consomateur);
        affiche_prefixe(abr->fils_gauche);
        affiche_prefixe(abr->fils_droit);
    }
}


int main(void) {
arbre * arbre_station = NULL;
arbre_station = lire_construire(station.dat ,arbre_station);
affiche_prefixe(arbre_station);
  return 0;
}
