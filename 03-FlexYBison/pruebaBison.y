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

%left   SUMA  RESTA	 COMA
%right  ASIGNACION	

%type <num> expresion primaria 
%type <cadena> ID sentencia

%start objetivo
%%

objetivo : programa FDT       {exit(0);};

programa : INICIO FIN 			  {exit(0);}
|INICIO listaSentencias FIN 	{exit(0);}
;

listaSentencias: sentencia 
|listaSentencias sentencia
;
 


sentencia: ID {printf("La longitud del identificador es: %d",yyleng); masDe32Caracteres();} ASIGNACION expresion PYCOMA    {asignar($1, $3);}
|LEER PARENIZQUIERDO listaIdentificadores PARENDERECHO PYCOMA
|ESCRIBIR PARENIZQUIERDO listaExpresiones PARENDERECHO PYCOMA 
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
|CONSTANTE                                                {printf("valores %d %d",atoi(yytext),$1+$3); $$ = $1;}
|PARENIZQUIERDO expresion PARENDERECHO
;
%%
FILE *yyin;
#define largo 33

typedef struct Identificador {
		char nombre[largo];
		int valor;
} Identificador;

Identificador buffer[1000]; */Identificadores*/
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

int main() {
int menu = 0;
	char file [30];
	if(argc == 1) {
		system("clear");
		printf("Ingrese 1 para escribir el nombre del archivo que desea abrir\n");
		printf("Ingrese 2 para escribir el codigo micro. (no olvides comenzar con 'inicio' y terminar con 'fin'\n OPCION: ");
		scanf("%d", &menu);

		while (menu != 0) {
			if(menu == 1){
				printf("archivo: ");
				scanf("%s", file);
				if((yyin=fopen(file,"rb"))){
					yyparse();
				} else {
					printf("Error al abrir el archivo %s\n", file);
				}
			}
			else if (menu == 2) {
				printf("Ingrese el codigo micro:\n");
				yyparse();
			}
			else {
				printf("Opcion invalida! \n0) para salir, \n1) para el ingresar el codigo a traves de un archivo, \n2) para ingresarlo de forma manual\n");
			}
		}
	} 

	else if (argc == 2){
		if((yyin=fopen(argv[1], "rb"))){
			yyparse();
		} else {
			printf("Error al abrir el archivo %s\n", argv[1]);
		}
	}

	else {
		printf("Error en los argumentos del main!");
	}

return 0;
}
