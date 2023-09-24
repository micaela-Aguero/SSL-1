#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

int esDecimal(char* cadena){
    if(cadena[0] == '+' || cadena[0] == '-' || (isdigit(cadena[0]) && cadena[0] != '0')){
        for(int i = 1; i < strlen(cadena); i++){
            if(isdigit(cadena[i])){
                return 1;
            }
        }
    }else{
        return 0;
    }
  
}

int esOctal(char *cadena){
    if(cadena[0] == '0' && cadena[1] != 'x'){
        for(int i = 1; i < strlen(cadena); i++){
           if(isdigit(cadena[i])){
                return 1;
            }
        }
        }else{
            return 0;
        }
}

int esLetraAaF(char *caracter) {
    if (caracter >= 'A' && caracter <= 'F' && isupper(caracter)) {
        return 1;
    }else{
        return 0;
    }
}

int esHexadecimal(char *cadena){
    if(cadena[0] == '0' && cadena[1] == 'x'){
        for(int i = 2; i < strlen(cadena); i++){
            if(isdigit(cadena[i]) || esLetraAaF(cadena[i])){
                return 1;
            }else return 0;
        }
    }else{
            return 0;
        }
}


void operarLista(char* lista) {
    char* token = strtok(lista, "$");
    while (token != NULL) {
        if (esDecimal(token)) {
            printf("DECIMAL", token);
        }
        if (esOctal(token)) {
            printf("OCTAL", token);
        }
        if (esHexadecimal(token)) {
            printf("HEXADECIMAL", token);
        }
        if (!esDecimal(token) && !esOctal(token) && !esHexadecimal(token)) {
            printf("ERROR", token);
        }
        token = strtok(NULL, "$");
        if (token != NULL) {
            printf("\n");
        }
    }
}

int main(){
    char cadena[] = "1234$0xAF45$023$assadskjfhakjl";
   operarLista(cadena);
   return 0;

    //Falta hacer lo de que lo lea por consola y lo de que lo lea de un archivo
  
}
