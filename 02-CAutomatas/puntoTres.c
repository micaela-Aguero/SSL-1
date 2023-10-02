#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "../02-CAutomatas/puntoUno.h"
#include "../02-CAutomatas/puntoDos.h"

// Funciones y estructura de las pilas

typedef struct tnodo
{
   int info;
   struct tnodo* sig;
}nodo;

typedef nodo* ptrNodo;

void push(ptrNodo* pila, int info) 
{
   ptrNodo nuevo=(ptrNodo)malloc(sizeof(nodo));
   nuevo->info=info;
   nuevo->sig=*pila;
   *pila=nuevo;
}

int pop(ptrNodo* pila)
{
	ptrNodo* p= pila;
	int x=(*pila)->info;
	*pila=(*pila)->sig; 
	return x;
}


// Punto 1)

// Declaracion de las transiciones del automata 
char cero[] = {'0'};
char N_0[] = {'1','2','3','4','5','6','7'};
char N_X[] = {'A','B','C','D','E','F'};
char D[] = {'8','9'};


//  Calcula las transiciones del automata

int queColumnaPertenceElCaracter(char caracter){
	
	int colum = 8;

	if(strchr(cero,caracter) != NULL){
		colum = 0;
	}
	if(strchr("x",caracter) != NULL){
		colum = 1;
	}
	if(strchr(N_0,caracter) != NULL){
		colum = 2;
	}
	if(strchr(N_X,caracter) != NULL){
		colum = 3;
	}
	if(strchr(D,caracter) != NULL){
		colum = 4;
	}
	if('$' == caracter){
		colum = 5;
	}
	if('+' == caracter){
		colum = 6;
	}
	if('-' == caracter){
		colum = 7;
	}

	return colum;
}

int funcion1(char *cadena,int impresion){
	

	
	char t_transiciones[7][9] = {{1,6,5,6,5,0,5,5,6},
								{4,2,4,6,6,0,6,6,6},
								{3,6,3,3,3,0,6,6,6},
								{3,6,3,3,3,0,6,6,6},
								{4,6,4,6,6,0,6,6,6},
								{5,6,5,6,5,0,6,6,6},
								{6,6,6,6,6,0,6,6,6}};

	int estadosAceptacion[] = {3,4,5}; 

	char *ptr = cadena;

	int cantHexa = 0;
	int cantOctal = 0;
	int cantDecimal = 0;
	int cantError = 0;
	int estadoError = 6;
	int estado = 0;


	while(1){
		if(*ptr == '$' && estado == estadoError || *ptr == '\0' && estado == estadoError){
			cantError++;
		}
		if(*ptr == '$' && estado == estadosAceptacion[0] || *ptr == '\0' && estado == estadosAceptacion[0]){
			cantHexa++;
		}
		if(*ptr == '$' && estado == estadosAceptacion[1] || *ptr == '\0' && estado == estadosAceptacion[1]){
			cantOctal++;
		}
		if(*ptr == '$' && estado == estadosAceptacion[2] || *ptr == '\0' && estado == estadosAceptacion[2]){
			cantDecimal++;
		}
		if(*ptr == '\0')
			break;
		estado = t_transiciones[estado][queColumnaPertenceElCaracter(*ptr)];

		ptr++;
	}	

	if(impresion == 1){
		printf("---------------------------------------------------\n");
	
		printf("La cadena a procesar es : %s\n",cadena);

		printf("---------------------------------------------------\n");

		printf("cantError: %i\n", cantError );
		printf("cantDecimales: %i\n", cantDecimal );
		printf("cantHexa: %i\n", cantHexa );
		printf("cantOctal: %i\n", cantOctal );

		printf("---------------------------------------------------\n");
	}
	
	int error = cantDecimal;

	if(cantError != 0 || cantHexa != 0 || cantOctal != 0){
		error = -1;
	}

	return error;
}



// Punto 2)

int caracterAInt(char caracter){
    return caracter - 48;
}



// Punto 3)

int operandos(char * numeros){
	ptrNodo pila = NULL;
	ptrNodo pilaInvertida  = NULL;
	char operadores[25];
	int resultado = 0;
	char * aux = numeros;
	int i = 1;
	int j = 0;
	int num = 0;
	push(&pila,caracterAInt(*aux));
	aux = numeros + i;
	i++;
// Carga los numeros a la pila realizando las multiplicaciones, y cagra las sumas y restas en orden en un array	
	while(1){
		if(*aux == '/'){
			aux = numeros + i;
			i++;
			num = pop(&pila);
			num = num / caracterAInt(*aux);
			push(&pila,num);
			aux = numeros + i;
			i++;
			continue;
		}
		if(*aux == '*'){
			aux = numeros + i;
			i++;
			num = pop(&pila);
			num = num * caracterAInt(*aux);
			push(&pila,num);
			aux = numeros + i;
			i++;
			continue;
		}
		if(*aux == '+'){
			operadores[j] = *aux;
			j++;
			aux = numeros + i;
			i++;
			push(&pila,caracterAInt(*aux));
			aux = numeros + i;
			i++;
			continue;
		}
		if(*aux == '-'){
			operadores[j] = *aux;
			j++;
			aux = numeros + i;
			i++;
			push(&pila,caracterAInt(*aux));
			aux = numeros + i;
			i++;
			continue;
		}
		break;
	}
	

// Invierte la pila, para mantener precedencia de izquierda a derecha
	while(pila != NULL){
		push(&pilaInvertida,pop(&pila));
	}
// Realiza las sumas y restas, dejando en la pila el resultado final	
	int k = 0;
	
	while(k<=j){
		char operador = operadores[k];
		if (operador == '+'){
			num = pop(&pilaInvertida);
			num += pop(&pilaInvertida);
			push(&pilaInvertida,num);
		}
		if (operador == '-'){
			num = pop(&pilaInvertida);
			num -= pop(&pilaInvertida);
			push(&pilaInvertida,num);
		}
		k++;
	}
// Se obtiene el resultado final de la pila	
	resultado = pop(&pilaInvertida);
	return resultado;
	
}

void verificarCadenaFun3(char *aux){

	char cadena[100];
	char* ptr = aux;
	char* ptr2 = cadena;
// Copia la cadena y cambia todos los operadores por '$', para verificarla con la funcion1
	strcpy(cadena, aux);

	while(*ptr2 != '\0'){
		if(*ptr2 == '+' || *ptr2 == '-' || *ptr2 == '*' || *ptr2 == '/'){
			*ptr2 = '$';
		}
		ptr2++;
	}

	int error = funcion1(cadena,0);

	if(error != -1){
		printf("\nResultado: %i\n",operandos(aux));
	}
	else{
		printf("La cadena ingresada no es valida \n");
	}
}

int main(void){
	char cadena[50];
	scanf("%s", cadena);
	verificarCadenaFun3(cadena);
	return 0;
}