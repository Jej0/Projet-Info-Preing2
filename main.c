#include <stdio.h>
#include <stdlib.h>

typedef struct arbre{
  int identifiant;
  int capacité;
  int consomateur;
  struct arbre *fils_gauche;
  struct arbre *fils_droit;
}arbre;

int main(void) {
  printf("Hello World test 1 2 c'est flopesque\n");
  return 0;
}
