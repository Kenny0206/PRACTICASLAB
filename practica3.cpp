#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMBINACIONES 1000  // limite de combinaciones
#define MAX_LONGITUD 12         // Longitud maxima de las combinaciones
#define MAX_DIGITOS 12          // Maximo de digitos por combinacion

// letras correspondientes al teclado del telefono
const char *teclado[] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

// Función para copiar cadenas 
char *copiarCadena(const char *origen) {
    char *destino = (char *)malloc(strlen(origen) + 1);
    if (destino) {
        strcpy(destino, origen);
    }
    return destino;
}

// Función generar las combinaciones de letras
void generarCombinaciones(char *digitos, int indice, char *actual, char **resultado, int *contador) {
    if (digitos[indice] == '\0') {  
        actual[indice] = '\0';  
        resultado[*contador] = copiarCadena(actual);  
        (*contador)++;
        return;
    }

//Verificador de numeros donde:
    int numero = digitos[indice] - '0';  
    if (numero < 2 || numero > 9) return;  

    const char *letras = teclado[numero];  

    for (int i = 0; letras[i] != '\0'; i++) {  
        actual[indice] = letras[i];  
        generarCombinaciones(digitos, indice + 1, actual, resultado, contador);  
    }
}

// Parte del codigo para obtener las combinaciones y guardarlas
char **obtenerCombinaciones(char *digitos, int *tamanioResultado) {
    if (!digitos || !*digitos) {  
        *tamanioResultado = 0;
        return NULL;
    }


    char **resultado = (char **)malloc(MAX_COMBINACIONES * sizeof(char *));  
    char actual[MAX_LONGITUD]; 
    *tamanioResultado = 0;

    generarCombinaciones(digitos, 0, actual, resultado, tamanioResultado);  
    return resultado;
}

//Impresion de los resultados

int main() {
    char digitos[MAX_DIGITOS];

    
    printf("<>----------<>Ingresa un numero:<>----------<> \n");
    printf("<>");
    scanf("%s", digitos);

    int tamanioResultado;
    char **combinaciones = obtenerCombinaciones(digitos, &tamanioResultado);

    
    if (tamanioResultado == 0) {
        printf("<>----------<>No hay ninguna combinacion posible.<>----------<>\n");
    } else {
        printf("<>----------<> Las posibles combinaciones son:<>----------<>\n");
        for (int i = 0; i < tamanioResultado; i++) {
            printf("<> %s\n", combinaciones[i]);
            free(combinaciones[i]);  
        }
    }

    free(combinaciones);  
    return 0;
}

