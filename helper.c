#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void printBT(char* string, arvore arvore, int isRight){
    if(arvore != NULL){
        printf("%s", string);
        printf(isRight ? "├──" : "└──" );

        switch (arvore->cor) {
            case PRETO:
                printf("\x1b[30m%d\x1b[0m\n", arvore->valor);
                break;
            case VERMELHO:
                printf("\x1b[31m%d\x1b[0m\n", arvore->valor);
                break;
            case DUPLO_PRETO:
                printf("\x1b[32m%d\x1b[0m\n", arvore->valor);
                break;
        }

        printBT( concat(string, (isRight ? "│   " : "    ")), arvore->direito, 1);
        printBT(concat(string, (isRight ? "│   " : "    ")) , arvore->esquerdo, 0);
    }
}