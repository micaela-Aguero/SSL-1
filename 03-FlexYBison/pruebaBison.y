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
%token ASIGNACION PYCOMA SUMA RESTA PARENIZQUIERDO PARENDERECHO COMA ESCRIBIR LEER INICIO FIN FDT
%token <cadena> ID
%token <num> CONSTANTE
%%

objetivo : programa FDT {exit(0);};
programa : INICIO FIN 					{exit(0);}
|INICIO sentencias FIN 	{exit(0);}
;

sentencias: sentencias sentencia 
|sentencia
;
sentencia: ID {printf("La longitud del identificador es: %d",yyleng);if(yyleng>32) yyerror("Error semantico, el identificador excede el limite de caracteres por identificador (32)");} ASIGNACION expresion PYCOMA
;
expresion: primaria 
|expresion operadorAditivo primaria 
; 
primaria: ID
|CONSTANTE {printf("valores %d %d",atoi(yytext),$1+$3); }
|PARENIZQUIERDO expresion PARENDERECHO
;
operadorAditivo: SUMA 
| RESTA
;
%%
int main() {
yyparse();
}
void yyerror (char *s){
printf ("%s\n",s);
}
int yywrap()  {
  return 1;  
} 
