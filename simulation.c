#include "affichage.c"


int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct Case* move(struct Case matrice[N][M], struct Case* lambda, int new_x, int new_y){
    matrice[new_x][new_y].bonhomme = lambda->bonhomme;
    lambda->bonhomme = NULL;
    return &matrice[new_x][new_y];
}

void jouer_tour_lambda(struct Case matrice[N][M], struct Case* lambdas[N*M], int lambda_index, int* nb_lambdas){
    struct Case* lambda = lambdas[lambda_index];
    int x = lambda->coordonnees->x;
    int y = lambda->coordonnees->y;

    // Si bonhomme malade
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

    bool moved = false;

    // Check for nearby virus
    for(int i=0; i<8; ++i){
        struct Case current_case = matrice[(N+x+dx[i])%N][(M+y+dy[i])%M]; // We use mod % to represent the fact that the grid is cylindrical
        if (current_case.contaminee_pour_x_prochains_tours > 0){
            lambda->bonhomme->est_infecte = true;
            float probability =  (float)(rand()) / (float)(RAND_MAX);
            if (probability < PROBA_MALADE_SI_INFECTE)
                lambda->bonhomme->est_malade = true;
            goto m_label;
        }
    }
    // No nearby virus move to next cell
    for(int i=0; i<8; ++i){
        struct Case current_case = matrice[(N+x+dx[i])%N][(M+y+dy[i])%M]; // We use mod % to represent the fact that the grid is cylindrical
        if (current_case.bonhomme == NULL){
            float probability =  (float)(rand()) / (float)(RAND_MAX);
            if (probability < PROBA_MOUVEMENT)
                lambdas[i] = move(matrice, lambda, (N+x+dx[i])%N, (M+y+dy[i])%M);
            break;
        }
    }
    m_label:
        {}
}

void jouer_tour_lambdas(struct Case matrice[N][M], struct Case* lambdas[N*M], int* nb_lambdas){
    for(int i=0; i<(*nb_lambdas); ++i)
            jouer_tour_lambda(matrice, lambdas, i, nb_lambdas);
}

void jouer_tour_soignants(){

}

void verifier_viruses(){

}

