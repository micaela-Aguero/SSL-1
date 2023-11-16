%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"
%}
DIGITO [0-9]

LETRA [a-zA-Z]

IDENTIFICADOR {LETRA}({LETRA}|{DIGITO})*
separador [\t]+
constEntera {DIGITO}({DIGITO})*
%%
":=" {return (ASIGNACION);}
{constEntera} {yylval.num=atoi(yytext);return (CONSTANTE);}
{IDENTIFICADOR} {return (ID);}
{separador}     {/omitir/}
";" {return (PYCOMA);}
"," {return (COMA);}
"(" {return (PARENIZQUIERDO);}
")" {return (PARENDERECHO);}
"+" {return (SUMA);}
"-" {return (RESTA);}
"inicio" {return (INICIO);}
"fin" {return (FIN);}
"leer" {return (LEER);}
"escribir" {return (ESCRIBIR);}
. {errorLexico();}
%% 

void errorLexico(void){
    printf("Error Lexico: se ha ingresado un caracter invalido (%s)\n", yytext);
}
