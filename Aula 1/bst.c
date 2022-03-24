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

int isPrimo(int valor){
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

int qtdPrimo(arvore a){
    if(a == NULL){
        return 0;
    }

    if(isPrimo(a->valor)){
        return 1 + qtdPrimo(a->esquerdo) + qtdPrimo(a->direito);
    }

    return 0 + qtdPrimo(a->esquerdo) + qtdPrimo(a->direito);
}

int sucessor(int n, arvore a){
    arvore encontrado = busca(n, a);

    if(encontrado != NULL){
        if(encontrado->valor >= a->valor){
            arvore hold = menorNo(encontrado->direito);
            return hold == NULL ? -1 : hold->valor;
        }else{
            arvore sucessor = NULL;
            arvore valor_atual = a;
            while(valor_atual != encontrado){
                if(encontrado->valor < valor_atual->valor){
                    sucessor = valor_atual;
                    valor_atual = valor_atual->esquerdo;
                } else {
                    valor_atual = valor_atual->direito;
                }
            }
            return sucessor->valor;
        }
    }
    return -1;
}

void caminho(int n, arvore a){
    if(a != NULL){
        if(a->valor == n){
            printf("[%d]", a->valor);
        }

        if(a->valor > n){
            printf("[%d]", a->valor);
            caminho(n, a->esquerdo);
        }else if(a->valor < n){
            printf("[%d]", a->valor);
            caminho(n, a->direito);
        }
    }
}

//Retorna o maior nó entre os dois nós mais próximos da raiz na esquerda
arvore maiorNo(arvore a){
    if(a != NULL){
        if(a->direito == NULL){
            return a;
        }
        return maiorNo(a->direito);
    }
    return NULL;
}

//Busca o menor nó na direita
arvore menorNo(arvore a){
    if(a != NULL){
        if(a->esquerdo == NULL){
            return a;
        }
        return menorNo(a->esquerdo);
    }
    return NULL;
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
            arvore maiorElemento = maiorNo(a->esquerdo);
            a->valor = maiorElemento->valor;

            a-> esquerdo = remover(maiorElemento->valor, a->esquerdo);

            return a;
        }
    }else{
        if(n < a->valor){
            a->esquerdo = remover(n, a->esquerdo);
        }else{
            a->direito = remover(n, a->direito);
        }
        return a;
    }
}

int altura(arvore a){
    if (a == NULL)
        return -1;
    else {
        int maxEsquerdo = altura(a->esquerdo);
        int maxDireito = altura(a->direito);

        return max(maxEsquerdo, maxDireito) + 1;
    }
}

int max(int maxEsquerdo, int maxDireito){
    return (maxEsquerdo > maxDireito) ? maxEsquerdo : maxDireito;
}
