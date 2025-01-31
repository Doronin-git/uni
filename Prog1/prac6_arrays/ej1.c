#include <stdio.h>

void ask_text(char* cadena);  
void analize(char* frase, int *words, int *vocales, int *constantes );


int main(){
    char frase[200];

    ask_text(frase); 


    int words = 0, vocales = 0, constantes = 0; 
    analize(frase, &words,&vocales,&constantes);  

    printf("Palabras: %d\n", words);
    printf("voc: %d\n", vocales);
    printf("const: %d\n", constantes);

}

void analize(char* frase,int *words, int *vocales, int *constantes ){
    int i = 0; 
    while(frase[i] != '\0'){  
        if (frase[i] == ' '){
            (*words)++;
        }
        else if (frase[i] == 'a' || frase[i] == 'e' || frase[i] == 'u' || frase[i] == 'i' || frase[i] == 'o' ){
            (*vocales)++;
        }
        else {
            (*constantes)++;
        }
        i++;
        
    }
    (*words)++;


    
}

void ask_text(char* cadena){
    printf("Introduce un texto de máximo 200 caracteres: ");
    scanf(" %[^\n]", cadena);  

   
}

