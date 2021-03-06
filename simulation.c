#include "affichage.c"


int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct Case *move(struct Case matrice[N][M], struct Case** lambda, int new_x, int new_y) {
    matrice[new_x][new_y].bonhomme = (*lambda)->bonhomme;
    (*lambda)->bonhomme = NULL;

    lambda = &matrice[new_x][new_y];
//    (*lambda)->coordonnees->x = new_x;
//    (*lambda)->coordonnees->y = new_y;
    return &matrice[new_x][new_y];
}

void jouer_tour_lambda(struct Case matrice[N][M], struct Case* lambdas[N * M], int lambda_index, int *nb_lambdas) {
    struct Case* lambda = lambdas[lambda_index];
    int x = lambda->coordonnees->x;
    int y = lambda->coordonnees->y;

//     Si bonhomme malade
//    if (lambda->bonhomme->est_malade){
//        float probability =  (float)(rand()) / (float)(RAND_MAX);
//        if (probability < PROBA_MORT_SI_MALADE){
//            lambda->bonhomme->est_malade = true;
//            lambda->bonhomme = NULL;
//
////            // remove from lambda table
//            lambdas[lambda_index] = lambdas[(*nb_lambdas)-1];
//            (*nb_lambdas)--;
//        }
//    }

    // Check for nearby virus
    for (int i = 0; i < 8; ++i) {
        // We use mod % to represent the fact that the grid is cylindrical
        struct Case current_case = matrice[(N + x + dx[i]) % N][(M + y + dy[i]) % M];
        if (current_case.contaminee_pour_x_prochains_tours > 0) {
            lambda->bonhomme->est_infecte = true;
            float probability = (float) (rand()) / (float) (RAND_MAX);
            if (probability < PROBA_MALADE_SI_INFECTE)
                lambda->bonhomme->est_malade = true;
            goto lambda_label;
        }
    }
    // No nearby virus move to next cell
    for (int i = 0; i < 8; ++i) {
        // We use mod % to represent the fact that the grid is cylindrical
        struct Case current_case = matrice[(N + x + dx[i]) % N][(M + y + dy[i]) % M];
        if (current_case.bonhomme == NULL) {
            float probability = (float) (rand()) / (float) (RAND_MAX);
            if (probability < PROBA_MOUVEMENT){
                move(matrice, &(lambdas[i]), (N + x + dx[i]) % N, (M + y + dy[i]) % M) ;
            }
            break;
        }
    }
    lambda_label:{}
}


void jouer_tour_soignant(struct Case matrice[N][M], struct Case* soignants[N * M], int soignant_index, int *nb_soignants) {
    struct Case* soignant = soignants[soignant_index];
    int x = soignant->coordonnees->x;
    int y = soignant->coordonnees->y;

//     Si bonhomme malade
//    if (soignant->bonhomme->est_malade){
//        float probability =  (float)(rand()) / (float)(RAND_MAX);
//        if (probability < PROBA_MORT_SI_MALADE){
//            soignant->bonhomme->est_malade = true;
//            soignant->bonhomme = NULL;
//
////            // remove from soignant table
//            soignants[soignant_index] = soignants[(*nb_soignants)-1];
//            (*nb_soignants)--;
//        }
//    }

    // Check for nearby virus
    for (int i = 0; i < 8; ++i) {
        // We use mod % to represent the fact that the grid is cylindrical
        struct Case current_case = matrice[(N + x + dx[i]) % N][(M + y + dy[i]) % M];
        if (current_case.contaminee_pour_x_prochains_tours > 0) {
            soignant->bonhomme->est_infecte = true;
            float probability = (float) (rand()) / (float) (RAND_MAX);
            if (probability < PROBA_MALADE_SI_INFECTE)
                soignant->bonhomme->est_malade = true;
            goto soignant_label;
        }
    }
    // No nearby virus move to next cell
    for (int i = 0; i < 8; ++i) {
        // We use mod % to represent the fact that the grid is cylindrical
        struct Case current_case = matrice[(N + x + dx[i]) % N][(M + y + dy[i]) % M];
        if (current_case.bonhomme == NULL) {
            float probability = (float) (rand()) / (float) (RAND_MAX);
            if (probability < PROBA_MOUVEMENT){
                move(matrice, &(soignants[i]), (N + x + dx[i]) % N, (M + y + dy[i]) % M) ;
            }
            break;
        }
    }
    soignant_label:{}
}

void jouer_tour_lambdas(struct Case matrice[N][M], struct Case *lambdas[N * M], int *nb_lambdas) {
    for (int i = 0; i < (*nb_lambdas); ++i)
        jouer_tour_lambda(matrice, lambdas, i, nb_lambdas);
}

void jouer_tour_soignants(struct Case matrice[N][M], struct Case *soignants[N * M], int *nb_soignants) {
    for (int i = 0; i < (*nb_soignants); ++i)
        jouer_tour_soignant(matrice, soignants, i, nb_soignants);
}


void verifier_viruses(struct Case matrice[N][M], struct Case *viruses[N * M], int *nb_viruses) {
//    for(int i=0; i<*nb_viruses; ++i){
//        if(viruses[i]->contaminee_pour_x_prochains_tours == 0){
//        // Delete Virus from table
//            viruses[i] = viruses[(*nb_viruses)-1];
//            (*nb_viruses)--;
//            i--;// Do NOT forget to consider the last virus!
//        }
//    }
}

