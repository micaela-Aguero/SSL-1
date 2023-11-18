%{
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
extern char *yytext;
extern int yyleng;
extern int yylex(void);
extern void yyerror(char*);
int variable=0;
%}
%union{
   char* cadena;
   int num;
} 
%token ASIGNACION PYCOMA SUMA RESTA PARENIZQUIERDO PARENDERECHO ID COMA ESCRIBIR LEER INICIO FIN FDT 
%token <num> CONSTANTE
%token <cadena> ID sentencia
%left   SUMA  RESTA	 COMA
%right  ASIGNACION	

%type <num> expresion primaria 

%start objetivo
%%

objetivo : programa FDT       {exit(0);};

programa : INICIO FIN 			  {exit(0);}
|INICIO listaSentencias FIN 	{exit(0);}
;

listaSentencias: sentencia {}
|listaSentencias sentencia {}
;
 


sentencia: ID {printf("La longitud del identificador es: %d",yyleng); masDe32Caracteres();} ASIGNACION expresion PYCOMA    {asignar($1, $3);}
|LEER PARENIZQUIERDO listaIdentificadores PARENDERECHO PYCOMA   {}
|ESCRIBIR PARENIZQUIERDO listaExpresiones PARENDERECHO PYCOMA   {}
;

listaIdentificadores: expresion          {leerIdentificador($1);}
|listaIdentificadores COMA ID            {leerIdentificador($3);}
;

listaExpresiones: expresion                            {escribirExpresion($1);}
|listaExpresiones COMA expresion                       {escribirExpresion($3);}
;

expresion: primaria                                        {$$ = $1;}
|expresion SUMA primaria                                   {$$ = $1 + $3;}
|expresion RESTA primaria                                  {$$ = $1 - $3;}

; 


primaria: ID                                              {leerIdentificador($1);}
|CONSTANTE                                                {printf("valores %d %d",atoi(yytext),$1); $$ = $1;}
|PARENIZQUIERDO expresion PARENDERECHO                    {}
;
%%
FILE *yyin;
#define largo 33

typedef struct Identificador {
		char nombre[largo];
		int valor;
} Identificador;

Identificador buffer[1000]; 
int tope = 0; 
void leer_id(char* nombre);
void escribir_exp(int valor);
void asignar(char* nombre, int valor);
int buscar(char* nombre);
void listarIdentificadores (void);

void masDe32Caracteres(){
  if (yyleng>32) yyerror("Error semantico, el identificador excede el limite de caracteres por identificador (32)")
}
void yyerror (char *s){
printf ("%s\n",s);
}
int yywrap()  {
  return 1;  
} 

void leer_id(){
  int i;
  for (i=0; i<tope; i++){
    if (strcmp(buffer[i].nombre,yytext)==0){
      printf("El valor de %s es %d\n",yytext,buffer[i].valor);
      return;
    }
  }
  printf("Error semantico, identificador %s no declarado!\n",yytext);
}

void asignar(nombre, valor){
  int i = buscar(nombre);
  if (i==0){
    strcpy(buffer[tope].nombre,nombre);
    buffer[tope].valor=valor;
    tope++;
  }
  else{
    buffer[i].valor=valor;
  }
}

void buscar(nombre){
  int i;
  for (i=0; i<tope; i++){
    if (strcmp(buffer[i].nombre,nombre)==0){
      return buffer[i].valor;
    }
  }
  return 0;
}

listaIdentificadores(){
  int i;
  for (i=0; i<tope; i++){
    printf("%s\n",buffer[i].nombre);
  }
}

void escribir_exp(int valor) {
	char nombre[largo];
	listarIdentificadores();
	printf("ID a asignar el valor %d: ", valor);
	scanf("%s", nombre);
	asignar(nombre, valor);
}
int main(int argc, char* argv[]) {
	int opcion = 0;
	char archivo [50];
	if(argc == 1) {
		printf("1) Escribir el nombre del archivo con codigo micro\n");
		printf("2) Para escribir codigo micro\n");
		scanf("%d", &opcion);

		while (opcion != 0) {
		    switch (opcion){
		        case 1: 
		        printf("archivo: ");
				scanf("%s", archivo);
				if((yyin=fopen(archivo,"rb"))){
					yyparse();
				} else {
					printf("Error al abrir el archivo: %s\n", archivo);
				}
				break;
				case 2:
					printf("Ingresar codigo micro: \n");
				yyparse();
				break;
				default:
                printf("Ingrese una opcion valida. \n");
                printf("0) Salir, \n1) Para escribir el nombre del archivo con codigo micr, \n2) Para escribir codigo micro\n");
  
		    }
		}
	} 

	else if (argc == 2){
		if((yyin=fopen(argv[1], "rb"))){
			yyparse();
		} else {
			printf("Error al intentar abrir el archivo %s\n", argv[1]);
		}
	}

	else {
		printf("Error en los argumentos del main!");
	}

return 0;
}
