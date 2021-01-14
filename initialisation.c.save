#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int N = 10;
int M = 10;

// Sum of probabilities shouldn't exceed 1
const float PROBA_LAMBDA = 0.2;
const float PROBA_SOIGNANT = 0.1;
const float PROBA_VIRUS = 0.05;


const float PROBA_MALADE_SI_INFECTE = 1 / 3;
const float PROBA_MORT_SI_MALADE = 0.1;
const float PROBA_MOUVEMENT = 0.7;
const float PROBA_DIRECTION_TOUR_PRECEDANT = 0.75;

const float PROBA_DISPERSION_VIRUS = 0.1;
const float VIRULENCE = 0.1;


struct Coordonnees {
    int x;
    int y;
};


struct Bonhomme {
    struct Coordonnees c;
    bool est_soignant;
    bool est_infecte;
    bool est_malade;

    int direction;
    // This is represented by a char that follows this convention:
    //   012
    //   3X4
    //   567

};

struct Case {
    struct Coordonnees *coordonnees;
    int contaminee_pour_x_prochains_tours;

    struct Bonhomme *bonhomme;
};

void flag_virus(struct Case* kase, bool has_virus) {
    if (has_virus)
        (kase)->contaminee_pour_x_prochains_tours = 4;
    else
        (kase)->contaminee_pour_x_prochains_tours = 0;
}

void set_bonhomme(struct Bonhomme **bonhomme, bool soignant) {
    *bonhomme = (struct Bonhomme *) malloc(sizeof(struct Bonhomme));

    (*bonhomme)->est_soignant = soignant;
    (*bonhomme)->est_malade = false;
    (*bonhomme)->est_infecte = false;
    (*bonhomme)->direction = rand() % 8;
}


void set_lambda(struct Bonhomme **bonhomme) {
    set_bonhomme(bonhomme, false);
}

void set_soignant(struct Bonhomme **bonhomme) {
    set_bonhomme(bonhomme, true);
}

void initialiser_matrice(struct Case matrice[N][M], struct Case *lambdas[N * M], int *nb_lambdas,
                         struct Case *soignants[N * M], int *nb_soignants, struct Case *viruses[N * M],
                         int *nb_viruses) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            matrice[i][j].coordonnees = (struct Coordonnees *) malloc(sizeof(struct Coordonnees));
            matrice[i][j].coordonnees->x = i;
            matrice[i][j].coordonnees->y = j;

            float probability = (float) (rand()) / (float) (RAND_MAX);
            if (probability < PROBA_LAMBDA) {
                flag_virus(&(matrice[i][j]), false);
                set_lambda(&matrice[i][j].bonhomme);
                lambdas[(*nb_lambdas)++] = &(matrice[i][j]);
                continue;
            }
            probability -= PROBA_LAMBDA;

            if (probability < PROBA_SOIGNANT) {
                flag_virus(&(matrice[i][j]), false);
                set_soignant(&matrice[i][j].bonhomme);
                soignants[(*nb_soignants)++] = &matrice[i][j];
                continue;
            }
            probability -= PROBA_SOIGNANT;
            matrice[i][j].bonhomme = NULL;

            if (probability < PROBA_VIRUS) {
                flag_virus(&(matrice[i][j]), true);
                viruses[(*nb_viruses)++] = &matrice[i][j];
                continue;
            }
            flag_virus(&(matrice[i][j]), false);
//            printf("%d\n", matrice[i][j].contaminee_pour_x_prochains_tours);
        }
    }
}

