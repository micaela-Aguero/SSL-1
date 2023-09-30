#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

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
        reconocerPorAutomata(cadena);
    }
    fclose(archivo);
}

void menu(){
    printf("Ingrese una opcion: \n");
    printf("1. Ingresar por linea de comando\n 2. Ingresar por archivo\n 3. Salir\n");
    int opcion;
    scanf("%i", &opcion);
    switch (opcion){
        case 1: printf("Ingrese la expresion separada por $: \n");
                char cadena[100];
                scanf("%s", &cadena);
                reconocerPorAutomata(cadena);
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
