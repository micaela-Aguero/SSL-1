#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <ctype.h>
#include <string.h> 
void menu();
int opcionValida(int opcion);

//Punto 1

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
int esOctal(char *cadena){
	return 0;
}
int esHexadecimal(char *cadena){
	return 0;
}

/*void esPalabra(char *cadena){
	if(!(esDecimal(cadena) || esOctal(cadena) || esHexadecimal(cadena))){
		printf("Hubo un error lexico\n");
	}
}*/

void reconocerPorAutomata(char cadenaEnteros[]){
	char *token;
	int decimales = 0;
	int octales = 0;
	int hexadecimales = 0;
	token = strtok(cadenaEnteros, "$");
	if(esDecimal(token)){
		decimales++;
	}else if(esOctal(token)){
		octales++;
	}else if (esHexadecimal(token)){
		hexadecimales++;
	}else{
		printf("Hubo error lexico\n");
	}
	while (token != NULL){
        token = strtok(NULL, "$");
        if (token != NULL){
		if(esDecimal(token)){
			decimales++;
		}else if(esOctal(token)){
			octales++;
		}else if (esHexadecimal(token)){
			hexadecimales++;
		}else{
			printf("Hubo error lexico\n");
		}
	            
        }
    }
	printf("\n%s%i\n%s%i\n%s%i\n", "- Cantidad decimales: ", decimales, "- Cantidad octales: ", octales, "- Cantidad hexadecimales: ", hexadecimales);
}



//Punto 2
int caracterAInt(char caracter){
	return caracter-48;
}
void funcionPuntoDos(){
	char caracter;
	scanf("%c", &caracter);
	printf("%i", caracterAInt(caracter));
		menu();
}

void funcionPuntoUno(){
	char cadenaEnteros[50];
	scanf("%s", &cadenaEnteros);
	if(!verifica(cadenaEnteros)){
		printf("Hay caracteres que no pertenecen al alfabeto\n");
	}else reconocerPorAutomata(cadenaEnteros);
		menu();
}

int verifica(char cadenaEnteros[]){
	unsigned i;
	for (i=0 ; cadenaEnteros[i];i++){
		if (!(cadenaEnteros[i]== '$' || esCaracterHexa(cadenaEnteros[i]) || isdigit(cadenaEnteros[i]))){
			return 0;
		}
	}	
	printf("Todos los caracteres pertenecen al alfabeto\n");
	return 1;
}

int esCaracterHexa(char *caracter){
	if((caracter>='A' && caracter<='F') || caracter=='X' || caracter=='x'){
		return 1;
	}
	return 0;
}



int main() {
/*	char caracter;
	printf("%i", caracterAInt(caracter));*/

	menu();



	return 0;
}


void menu(){
	printf("\n%s\n\n%s\n\n %s\n %s\n %s\n", "MENU", "Ingresar Opcion:","1. Reconocer constantes enteras", "2. Caracter numerico a Int", "3. Resultado de operacion matematica");
	int opcion;
	scanf("%i", &opcion);
	while(!opcionValida(opcion)){
		printf("\nIngresa una opcion valida:\n\n");
		printf(" %s\n %s\n %s\n","1. Reconocer constantes enteras", "2. Caracter numerico a Int", "3. Resultado de operacion matematica");
		scanf("%i", &opcion);
		}
	switch (opcion){
		case 1: printf("Ingresar enteros separados por el caracter $\n");
				fflush(stdin);
				funcionPuntoUno();
				break;
		case 2: printf("Ingresar un caracter numerico\n");
				fflush(stdin);
				funcionPuntoDos();
				break;
		case 3: printf("Ingresar una operacion aritmetica sin parentesis\n");
				fflush(stdin);
				//funcionPuntoTres();
				break;
	}
	}
	
int opcionValida(int opcion){
	if(opcion == 1 || opcion == 2 || opcion == 3){
		return 1;
	}else return 0;
}
