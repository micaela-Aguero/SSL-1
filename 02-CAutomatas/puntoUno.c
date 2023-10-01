#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

/*
int columnaDecimales(int x){
	switch(x){
		case '+':
			return 1;
		case '-':
			return 1;	
		case '0':
			return 0;
		case '*':
			return 2;
		case '/':
			return 2;
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
		printf("es decimal\n");
		return 1;
	}else{
		printf("no es decimal\n");
		return 0;}
	//return 0;
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
	printf("- Cantidad decimales: ", decimales, "\n- Cantidad octales: ", octales, "\n- Cantidad hexadecimales: ", hexadecimales, "\n");
}

int esCaracterHexa(char *caracter){
	if((caracter>='A' && caracter<='F') || caracter=='X' || caracter=='x'){
		return 1;
	}
	return 0;
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

void funcionPuntoUno(char *cadenaEnteros){
	if(!verifica(cadenaEnteros)){
		printf("Hay caracteres que no pertenecen al alfabeto\n");
	}else reconocerPorAutomata(cadenaEnteros);
		menu();
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
	char cadena[100];
	scanf("%s", &cadena);
	esDecimal(cadena);

   //menu();
    return 0;
}

*/
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
	if('&' == caracter){
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
		if(*ptr == '&' && estado == estadoError || *ptr == '\0' && estado == estadoError){
			cantError++;
		}
		if(*ptr == '&' && estado == estadosAceptacion[0] || *ptr == '\0' && estado == estadosAceptacion[0]){
			cantHexa++;
		}
		if(*ptr == '&' && estado == estadosAceptacion[1] || *ptr == '\0' && estado == estadosAceptacion[1]){
			cantOctal++;
		}
		if(*ptr == '&' && estado == estadosAceptacion[2] || *ptr == '\0' && estado == estadosAceptacion[2]){
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
