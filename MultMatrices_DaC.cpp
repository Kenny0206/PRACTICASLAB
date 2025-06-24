//Problema 2
//Multiplicación de matrices por forma DaC (Divide y venceras)
#include <stdio.h>
#include <stdlib.h>

void sumar(int **A, int **B, int **resultado, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            resultado[i][j] = A[i][j] + B[i][j];
}

void restar(int **A, int **B, int **resultado, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            resultado[i][j] = A[i][j] - B[i][j];
}

int **crearMatriz(int n) {
    int **matriz = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        matriz[i] = (int *)calloc(n, sizeof(int));
    return matriz;
}

void liberarMatriz(int **matriz, int n) {
    for (int i = 0; i < n; i++)
        free(matriz[i]);
    free(matriz);
}

void multiplicarDAC(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int nuevoTam = n / 2;
	//SubMatrices
    int **A11 = crearMatriz(nuevoTam);
    int **A12 = crearMatriz(nuevoTam);
    int **A21 = crearMatriz(nuevoTam);
    int **A22 = crearMatriz(nuevoTam);
    int **B11 = crearMatriz(nuevoTam);
    int **B12 = crearMatriz(nuevoTam);
    int **B21 = crearMatriz(nuevoTam);
    int **B22 = crearMatriz(nuevoTam);
    int **C11 = crearMatriz(nuevoTam);
    int **C12 = crearMatriz(nuevoTam);
    int **C21 = crearMatriz(nuevoTam);
    int **C22 = crearMatriz(nuevoTam);
    int **M1 = crearMatriz(nuevoTam);
    int **M2 = crearMatriz(nuevoTam);

   
    for (int i = 0; i < nuevoTam; i++) {
        for (int j = 0; j < nuevoTam; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + nuevoTam];
            A21[i][j] = A[i + nuevoTam][j];
            A22[i][j] = A[i + nuevoTam][j + nuevoTam];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + nuevoTam];
            B21[i][j] = B[i + nuevoTam][j];
            B22[i][j] = B[i + nuevoTam][j + nuevoTam];
        }
    }


    multiplicarDAC(A11, B11, M1, nuevoTam);
    multiplicarDAC(A12, B21, M2, nuevoTam);
    sumar(M1, M2, C11, nuevoTam);

    multiplicarDAC(A11, B12, M1, nuevoTam);
    multiplicarDAC(A12, B22, M2, nuevoTam);
    sumar(M1, M2, C12, nuevoTam);

    multiplicarDAC(A21, B11, M1, nuevoTam);
    multiplicarDAC(A22, B21, M2, nuevoTam);
    sumar(M1, M2, C21, nuevoTam);

    multiplicarDAC(A21, B12, M1, nuevoTam);
    multiplicarDAC(A22, B22, M2, nuevoTam);
    sumar(M1, M2, C22, nuevoTam);

    // Combinar submatrices en una nueva matriz. (C)
    for (int i = 0; i < nuevoTam; i++) {
        for (int j = 0; j < nuevoTam; j++) {
            C[i][j] = C11[i][j];
            C[i][j + nuevoTam] = C12[i][j];
            C[i + nuevoTam][j] = C21[i][j];
            C[i + nuevoTam][j + nuevoTam] = C22[i][j];
        }
    }

    // Liberar memoria
    liberarMatriz(A11, nuevoTam); liberarMatriz(A12, nuevoTam);
    liberarMatriz(A21, nuevoTam); liberarMatriz(A22, nuevoTam);
    liberarMatriz(B11, nuevoTam); liberarMatriz(B12, nuevoTam);
    liberarMatriz(B21, nuevoTam); liberarMatriz(B22, nuevoTam);
    liberarMatriz(C11, nuevoTam); liberarMatriz(C12, nuevoTam);
    liberarMatriz(C21, nuevoTam); liberarMatriz(C22, nuevoTam);
    liberarMatriz(M1, nuevoTam);  liberarMatriz(M2, nuevoTam);
}

// Función para imprimir matrices
void imprimirMatriz(int **matriz, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", matriz[i][j]);
        printf("\n");
    }
}

int main() {
    int n = 4; 
    int **A = crearMatriz(n);
    int **B = crearMatriz(n);
    int **C = crearMatriz(n);

    //Valores para A y B
    int valor = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = valor++;

    valor = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = valor++;

    printf("Matriz A:\n");
    imprimirMatriz(A, n);

    printf("\nMatriz B:\n");
    imprimirMatriz(B, n);

    multiplicarDAC(A, B, C, n);

    printf("\nResultado de la multiplicacion entre las matrices A y B declaradas anteriormente:\n");
    imprimirMatriz(C, n);

    liberarMatriz(A, n);
    liberarMatriz(B, n);
    liberarMatriz(C, n);

    return 0;
}


