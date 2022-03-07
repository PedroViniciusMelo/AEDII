#include "bst.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    arvore a;
    //Inicialização da árvore vazia
    a = NULL;
    a = inserir(a, 32);
    a = inserir(a, 45);
    a = inserir(a, 20);
    a = inserir(a, 11);
    a = inserir(a, 12);
    a = inserir(a, 80);
    a = inserir(a, 79);
    a = inserir(a, 84);
    a = inserir(a, 83);
    a = inserir(a, 86);
    a = inserir(a, 82);
    a = inserir(a, 43);
    a = inserir(a, 42);
    printf("Preorder: \n");
    preorder(a);
    printf("\nInorder:\n");
    inorder(a);
    printf("\nPosorder:\n");
    posorder(a);
    printf("\nReverso:\n");
    reverso(a);
    printf("\nContaPrimo:\n");
    printf("%d", qtdPrimo(a));

    return 0;
}