#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

const int N=8;
const int M=3;

// Sum of probabilities shouldn't exceed 1
const float PROBA_LAMBDA = 0.5;//0.2;
const float PROBA_SOIGNANT = 0.4;//0.1;
const float PROBA_VIRUS = 0.05;

const float PROBA_MALADE_SI_INFECTE = 1/3;

struct Coordonnees {
    int x;
    int y;
};



struct Bonhomme {
//    struct Coordonnees c;
    bool est_soignant;
    bool est_infecte;
    bool est_malade;
    bool est_vivant;

    int direction;
    // This is represented by a char that follows this convention:
    //   012
    //   3X4
    //   567

    char* etat;
};

struct Case {
    struct Coordonnees* Coordonnees;
    bool contaminee_pour_x_prochains_tours;

    struct Bonhomme* bonhomme;
};



//struct Bonhomme* initialiser_bonhommes(length){
//    struct Bonhomme bonhommes[length];
//    return bonhommes;
//}

//struct Coordonnees* initialiser_virus(length){
//    struct Coordonnees virus[length];
//    return virus;
//}

void set_lambda(struct Bonhomme** bonhomme){
    set_bonhomme(bonhomme, false);
}

void set_soignant(struct Bonhomme** bonhomme){
    set_bonhomme(bonhomme, true);
}

void set_bonhomme(struct Bonhomme** bonhomme, bool soignant){
    *bonhomme = (struct Bonhomme*) malloc(sizeof(struct Bonhomme));

    (*bonhomme)->est_soignant = soignant;
    (*bonhomme)->est_vivant = true;
    (*bonhomme)->est_malade = false;
    (*bonhomme)->est_infecte = true;
    (*bonhomme)->direction = rand() % 8;
//    printf("dir: %d %s\n", *bonhomme, soignant? "soignant":"lambda");
}

void initialiser_matrice(struct Case matrice[N][M]){

    int nb_lambdas = 0;
    int nb_soignants = 0;
    int nb_viruses = 0;

    struct Case* lambdas[N*M];
    struct Case* soignants[N*M];
    struct Case* viruses[N*M];

    for(int i=0; i<N; ++i){
        for(int j=0; j<M; ++j){
            float probability =  (float)(rand()) / (float)(RAND_MAX);
            if (probability < PROBA_LAMBDA){
                set_lambda(&matrice[i][j].bonhomme);
//                printf("%d %d lambda %d\n", i, j, (matrice[i][j].bonhomme));
                lambdas[nb_lambdas] = &(matrice[i][j]);
                nb_lambdas++;
                continue;
            }
//            printf("%d %d", i, j);
            probability -= PROBA_LAMBDA;
            if (probability < PROBA_SOIGNANT){
                set_soignant(&matrice[i][j].bonhomme);
                soignants[nb_soignants] = &matrice[i][j];
                nb_soignants++;
//                printf("%d %d soignant %d\n", i, j, matrice[i][j].bonhomme->direction);
                continue;
            }
            matrice[i][j].bonhomme = NULL;

            probability -= PROBA_SOIGNANT;
            if (probability < PROBA_VIRUS){
//                set_virus(matrice[i][j]);
                viruses[nb_viruses] = &matrice[i][j];
                nb_viruses++;
            }
//            printf("%d %d noo \n", i, j, matrice[i][j]);

        }
    }
}

