#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    time_t t;
    time(&t);


    FILE* texto = fopen("output.txt", "w");

    fprintf(texto, "Hello World %s", ctime(&t), "\n");
    fprintf(stdout, "Hello World %s", ctime(&t), "\n");

    return 0;
}
