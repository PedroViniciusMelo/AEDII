#include "bst.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    arvore a;
    //Inicialização da árvore vazia
    a = NULL;
    a = inserir(a, 10);
    a = inserir(a, 8);
    a = inserir(a, 9);
    a = inserir(a, 2);
    preorder(a);

    return 0;
}