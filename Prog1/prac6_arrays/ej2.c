#include <stdio.h>
#include <string.h>

void scan_palabra(char *palabra);

int main(){
    char palabra[20];
    scan_palabra(&palabra);




    return 0;
}


void scan_palabra(char *palabra){
    printf("Escribe una palabra: ");
    scanf("%[\n]", *palabra);
    printf("%c", palabra);
}