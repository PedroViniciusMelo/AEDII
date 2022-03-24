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

    a = inserir(a, 8, cresceu);
    a = inserir(a, 10, cresceu);
    a = inserir(a, 17, cresceu);
    a = inserir(a, 9, cresceu);
    a = inserir(a, 15, cresceu);
    a = inserir(a, 16, cresceu);
    //printBT("", a, 0);
    a = NULL;
    a = inserir(a, 20, cresceu);
    a = inserir(a, 10, cresceu);
    a = inserir(a, 15, cresceu);
    a = inserir(a, 9, cresceu);
    a = inserir(a, 18, cresceu);
    a = inserir(a, 30, cresceu);
    a = inserir(a, 40, cresceu);
    a = inserir(a, 7, cresceu);
    a = inserir(a, 26, cresceu);
    a = inserir(a, 28, cresceu);
    a = inserir(a, 50, cresceu);
    a = inserir(a, 12, cresceu);
    a = remover (28, a, diminuiu);
    a = remover (26, a, diminuiu);
    a = remover (18, a, diminuiu);
    printBT("", a, 0);






/*
    a = inserir(a, 50, cresceu);
    a = inserir(a, 9, cresceu);
    a = inserir(a, 60, cresceu);
    a = inserir(a, 8, cresceu);
    a = inserir(a, 59, cresceu);
    a = inserir(a, 58, cresceu);
    a = inserir(a, 63, cresceu);
    a = inserir(a, 10, cresceu);
    a = inserir(a, 9, cresceu);
    a = inserir(a, 11, cresceu);
    a = inserir(a, 12, cresceu);
    a = inserir(a, 13, cresceu);
    a = inserir(a, 14, cresceu);
    a = inserir(a, 15, cresceu);
    a = inserir(a, 16, cresceu);
    a = inserir(a, 17, cresceu);
    a = inserir(a, 18, cresceu);
    a = inserir(a, 19, cresceu);
    a = inserir(a, 20, cresceu);
    a = inserir(a, 21, cresceu);
    a = inserir(a, 22, cresceu);

    printBT("", a, 0);

    /*
    while(1){
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                scanf("%d", &valor);
                a = inserir(a, valor);
                break;
            case 2:
                preorder(a);
                printf("\n");
                break;
            case 3:
                inorder(a);
                printf("\n");
                break;
            case 4:
                posorder(a);
                printf("\n");
                break;
            case 5:
                reverso(a);
                printf("\n");
                break;
            case 6:
                printf("%d", qtdPrimo(a));
                printf("\n");
                break;
            case 7:
                scanf("%d", &valor);
                printf("%d", sucessor(valor, a));
                printf("\n");
                break;
            case 8:
                scanf("%d", &valor);
                caminho(valor, a);
                printf("\n");
                break;
            case 9:
                scanf("%d", &valor);
                a = remover(valor, a);
                break;
            case 10:
                printf("%d", altura(a));
                printf("\n");
                break;
            case 99:
                exit(0);
        }
    }*/
}