#include <stdio.h>
#include <stdlib.h>

int trap(int* height, int heightSize) {
    if (heightSize == 0) return 0;

    int left = 0, right = heightSize - 1;
    int left_max = 0, right_max = 0;
    int water = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= left_max) {
                left_max = height[left];
            } else {
                water += left_max - height[left];
            }
            left++;
        } else {
            if (height[right] >= right_max) {
                right_max = height[right];
            } else {
                water += right_max - height[right];
            }
            right--;
        }
    }

    return water;
}

int main() {
    int n;
    printf("De cuanto es el arreglo: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("El tamaño debe ser mayor que 0.\n");
        return 1;
    }

    int* height = (int*)malloc(n * sizeof(int));
    if (height == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    printf("Ingresa los %d valores del arreglo:\n", n);
    for (int i = 0; i < n; i++) {
        printf("height[%d]: ", i);
        scanf("%d", &height[i]);
        if (height[i] < 0) {
            printf("Los valores no pueden ser negativos.\n");
            free(height);
            return 1;
        }
    }

    int resultado = trap(height, n);
    printf("\nCantidad de agua atrapada: %d\n", resultado);

    free(height);
    return 0;
}
