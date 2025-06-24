//Salazar Sánchez Karla Gabriela
//Problema:Minimum Fibonacci Terms with Sum Equal to K
//Formula
//(Día de nacimiento * 100) + (Mes de nacimiento * 10) + (Año de nacimiento % 100)
//Ejemplo con mis datos
//(4 * 100) + (01 * 10) + (2005 % 100)
//(400) + (10) + (5) = 415
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool esPrimo(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

void generarFibonacciFiltrado(int fib[], int *n, int K) {
    int a = 0, b = 1, c, i = 1;
    fib[(*n)++] = a; 
    fib[(*n)++] = b; 

    while (1) {
        c = a + b;
        a = b;
        b = c;
        i++;
        if (c > K) break;
        if (!esPrimo(i)) {
            fib[(*n)++] = c;
        }
    }
}

int encontrarMinimoTerminos(int fib[], int n, int K) {
    int usados[1000] = {0};
    int count = 0;
    for (int i = n - 1; i >= 0 && K > 0; i--) {
        if (fib[i] <= K) {
            K -= fib[i];
            usados[count++] = fib[i];
        }
    }

    printf("Terminos para formar K:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", usados[i]);
    }
    printf("\n");
    printf("\n");
    return count;
}

int main() {
    int dia, mes, anio;

    printf("Ingrese su dia de nacimiento: ");
    scanf("%d", &dia);
    printf("Ingrese su mes de nacimiento en numeros: ");
    scanf("%d", &mes);
    printf("Ingrese su anio de nacimiento: ");
    scanf("%d", &anio);

    int K = (dia * 100) + (mes * 10) + (anio % 100);
    printf("\nValor de K calculado: %d\n", K);

    int fib[1000];
    int n = 0;
    generarFibonacciFiltrado(fib, &n, K);
    printf("\n");
    

    printf("Secuencia de Fibonacci:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");
    printf("\n");

    int total = encontrarMinimoTerminos(fib, n, K);
    printf("Numero minimo de terminos usados: %d\n", total);

    return 0;
}

// Salazar Sánchez Karla Gabriela
