#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int opcao;
    int valor;

    arvore a = NULL;

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
    }
}