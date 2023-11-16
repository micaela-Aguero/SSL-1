%{

    #include <stdio.h>
    int yylex();
    int yyerror(char *s);

%}

%token HOLA ENTERO PUNTOYCOMA IDENTIFICADOR OTRO //son los que puse en el return de flex


%union{
    char cadena[100];
    int digito;
    char *reservada;

}

%type <cadena> IDENTIFICADOR
%type <digito> ENTERO
%type <reservada> HOLA


%%

programa: programa sentencia
        | sentencia PUNTOYCOMA
        ;

sentencia:
        | IDENTIFICADOR {printf("Identificador: %s\n", $1);}
        | ENTERO {printf("Entero: %d\n", $1);}
        | HOLA {printf("Hola genio");}
        | OTRO

%%

int yyerror(char *s){
    printf("Error sintactico: %s\n", s);
    return 0;
}

int main(){
    yyparse();
    return 0;
}

%%