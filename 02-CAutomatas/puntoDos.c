#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../02-CAutomatas/puntoUno.h"

/*
int caracterAInt(char *cadena){
    int resultado = 0;
    int indice = 0;
    
    // Mientras no lleguemos al final de la cadena y el carácter actual sea un dígito
    while (cadena[indice] != '\0' && cadena[indice] >= '0' && cadena[indice] <= '9') {
        // Multiplicamos el resultado actual por 10 y le sumamos el valor del dígito
        resultado = resultado * 10 + (cadena[indice] - '0');
        indice++;
    }
    
    return resultado;
}

int main() {
    char entrada[100]; // Puedes ajustar el tamaño según tus necesidades
    
    printf("Ingresa un número: ");
    fgets(entrada, sizeof(entrada), stdin);
    
    // Reemplazamos el salto de línea (si existe) con el terminador de cadena
    for(int i = 0; i < sizeof(entrada); i++) {
        if (entrada[i] == '\n') {
            entrada[i] = '\0';
            break;
        }
    }

    int numero = caracterAInt(entrada);
    printf("El número ingresado es: %d\n", numero);

    return 0;
}

*/

int caracterAInt(char caracter){
    return caracter - 48;
}

int main(){
    printf("Ingrese un caracter: \n");
    char* c;
    scanf("%s", &c);
    int numero = caracterAInt(c);
    printf("El numero ingresado es: %i\n", numero);
    return 0; 
}