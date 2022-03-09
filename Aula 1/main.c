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
    a = inserir(a, 12);
    a = inserir(a, 82);
    a = inserir(a, 43);
    a = inserir(a, 42);

    /*a = inserir(a, 45);
    a = inserir(a, 43);
    a = inserir(a, 42);
    a = inserir(a, 80);
    a = inserir(a, 79);
    a = inserir(a, 84);
    a = inserir(a, 83);
    a = inserir(a, 86);
    a = inserir(a, 82);*/

    printf("Preorder: \n");
    preorder(a);
    printf("\nInorder:\n");
    inorder(a);
    printf("\nPosorder:\n");
    posorder(a);
    printf("\nReverso:\n");
    reverso(a);
    printf("\nQuantidade de primos:\n");
    printf("[%d]", qtdPrimo(a));
    printf("\nSucessor:\n");
    printf("%d", sucessor(100, a));
    printf("\nRemover:\n");
    a = remover(32, a);

    return 0;
}