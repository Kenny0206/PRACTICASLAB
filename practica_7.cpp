#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 256

typedef struct Nodo {
    unsigned char simbolo;
    unsigned frecuencia;
    struct Nodo *izq, *der;
} Nodo;

typedef struct NodoCola {
    Nodo* nodo;
    struct NodoCola *sig;
} NodoCola;

NodoCola* insertarNodoCola(NodoCola* cabeza, Nodo* nodo) {
    NodoCola* nuevo = (NodoCola*)malloc(sizeof(NodoCola));
    nuevo->nodo = nodo;
    nuevo->sig = NULL;

    if (!cabeza || nodo->frecuencia < cabeza->nodo->frecuencia) {
        nuevo->sig = cabeza;
        return nuevo;
    }

    NodoCola* actual = cabeza;
    while (actual->sig && actual->sig->nodo->frecuencia <= nodo->frecuencia) {
        actual = actual->sig;
    }
    nuevo->sig = actual->sig;
    actual->sig = nuevo;
    return cabeza;
}

Nodo* extraerMinimo(NodoCola** cabeza) {
    if (!(*cabeza)) return NULL;
    NodoCola* temp = *cabeza;
    Nodo* nodo = temp->nodo;
    *cabeza = temp->sig;
    free(temp);
    return nodo;
}

Nodo* crearNodo(unsigned char simbolo, unsigned frecuencia, Nodo* izq, Nodo* der) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->simbolo = simbolo;
    nuevo->frecuencia = frecuencia;
    nuevo->izq = izq;
    nuevo->der = der;
    return nuevo;
}

Nodo* crearArbolHuffman(unsigned frecuencias[]) {
    NodoCola* lista = NULL;

    for (int i = 0; i < MAX_SYMBOLS; i++) {
        if (frecuencias[i] > 0) {
            Nodo* nodo = crearNodo((unsigned char)i, frecuencias[i], NULL, NULL);
            lista = insertarNodoCola(lista, nodo);
        }
    }

    while (lista && lista->sig) {
        Nodo* izq = extraerMinimo(&lista);
        Nodo* der = extraerMinimo(&lista);
        Nodo* padre = crearNodo(0, izq->frecuencia + der->frecuencia, izq, der);
        lista = insertarNodoCola(lista, padre);
    }

    return extraerMinimo(&lista);
}

void generarCodigos(Nodo* raiz, char* codigo, int longitud, char codigos[MAX_SYMBOLS][MAX_SYMBOLS]) {
    if (!raiz) return;
    if (!raiz->izq && !raiz->der) {
        codigo[longitud] = '\0';
        strcpy(codigos[raiz->simbolo], codigo);
        return;
    }
    codigo[longitud] = '0';
    generarCodigos(raiz->izq, codigo, longitud + 1, codigos);
    codigo[longitud] = '1';
    generarCodigos(raiz->der, codigo, longitud + 1, codigos);
}

void comprimirArchivo(FILE* entrada, FILE* salida, char codigos[MAX_SYMBOLS][MAX_SYMBOLS], unsigned* bitsOriginal, unsigned* bitsComprimido) {
    int c;
    while ((c = fgetc(entrada)) != EOF) {
        *bitsOriginal += 8;
        fputs(codigos[(unsigned char)c], salida);
        *bitsComprimido += (unsigned)strlen(codigos[(unsigned char)c]);
    }
}

void decodificarArchivo(FILE* entrada, Nodo* raiz, FILE* salida) {
    Nodo* actual = raiz;
    int c;
    while ((c = fgetc(entrada)) != EOF) {
        if (c == '0') actual = actual->izq;
        else if (c == '1') actual = actual->der;
        else continue; 

        if (!actual->izq && !actual->der) {
            fputc(actual->simbolo, salida);
            actual = raiz;
        }
    }
}

int main() {
    char nombreArchivo[260];
    printf("Ingrese el nombre del archivo txt que se desea comprimir: ");
    scanf("%259s", nombreArchivo);

    FILE* entrada = fopen(nombreArchivo, "r");
    if (!entrada) {
        perror("No se pudo abrir el archivo de entrada");
        return 1;
    }

    
    unsigned frecuencias[MAX_SYMBOLS] = {0};
    int palabraCount = 0;
    char buffer[1024];

    
    while (fscanf(entrada, "%1023s", buffer) == 1) {
        palabraCount++;
        for (int i = 0; buffer[i] != '\0'; i++) {
            frecuencias[(unsigned char)buffer[i]]++;
        }
    }

    if (palabraCount < 20 || palabraCount > 500) {
        printf("El archivo debe tener entre 20 y 500 palabras. Tiene %d palabras.\n", palabraCount);
        fclose(entrada);
        return 1;
    }

    rewind(entrada); 

    Nodo* arbol = crearArbolHuffman(frecuencias);

    char codigos[MAX_SYMBOLS][MAX_SYMBOLS] = {{0}};
    char codigoTemporal[MAX_SYMBOLS];
    generarCodigos(arbol, codigoTemporal, 0, codigos);

    FILE* salida = fopen("codificado.txt", "w");
    if (!salida) {
        perror("No se pudo abrir el archivo de salida");
        fclose(entrada);
        return 1;
    }

    unsigned bitsOriginal = 0;
    unsigned bitsComprimido = 0;

    comprimirArchivo(entrada, salida, codigos, &bitsOriginal, &bitsComprimido);

    fclose(entrada);
    fclose(salida);

    printf("Archivo comprimido y guardado en 'codificado.txt'\n");
    printf("Tamanio original en bits: %u\n", bitsOriginal);
    printf("Tamanio comprimido en bits: %u\n", bitsComprimido);
    printf("Tasa de compresion: %.2f%%\n", 100.0 * bitsComprimido / bitsOriginal);

    
    entrada = fopen("codificado.txt", "r");
    if (!entrada) {
        perror("No se pudo abrir el archivo codificado para decodificar");
        return 1;
    }
    FILE* decodificado = fopen("decodificado.txt", "w");
    if (!decodificado) {
        perror("No se pudo crear el archivo decodificado");
        fclose(entrada);
        return 1;
    }

    decodificarArchivo(entrada, arbol, decodificado);

    fclose(entrada);
    fclose(decodificado);

    printf("Archivo decodificado guardado en 'decodificado.txt'\n");

    return 0;
}

