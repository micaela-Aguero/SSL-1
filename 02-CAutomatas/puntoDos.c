#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../02-CAutomatas/puntoUno.h"

int caracterAInt(char caracter){
    return caracter - 48;
}

int funcionPuntoDos(char caracter){

	printf("%i", caracterAInt(caracter));
}

int main(){
    printf("Ingrese el caracter:\n");
    char caracter[100];
    scanf("%c", &caracter[0]);
    funcionPuntoDos(caracter[0]);
    return 0;
}
