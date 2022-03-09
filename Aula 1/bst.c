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

int isPrimo(valor){
    int divisores = 0;

    for (int i = 2; i <= valor; ++i) {
        if (valor % i == 0) {
            divisores++;
        }
    }

    return divisores == 1;
}

arvore busca(int n, arvore a){
    if(a != NULL){
        if(a->valor == n){
            return a;
        }

        if(a->valor > n){
            return busca(n, a->esquerdo);
        }
        return busca(n, a->direito);
    }
    return a;
}

int contaPrimos (arvore a, int val){
    if(a != NULL){
        contaPrimos(a->esquerdo, val);
        contaPrimos(a->direito, val);

        return isPrimo(a->valor) ? val + 1 : val;
    }
    return val;
}

int qtdPrimo(arvore a){
    if(a == NULL){
        return NULL;
    }

    if(isPrimo(a->valor)){
        printf("%d ", a->valor);
        return 1;
    }

    return qtdPrimo(a->esquerdo) + qtdPrimo(a->direito);
}

int sucessor(int n, arvore a){
    arvore encontrado = busca(n, a);

    return menorNo(encontrado->direito)->valor;
}

int caminho(int n, arvore a){

}

//Retonra o maior nó entre os dois nós mais próximos da raiz na esquerda

arvore maiorNo(arvore a){
    if(a->esquerdo != NULL && a->direito != NULL){
        int valor_esquerdo = a->esquerdo->valor, valor_direito = a->direito->valor, valor_atual = a->valor;

        if(!(valor_direito > valor_atual && valor_esquerdo < valor_direito)){
            return maiorNo(a->direito);
        }else{
            return maiorNo(a->esquerdo);
        }
    }else if(a->esquerdo != NULL && a->direito == NULL){
        if(a->esquerdo->valor > a->valor){
            return maiorNo(a->esquerdo);
        }
        return a;
    }else if(a->direito != NULL && a->esquerdo == NULL){
        if(a->direito->valor > a->valor){
            return maiorNo(a->direito);
        }
        return a;
    }else{
        return a;
    }
}

//Busca o menor nó na direita
arvore menorNo(arvore a){
    if(a->esquerdo == NULL){
        return a;
    }
    return menorNo(a->esquerdo);
}

arvore remover(int n, arvore a){
    if(a == NULL){
        return NULL;
    }

    if(n == a->valor){
        if(a->esquerdo == NULL && a->direito == NULL){
            free(a);
            return NULL;
        }

        if(a->esquerdo != NULL && a->direito == NULL){
            arvore esquerdo = a->esquerdo;
            free(a);
            return esquerdo;
        }

        if(a->direito != NULL && a->esquerdo == NULL){
            arvore direito = a->direito;
            free(a);
            return direito;
        }

        if(a->esquerdo != NULL && a->direito != NULL){
            arvore maiorElemento = maiorNo(a);
            a->valor = maiorElemento->valor;

            if(a->esquerdo->valor > a->direito->valor){
                a->direito = remover(maiorElemento->valor, a->direito);
            }else{
                a-> esquerdo = remover(maiorElemento->valor, a->esquerdo);
            }
            return a;
        }
    }else{

        a->esquerdo = remover(n, a->esquerdo);
        a->direito = remover(n, a->direito);

        return a;
    }
}