#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(){
    char a[20];
    int len;
    bool esRaro = true;
    printf("palabra1: ");
    scanf("%19s", a);
    len = strlen(a);

    for (int i = 0; i<=len;i++){
        if (a[i] != a[(len-1)-i]){
            esRaro = false;
        }
    }
    if (esRaro){
        printf("es raro");
    }
    else{
        printf("no es raro");
    }

// hooh len = 4 i = 0 h    4-0

    return 0;
}
    