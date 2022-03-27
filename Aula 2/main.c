#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        //printf("\033[31;1mHello\033[0m");
        printf("%d (%d)\n", arvore->valor, arvore->ftBalanco);

        printBT( concat(string, (isRight ? "│   " : "    ")), arvore->direito, 1);
        printBT(concat(string, (isRight ? "│   " : "    ")) , arvore->esquerdo, 0);
    }
}

int main(int argc, char const *argv[])
{
    int opcao;
    int valor;

    arvore a = NULL;
    int *cresceu = malloc(sizeof(int));
    int *diminuiu = malloc(sizeof(int));

    while(1){
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                scanf("%d", &valor);
                a = inserir(a, valor, cresceu);
                break;
            case 2:
                scanf("%d", &valor);
                a = remover(valor, a, diminuiu);
                break;
            case 3:
                imprimir(a);
                printf("\n");
                break;
            case 99:
                exit(0);
        }
    }
}