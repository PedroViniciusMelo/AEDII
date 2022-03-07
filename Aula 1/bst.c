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

void inorder(arvore a){
    if(a != NULL){
        inorder(a->esquerdo);
        printf("[%d]", a->valor);
        inorder(a->direito);
    }
}

void posorder(arvore a){
    if(a != NULL){
        posorder(a->esquerdo);
        posorder(a->direito);
        printf("[%d]", a->valor);
    }
}

void reverso(arvore a){
    if(a != NULL){
        reverso(a->direito);
        printf("[%d]", a->valor);
        reverso(a->esquerdo);
    }
}

int contaPrimos (arvore a, int val){
    if(a != NULL){
        contaPrimos(a->esquerdo, val);
        contaPrimos(a->direito, val);

        int divisores = 0;

        for (int i = 2; i <= a->valor; ++i) {
            if (a->valor % i == 0) {
                divisores++;
            }
        }
        printf("%d ", a->valor);
        if(divisores == 1){
            printf("%d", a->valor);
        }
        return divisores == 1 ? val + 1 : val;
    }
    return val;
}
int qtdPrimo(arvore a){
    return contaPrimos(a, 0);
}
