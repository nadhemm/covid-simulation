#include "initialisation.c"


const int DEFAULT_COLOR = 0;
const int GREEN_COLOR = 1;
const int ORANGE_COLOR = 2;
const int RED_COLOR = 3;

void printf_colored(char** text, int color){
    if (color == GREEN_COLOR)
        printf("\033[38;5;10m%s\033[0m", text);
    else if (color == ORANGE_COLOR)
        printf("\033[38;5;209m%s\033[0m", text);
    else if (color == RED_COLOR)
        printf("\033[31m%s\033[0m", text);
    else
        printf("%s", text);
}

void afficher_soignant(struct Bonhomme* bonhomme){
    if (bonhomme->est_infecte)
        printf_colored("S", ORANGE_COLOR);
    else
        printf_colored("S", GREEN_COLOR);
}

void afficher_bonhomme(struct Bonhomme* bonhomme){
    if (bonhomme->est_malade)
        printf_colored("M", RED_COLOR);

    else if (bonhomme->est_soignant)
        afficher_soignant(bonhomme);

    else {
        char* output;
        switch (bonhomme->direction){
            case 0:
            case 7:
                output = "\\"; break;
            case 1:
                output = "^"; break;
            case 2:
            case 5:
                output = "/"; break;
            case 3:
                output = "<"; break;
            case 4:
                output = ">"; break;
            case 6:
                output = "v"; break;

            default:
                output = " "; break;
        }
        printf_colored(output, bonhomme->est_infecte ? RED_COLOR : DEFAULT_COLOR);
   }
}

void afficher_case(struct Case kase){ // case is a keyword
    if (kase.bonhomme != NULL)
        afficher_bonhomme(kase.bonhomme);
    else
        printf("$");
}

void afficher_matrice(struct Case matrice[N][M], int n, int m){
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
//            printf("\n%d, %d", i, j);
            afficher_case(matrice[i][j]);
        }
        printf("\n");
    }

}
