//Problema 1
//Multiplicación de matrices por forma tradicional
#include <stdio.h>
#include <stdlib.h>

void multiplicacionTradicional(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


int** crearMatriz(int n) {
    int **matriz = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matriz[i] = (int *)malloc(n * sizeof(int));
    }
    return matriz;
}


void liberarMatriz(int **matriz, int n) {
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}


void imprimirMatriz(int **matriz, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 2;

    
    int **A = crearMatriz(n);
    int **B = crearMatriz(n);
    int **C = crearMatriz(n);

    //Matriz 1 Valores de(A)
    A[0][0] = 1; A[0][1] = 2;
    A[1][0] = 3; A[1][1] = 1;

	//Matriz 2 Valores de (B)
    B[0][0] = 0; B[0][1] = 1;
    B[1][0] = 2; B[1][1] = 1;

    
    multiplicacionTradicional(A, B, C, n);

    
    printf("Resultado de la multiplicacion entre las matrices A y B declaradas anteriormente:\n");
    imprimirMatriz(C, n);

    
    liberarMatriz(A, n);
    liberarMatriz(B, n);
    liberarMatriz(C, n);

    return 0;
}

