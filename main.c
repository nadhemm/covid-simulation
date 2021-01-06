#include <stdio.h>
#include <stdbool.h>
// TODO: add header files, optimize imports
//#include "affichage.c"
#include "simulation.c"

void read_tours_restants(int* tours_restants){
    printf("Combien de tours de simulation souhaitez vous jouer?\n");
    if (scanf("%[^\n]d", tours_restants) < 1) *tours_restants=1; else *(tours_restants)-='0';
}

int main() {
    srand(time(0));

    struct Case matrice[N][M];

    struct Case* lambdas[N*M];
    struct Case* soignants[N*M];
    struct Case* viruses[N*M];

    int nb_lambdas = 0;
    int nb_soignants = 0;
    int nb_viruses = 0;

    initialiser_matrice(matrice, lambdas, &nb_lambdas, soignants, &nb_soignants, viruses, &nb_viruses);

    int tours_restants;
    int etape = 0;
    read_tours_restants(&tours_restants);
    while(tours_restants--){
        jouer_tour_lambdas(matrice, lambdas, &nb_lambdas);
        jouer_tour_soignants();
        verifier_viruses();

        simuler_tour(++etape, matrice);

        if (tours_restants == 0){
            while (getchar() != '\n')
                continue;
            read_tours_restants(&tours_restants);
        }
    }


    return 0;
}
