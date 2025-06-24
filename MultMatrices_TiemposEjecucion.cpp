//Tabla de Tiempos de Ejecucion
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int** crearMatriz(int n) {
    int **matriz = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        matriz[i] = (int *)malloc(n * sizeof(int)); 
    return matriz;
}

void liberarMatriz(int **matriz, int n) {
    for (int i = 0; i < n; i++)
        free(matriz[i]);
    free(matriz);
}

void llenarMatrizAleatoria(int **matriz, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matriz[i][j] = rand() % 10;
}

void sumar(int **A, int **B, int **res, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res[i][j] = A[i][j] + B[i][j];
}

void restar(int **A, int **B, int **res, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res[i][j] = A[i][j] - B[i][j];
}

void multiplicacionTradicional(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

void multiplicarDAC(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int mitad = n / 2;
    int **A11 = crearMatriz(mitad), **A12 = crearMatriz(mitad),
        **A21 = crearMatriz(mitad), **A22 = crearMatriz(mitad),
        **B11 = crearMatriz(mitad), **B12 = crearMatriz(mitad),
        **B21 = crearMatriz(mitad), **B22 = crearMatriz(mitad),
        **C11 = crearMatriz(mitad), **C12 = crearMatriz(mitad),
        **C21 = crearMatriz(mitad), **C22 = crearMatriz(mitad),
        **M1 = crearMatriz(mitad), **M2 = crearMatriz(mitad);

    for (int i = 0; i < mitad; i++)
        for (int j = 0; j < mitad; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mitad];
            A21[i][j] = A[i + mitad][j];
            A22[i][j] = A[i + mitad][j + mitad];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mitad];
            B21[i][j] = B[i + mitad][j];
            B22[i][j] = B[i + mitad][j + mitad];
        }

    multiplicarDAC(A11, B11, M1, mitad);
    multiplicarDAC(A12, B21, M2, mitad);
    sumar(M1, M2, C11, mitad);

    multiplicarDAC(A11, B12, M1, mitad);
    multiplicarDAC(A12, B22, M2, mitad);
    sumar(M1, M2, C12, mitad);

    multiplicarDAC(A21, B11, M1, mitad);
    multiplicarDAC(A22, B21, M2, mitad);
    sumar(M1, M2, C21, mitad);

    multiplicarDAC(A21, B12, M1, mitad);
    multiplicarDAC(A22, B22, M2, mitad);
    sumar(M1, M2, C22, mitad);

    for (int i = 0; i < mitad; i++)
        for (int j = 0; j < mitad; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mitad] = C12[i][j];
            C[i + mitad][j] = C21[i][j];
            C[i + mitad][j + mitad] = C22[i][j];
        }

    liberarMatriz(A11, mitad); liberarMatriz(A12, mitad);
    liberarMatriz(A21, mitad); liberarMatriz(A22, mitad);
    liberarMatriz(B11, mitad); liberarMatriz(B12, mitad);
    liberarMatriz(B21, mitad); liberarMatriz(B22, mitad);
    liberarMatriz(C11, mitad); liberarMatriz(C12, mitad);
    liberarMatriz(C21, mitad); liberarMatriz(C22, mitad);
    liberarMatriz(M1, mitad); liberarMatriz(M2, mitad);
}

