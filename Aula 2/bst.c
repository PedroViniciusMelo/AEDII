#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

arvore inserir(arvore a, int v){
    //Caso base de recursão
    //1.in numa (sub)árvore vazia
    if (a == NULL){
        //alocar espaço para o nó
        arvore no = (arvore) malloc(sizeof(no));
        //inicializar os valores das variáveis membro
        no->valor = v;
        no->esq = NULL;
        no->dir = NULL;
        return no;
    } else{
        //Se o valor que eu quero 1.in (v) for
        //menor que a raiz relativa (a->valore), 1.in na
        //sub-árvore a esquerda
        if(v<a->valor){
            a->esq = inserir(a->esq, v);
        } else{
            a->dir = inserir(a->dir, v);

        }
        return a;
    }

    return NULL;
}

void preorder(arvore a){
    if(a != NULL){
        printf("[%d]", a->valor);
        preorder(a->esq);
        preorder(a->dir);
    }
}
