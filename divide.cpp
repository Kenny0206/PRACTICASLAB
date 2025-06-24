	//Librerias
	#include <stdio.h>
	#include <limits.h>


	//Funcion para dividir 

	int divide(int dividend, int divisor) {
    if (dividend == INT_MIN && divisor == -1) {
        return INT_MAX;
    }
    
	//Determina el signo con el cual va a salir el resultado de la division
    int negative = (dividend < 0) ^ (divisor < 0);
    
    //Convierte los valores en absolutos y convierte temporalmente ambos valores en positivo
    unsigned int udividend = dividend < 0 ? -dividend : dividend;
    unsigned int udivisor = divisor < 0 ? -divisor : divisor;
    
    //Almacenador del resultado de la division
    int rvalor = 0;
    
    //Se repite mientras el dividendo siga siendo mayor o igual al divisor.
    while (udividend >= udivisor) {
        unsigned int temp = udivisor, multiple = 1;
    
        while (udividend >= (temp << 1) && (temp << 1) > temp) {
            temp <<= 1;
            multiple <<= 1;
        }
        udividend -= temp; // Se resta el mayor múltiplo posible de divisor a dividendo.
        rvalor += multiple; //Se suma el múltiplo correspondiente al cociente.
    }
    
    //Regresa el resultado negativo
    return negative ? -rvalor : rvalor;
}


//Imprimir los mensajes para pedir el divisor y el dividiendo
int main() {
    int dividend, divisor;
    printf("Ingrese el dividendo: ");
    scanf("%d", &dividend);
    printf("Ingrese el divisor: ");
    scanf("%d", &divisor);
    
    
    int resultado_entero = divide(dividend, divisor);
    float resultado_decimal = (float)dividend / divisor;
    
//Imprimir los resultados del divisor, dividiendo y el cociente
    printf("\n<>---------------------------------------------------<>\n");
    printf("Dividendo: %d\n", dividend);
    printf("Divisor: %d\n", divisor);
    printf("Cociente entero: %d\n", resultado_entero);
    printf("Cociente decimal: %.6f\n", resultado_decimal);
    printf("<>---------------------------------------------------<>\n");
    
    return 0;
}

