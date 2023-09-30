#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../02-CAutomatas/puntoUno.h"
#include "../02-CAutomatas/puntoDos.h"


int columnaDecimales(int x){
	switch(x){
		case '+':
			return 1;
		case '-':
			return 1;	
		case '0':
			return 0;
		default:
			return 2;
	}
}

int esDecimal(char *cadena){
	const int tt[5][3] = {{3,1,2},
						  {4,4,2},
						  {2,4,2},
						  {4,4,4},
						  {4,4,4},						
					     };
	int estado = 0;
	int i = 0;

	int aux = cadena[i];
	while(aux!='\0'){
		
		estado = tt[estado][columnaDecimales(aux)];
		aux=cadena[++i];
		
	}
	if(estado == 2 || estado == 3){
	//	printf("es decimal\n");
		return 1;
	}
	return 0;
}

int caracterAInt(char caracter){
    return caracter - 48;
}

float operar(int operando1, char operador, int operando2){
    switch(operador){
        case '+':
            return operando1 + operando2;
        case '-':
            return operando1 - operando2;
        case '*':
            return operando1 * operando2;
        case '/':
            return operando1 / operando2;
        default:
            printf("El operador no es valido\n");
            return 0;
    }
}

float evaluarExpresion(char *expresion){
    if(expresion != NULL){
        float resultado = operar(caracterAInt(expresion[0]), expresion[1], caracterAInt(expresion[2]));
        printf("El resultado parcial es %f\n", resultado);
        int i = 3;
        for (i ; expresion[i] != '\0'; i+=2){
            char operador = expresion[i];
            int operando = caracterAInt(expresion[i+1]);
            resultado = operar(resultado, operador, operando);
            printf("El resultado parcial es %f\n", resultado);
        }
        return resultado;
    }else{
        printf("La expresion es nula\n");
        return 0;
    }
}


int main(){
    printf("Ingrese la expresion:\n");
    char expresion[100];
    scanf("%s", expresion);
    printf("El resultado es %f\n", evaluarExpresion(expresion));
    return 0;
}