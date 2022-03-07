#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

arvore inserir(arvore subarvore, int valor){
    //Caso base de recursão
    if (subarvore == NULL){
        arvore no = (arvore) malloc(sizeof(no));
        no->valor = valor;
        no->esquerdo = NULL;
        no->direito = NULL;
        return no;
    } else{
        if(valor < subarvore->valor){
            subarvore->esquerdo = inserir(subarvore->esquerdo, valor);
        } else{
            subarvore->direito = inserir(subarvore->direito, valor);
        }
        return subarvore;
    }
}

void preorder(arvore a){
    if(a != NULL){
        printf("[%d]", a->valor);
        preorder(a->esquerdo);
        preorder(a->direito);
    }
}
