#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>


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
	if(strchr("X",caracter) != NULL){
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

int funcionPuntoUno(char *cadena){
	
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

		printf("---------------------------------------------------\n");
	
		printf("La cadena a procesar es : %s\n",cadena);

		printf("---------------------------------------------------\n");

		printf("cantError: %i\n", cantError );
		printf("cantDecimales: %i\n", cantDecimal );
		printf("cantHexa: %i\n", cantHexa );
		printf("cantOctal: %i\n", cantOctal );

		printf("---------------------------------------------------\n");
	
	int error = cantDecimal;

	if(cantError != 0 || cantHexa != 0 || cantOctal != 0){
		error = -1;
	}

	return error;
}


void abrirArchivo(char nombreArchivo[]){
    FILE *archivo;
    char caracter;
    char cadena[100];
    int i = 0;
    archivo = fopen(nombreArchivo,"r");
    if (archivo == NULL){
        printf("\nError de apertura del archivo. \n\n");
    }else{
        printf("\nEl contenido del archivo de prueba es \n\n");
        while((caracter = fgetc(archivo)) != EOF){
            cadena[i] = caracter;
            i++;
        }
        cadena[i] = '\0';
        printf("%s\n", cadena);
        funcionPuntoUno(cadena);
    }
    fclose(archivo);
}

int menu(){
    printf("Ingrese una opcion: \n");
    printf("1. Ingresar por linea de comando\n 2. Ingresar por archivo\n 3. Salir\n");
    int opcion;
    scanf("%i", &opcion);
    switch (opcion){
        case 1: printf("Ingrese la expresion separada por $: \n");
                char cadena[100];
				
                scanf("%s", &cadena);
                funcionPuntoUno(cadena);
                break;
        case 2: printf("Ingrese el nombre del archivo: \n");
                char nombreArchivo[100];
                scanf("%s", &nombreArchivo);
                abrirArchivo(nombreArchivo);
                break;
    }
}

int main(){
	menu();
    return 0;
}

