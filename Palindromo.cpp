#include <stdio.h>
#include <stdlib.h>

// Funcion para invertir un n�mero
int invertirNum(int x) {
    int pal = 0;
    while (x > 0) {
        int digit = x % 10;
        pal = pal * 10 + digit;
        x /= 10;
    }
    return pal;
}

// Funci�n para verificar si es un pal�ndromo
int esPalindromo(int x) {
    if (x < 0 || (x % 10 == 0 && x != 0)) {
        return 0; 
    }
    return x == invertirNum(x);
}

int main() {
    int num;
    printf("Ingresa un numero: ");
    scanf("%d", &num);
    printf("------------------------------------------------------------------------------\n");

    int numInvertido = invertirNum(num); 

    if (esPalindromo(num)) {
        printf("Si es un palindromo\n");
        printf("Debido a que el numero %d se lee igual de forma normal y al reves.\n", num);
    } else {
        printf("No es un palindromo\n");
        printf("Debido a que el numero %d no se lee igual de forma normal y al reves.\n", num);
    }
    
    printf("------------------------------------------------------------------------------\n");
    printf("Ejemplo:\n");
    printf("De forma original se lee: %d\n", num);
    printf("De forma invertida se lee: %d\n", numInvertido);
    printf("------------------------------------------------------------------------------\n");

    return 0;
}

    
