#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int opcao;
    arvore a = NULL;
    int *cresceu = malloc(sizeof(int));
    int *diminuiu = malloc(sizeof(int));

    while(1){
        int valor;
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