void multiplicarStrassen(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int mitad = n / 2;
    int **A11 = crearMatriz(mitad), **A12 = crearMatriz(mitad),
        **A21 = crearMatriz(mitad), **A22 = crearMatriz(mitad),
        **B11 = crearMatriz(mitad), **B12 = crearMatriz(mitad),
        **B21 = crearMatriz(mitad), **B22 = crearMatriz(mitad),
        **M1 = crearMatriz(mitad), **M2 = crearMatriz(mitad),
        **M3 = crearMatriz(mitad), **M4 = crearMatriz(mitad),
        **M5 = crearMatriz(mitad), **M6 = crearMatriz(mitad),
        **M7 = crearMatriz(mitad),
        **T1 = crearMatriz(mitad), **T2 = crearMatriz(mitad);

    for (int i = 0; i < mitad; i++)
        for (int j = 0; j < mitad; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mitad];
            A21[i][j] = A[i + mitad][j];
            A22[i][j] = A[i + mitad][j + mitad];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mitad];
            B21[i][j] = B[i + mitad][j];
            B22[i][j] = B[i + mitad][j + mitad];
        }

    sumar(A11, A22, T1, mitad); sumar(B11, B22, T2, mitad); multiplicarStrassen(T1, T2, M1, mitad);
    sumar(A21, A22, T1, mitad); multiplicarStrassen(T1, B11, M2, mitad);
    restar(B12, B22, T1, mitad); multiplicarStrassen(A11, T1, M3, mitad);
    restar(B21, B11, T1, mitad); multiplicarStrassen(A22, T1, M4, mitad);
    sumar(A11, A12, T1, mitad); multiplicarStrassen(T1, B22, M5, mitad);
    restar(A21, A11, T1, mitad); sumar(B11, B12, T2, mitad); multiplicarStrassen(T1, T2, M6, mitad);
    restar(A12, A22, T1, mitad); sumar(B21, B22, T2, mitad); multiplicarStrassen(T1, T2, M7, mitad);

    int **C11 = crearMatriz(mitad), **C12 = crearMatriz(mitad),
        **C21 = crearMatriz(mitad), **C22 = crearMatriz(mitad);

    sumar(M1, M4, T1, mitad); restar(T1, M5, T2, mitad); sumar(T2, M7, C11, mitad);
    sumar(M3, M5, C12, mitad);
    sumar(M2, M4, C21, mitad);
    restar(M1, M2, T1, mitad); sumar(T1, M3, T2, mitad); sumar(T2, M6, C22, mitad);

    for (int i = 0; i < mitad; i++)
        for (int j = 0; j < mitad; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mitad] = C12[i][j];
            C[i + mitad][j] = C21[i][j];
            C[i + mitad][j + mitad] = C22[i][j];
        }

    liberarMatriz(A11, mitad); liberarMatriz(A12, mitad);
    liberarMatriz(A21, mitad); liberarMatriz(A22, mitad);
    liberarMatriz(B11, mitad); liberarMatriz(B12, mitad);
    liberarMatriz(B21, mitad); liberarMatriz(B22, mitad);
    liberarMatriz(M1, mitad); liberarMatriz(M2, mitad); liberarMatriz(M3, mitad);
    liberarMatriz(M4, mitad); liberarMatriz(M5, mitad); liberarMatriz(M6, mitad); liberarMatriz(M7, mitad);
    liberarMatriz(C11, mitad); liberarMatriz(C12, mitad); liberarMatriz(C21, mitad); liberarMatriz(C22, mitad);
    liberarMatriz(T1, mitad); liberarMatriz(T2, mitad);
}

int main() {
    srand(time(NULL));
    printf("n\tStrassen\tDaC\t\tTradicional\n");

    for (int n = 2; n <= 64; n *= 2) {
        int **A = crearMatriz(n);
        int **B = crearMatriz(n);
        int **C = crearMatriz(n);

        llenarMatrizAleatoria(A, n);
        llenarMatrizAleatoria(B, n);

        clock_t inicio, fin;
        double tiempoTrad, tiempoDAC, tiempoStrassen;

        inicio = clock();
        multiplicacionTradicional(A, B, C, n);
        fin = clock();
        tiempoTrad = (double)(fin - inicio) / CLOCKS_PER_SEC;

        inicio = clock();
        multiplicarDAC(A, B, C, n);
        fin = clock();
        tiempoDAC = (double)(fin - inicio) / CLOCKS_PER_SEC;

        inicio = clock();
        multiplicarStrassen(A, B, C, n);
        fin = clock();
        tiempoStrassen = (double)(fin - inicio) / CLOCKS_PER_SEC;

        printf("%d\t%.6f\t%.6f\t%.6f\n", n, tiempoTrad, tiempoDAC, tiempoStrassen);

        liberarMatriz(A, n);
        liberarMatriz(B, n);
        liberarMatriz(C, n);
    }

    return 0;
}

