#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int team(int *skill, int n) {
    if (n % 2 != 0) return -1; 

    qsort(skill, n, sizeof(int), compare);

    int total = 0;
    int Sum = skill[0] + skill[n - 1];

    printf("<> Dividimos los jugadores en los siguientes equipos: \n");
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        if (skill[i] + skill[j] != Sum) {
            return -1; 
        }
        printf("(<> %d, %d), ", skill[i], skill[j]);
        total += skill[i] * skill[j];
    }

    printf("\n <> Cada equipo tiene una suma total de habilidades de: %d\n", Sum);
    printf(" <> La suma de la quimica de todos los equipos es: %d \n", total);
    
    return total;
}

int main() {
    int n;

    
    printf("<> Ingrese el numero de jugadores: \n");
    scanf("%d", &n);

    if (n % 2 != 0) {
        printf("\n -1 \n");
        return 0;
    }

    int *skill = (int*)malloc(n * sizeof(int));
    if (skill == NULL) {
        printf("<>---<>Memoria insuficiente.<>---<>\n");
        return 1;
    }

  
    printf("<> Ingrese las habilidades de los jugadores: \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &skill[i]);
    }

    int result = team(skill, n);
    if (result == -1) {
        printf("\n -1 \n");
    }

    free(skill); 
    return 0;
}

