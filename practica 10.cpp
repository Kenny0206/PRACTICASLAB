#include <stdio.h>
#include <string.h>

#define MAX_WEIGHT 4
#define NUM_ITEMS 4

typedef struct {
    char nombre[10];
    int peso;
    int valor;
    char inicial;
} Objeto;

int main() {
    Objeto objetos[NUM_ITEMS] = {
        {"Guitarra", 1, 1500, 'G'},
        {"Estereo", 4, 3000, 'S'},
        {"Laptop", 3, 2000, 'L'},
        {"iPhone", 1, 2000, 'I'}
    };

    int dp[NUM_ITEMS + 1][MAX_WEIGHT + 1];
    char path[NUM_ITEMS + 1][MAX_WEIGHT + 1][10];
printf("<>----------------------------------------------------------------<>\n");
    printf("Objetos disponibles para hechar en la mochila:\n");
    for (int i = 0; i < NUM_ITEMS; i++) {
        printf("%s - Peso: %dlb, Valor: $%d\n", objetos[i].nombre, objetos[i].peso, objetos[i].valor);
    }
    printf("\n");

    for (int i = 0; i <= NUM_ITEMS; i++) {
        for (int w = 0; w <= MAX_WEIGHT; w++) {
            dp[i][w] = 0;
            strcpy(path[i][w], "");
        }
    }

    for (int i = 1; i <= NUM_ITEMS; i++) {
        for (int w = 0; w <= MAX_WEIGHT; w++) {
            if (objetos[i-1].peso <= w) {
                int incluir = objetos[i-1].valor + dp[i-1][w - objetos[i-1].peso];
                int excluir = dp[i-1][w];
                if (incluir > excluir) {
                    dp[i][w] = incluir;
                    strcpy(path[i][w], path[i-1][w - objetos[i-1].peso]);
                    int len = strlen(path[i][w]);
                    path[i][w][len] = objetos[i-1].inicial;
                    path[i][w][len + 1] = '\0';
                } else {
                    dp[i][w] = excluir;
                    strcpy(path[i][w], path[i-1][w]);
                }
            } else {
                dp[i][w] = dp[i-1][w];
                strcpy(path[i][w], path[i-1][w]);
            }
        }
    }

    printf("<>----------------------------------------------------------------<>\n");
    printf("Objetos finales seleccionados para hechar en la mochila:\n");

    for (int i = NUM_ITEMS, w = MAX_WEIGHT; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            printf("- %s (Peso: %d lb, Valor: $%d)\n", objetos[i-1].nombre, objetos[i-1].peso, objetos[i-1].valor);
            w -= objetos[i-1].peso;
        }
    }
    
printf("\n");
 printf("<>----------------------------------------------------------------<>\n");
printf("Valor maximo en la mochila de %d lb: $%d\n", MAX_WEIGHT, dp[NUM_ITEMS][MAX_WEIGHT]);
 printf("<>----------------------------------------------------------------<>\n");
    printf("Tabla final:\n");

    for (int i = 1; i <= NUM_ITEMS; i++) {
        for (int w = 1; w <= MAX_WEIGHT; w++) {
            printf("$%d %-4s\t", dp[i][w], path[i][w]);
        }
        printf("\n");
    }

    return 0;
}

