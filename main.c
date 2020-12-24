#include <stdio.h>
#include <stdbool.h>
#include "affichage.c"

//const int N=8;
//const int M=3;



int main() {
    srand(time(0));

//    struct Bonhomme* lambdas = initialiser_bonhommes(N*M);
//    struct Bonhomme* soignants = initialiser_bonhommes(N*M);
//    struct Coordonnees* tableau_virus = initialiser_virus(N*M);

    struct Case matrice[N][M];
    initialiser_matrice(matrice);

    afficher_matrice(matrice, N, M);


    return 0;
}
