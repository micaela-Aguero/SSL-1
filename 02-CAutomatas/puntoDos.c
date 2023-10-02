#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Le resta el valor ASCII de ´0´ al caracter y devuelve el numero entero
int caracterAInt(char caracter){
    return caracter - 48;
}

int main(){
    printf("Ingrese un caracter: \n");
    char c;
    scanf("%s", &c);
    int numero = caracterAInt(c);
    printf("El numero ingresado es: %d\n", numero);
    return 0; 
}