%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "pruebaBison.tab.h"

	void showError();
%}

DIGITO ([0-9])
LETRA ([a-zA-Z])

%%

"hola" {yylval.reservada = yytext; return (HOLA);}
{DIGITO} {yylval.digito = atoi(yytext); return (ENTERO);}
";" {return (PUNTOYCOMA);}
{LETRA} {sscanf(yytext, "%s", yyval.cadena); return (IDENTIFICADOR);}
. {showError();return(OTRO);}


%%

showError(char* otro){
	printf("-----<<<<< Error lexico: \"%s\" >>>>>-----\n", otro);
}


