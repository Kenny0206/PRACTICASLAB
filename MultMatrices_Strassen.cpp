//Problema 3
//Multiplicación de matrices por Strassen
#include <stdio.h>
#include <stdlib.h>

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

void multiplicarStrassen(int **A, int **B, int **C, int n) {
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

    int **M1 = crearMatriz(nuevoTam);
    int **M2 = crearMatriz(nuevoTam);
    int **M3 = crearMatriz(nuevoTam);
    int **M4 = crearMatriz(nuevoTam);
    int **M5 = crearMatriz(nuevoTam);
    int **M6 = crearMatriz(nuevoTam);
    int **M7 = crearMatriz(nuevoTam);

    int **temp1 = crearMatriz(nuevoTam);
    int **temp2 = crearMatriz(nuevoTam);


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

    sumar(A11, A22, temp1, nuevoTam);
    sumar(B11, B22, temp2, nuevoTam);
    multiplicarStrassen(temp1, temp2, M1, nuevoTam);

    sumar(A21, A22, temp1, nuevoTam);
    multiplicarStrassen(temp1, B11, M2, nuevoTam);

    restar(B12, B22, temp1, nuevoTam);
    multiplicarStrassen(A11, temp1, M3, nuevoTam);

    restar(B21, B11, temp1, nuevoTam);
    multiplicarStrassen(A22, temp1, M4, nuevoTam);

    sumar(A11, A12, temp1, nuevoTam);
    multiplicarStrassen(temp1, B22, M5, nuevoTam);

    restar(A21, A11, temp1, nuevoTam);
    sumar(B11, B12, temp2, nuevoTam);
    multiplicarStrassen(temp1, temp2, M6, nuevoTam);

    restar(A12, A22, temp1, nuevoTam);
    sumar(B21, B22, temp2, nuevoTam);
    multiplicarStrassen(temp1, temp2, M7, nuevoTam);

    sumar(M1, M4, temp1, nuevoTam);
    restar(temp1, M5, temp2, nuevoTam);
    sumar(temp2, M7, temp1, nuevoTam);

    sumar(M3, M5, temp2, nuevoTam);

    sumar(M2, M4, C, nuevoTam); 

    restar(M1, M2, temp2, nuevoTam);
    sumar(temp2, M3, temp1, nuevoTam);
    sumar(temp1, M6, temp2, nuevoTam);

    for (int i = 0; i < nuevoTam; i++) {
        for (int j = 0; j < nuevoTam; j++) {
            C[i][j] = temp1[i][j];                             
            C[i][j + nuevoTam] = temp2[i][j];                  
            C[i + nuevoTam][j] = C[i + nuevoTam][j];           
            C[i + nuevoTam][j + nuevoTam] = temp2[i][j];       
        }
    }

    // Liberar memoria
    liberarMatriz(A11, nuevoTam); liberarMatriz(A12, nuevoTam);
    liberarMatriz(A21, nuevoTam); liberarMatriz(A22, nuevoTam);
    liberarMatriz(B11, nuevoTam); liberarMatriz(B12, nuevoTam);
    liberarMatriz(B21, nuevoTam); liberarMatriz(B22, nuevoTam);
    liberarMatriz(M1, nuevoTam); liberarMatriz(M2, nuevoTam);
    liberarMatriz(M3, nuevoTam); liberarMatriz(M4, nuevoTam);
    liberarMatriz(M5, nuevoTam); liberarMatriz(M6, nuevoTam);
    liberarMatriz(M7, nuevoTam);
    liberarMatriz(temp1, nuevoTam); liberarMatriz(temp2, nuevoTam);
}

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

    multiplicarStrassen(A, B, C, n);

    printf("\nResultado de la multiplicacion entre las matrices A y B declaradas anteriormente:\n");
    imprimirMatriz(C, n);

    liberarMatriz(A, n);
    liberarMatriz(B, n);
    liberarMatriz(C, n);

    return 0;
}

