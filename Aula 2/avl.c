#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

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

arvore rotacaoDireita(arvore pivot){
    arvore u = pivot->esquerdo;
    arvore t2 = u->direito;

    //Realiza a rotação
    u->direito = pivot;
    pivot->esquerdo = t2;

    if(u->ftBalanco == -1){
        pivot->ftBalanco = 0;
        u->ftBalanco = 0;
    }else{
        pivot->ftBalanco = -1;
        u->ftBalanco = 1;
    }

    return u;
}

arvore rotacaoEsquerda(arvore pivot){
    arvore u = pivot->direito;
    arvore t2 = u->esquerdo;

    //Realiza a rotação
    u->esquerdo = pivot;
    pivot->direito = t2;

    if(u->ftBalanco == 1){
        pivot->ftBalanco = 0;
        u->ftBalanco = 0;
    }else{
        pivot->ftBalanco = 1;
        u->ftBalanco = -1;
    }

    return u;
}

/*---
Auxiliar de imprimir
---*/
void imprimir_elemento(arvore raiz) {
    printf("%d [%d]", raiz->valor, raiz->ftBalanco);
}

void imprimir(arvore raiz) {
    printf("(");
    if(raiz != NULL) {
        imprimir_elemento(raiz);
        imprimir(raiz->esquerdo);
        imprimir(raiz->direito);
    }
    printf(")");
}

arvore rotacaoDuplaDireita(arvore pivot){
    arvore u = pivot->esquerdo;
    arvore v = u->direito;
    arvore t1 = u->esquerdo;
    arvore t2 = v->esquerdo;
    arvore t3 = v->direito;
    arvore t4 = pivot->direito;

    u->direito = t1;
    u->esquerdo = t2;
    v->esquerdo = u;
    v->direito = t3;

    pivot->esquerdo = v->direito;
    v->direito = pivot;

    switch (v->ftBalanco) {
        case 0:
            pivot->ftBalanco = 0;
            u->ftBalanco = 0;
            v->ftBalanco = 0;
            break;
        case 1:
            pivot->ftBalanco = 0;
            u->ftBalanco = -1;
            v->ftBalanco = 0;
            break;
        case -1:
            pivot->ftBalanco = 1;
            u->ftBalanco = 0;
            v->ftBalanco = 0;
            break;
    }
    return v;
}

arvore rotacaoDuplaEsquerda(arvore pivot){
    arvore u = pivot->direito;
    arvore v = u->esquerdo;
    arvore t1 = pivot->esquerdo;
    arvore t2 = v->esquerdo;
    arvore t3 = v->direito;
    arvore t4 = u->direito;

    u->direito = t4;
    u->esquerdo = t3;
    v->esquerdo = t2;
    v->direito = u;

    pivot->direito = v->esquerdo;
    v->esquerdo = pivot;

    switch (v->ftBalanco) {
        case 0:
            pivot->ftBalanco = 0;
            u->ftBalanco = 0;
            v->ftBalanco = 0;
            break;
        case -1:
            pivot->ftBalanco = 0;
            u->ftBalanco = 1;
            v->ftBalanco = 0;
            break;
        case 1:
            pivot->ftBalanco = -1;
            u->ftBalanco = 0;
            v->ftBalanco = 0;
            break;
    }
    return v;
}

arvore rotacionar(arvore pivot){
    if(pivot->ftBalanco >= 1){
        //Desbalanceada na direita, necessário rotação para esquerda
        switch (pivot->direito->ftBalanco) {
            //Verificando oscs
            case 0:
            case 1:
                return rotacaoEsquerda(pivot);
            case -1:
                return rotacaoDuplaEsquerda(pivot);
        }
    }else{
        switch (pivot->esquerdo->ftBalanco) {
            case 0:
            case 1:
                return rotacaoDuplaDireita(pivot);
            case -1:
                return rotacaoDireita(pivot);
        }
    }
}

arvore inserir(arvore subarvore, int valor, int *cresceu){
    //Caso base de recursão
    if (subarvore == NULL){
        arvore no = (arvore) malloc(sizeof(no));
        no->valor = valor;
        no->esquerdo = NULL;
        no->direito = NULL;
        no->ftBalanco = 0;
        *cresceu = 1;
        return no;
    }

    if(valor < subarvore->valor){
        //Inserir na esquerda
        subarvore->esquerdo = inserir(subarvore->esquerdo, valor, cresceu);

        if(*cresceu){
            //Propriedade que se aplica a todos os nós
            switch (subarvore->ftBalanco) {
                case 0:
                    subarvore->ftBalanco = -1;
                    *cresceu = 1;
                    break;
                case -1:
                    *cresceu = 0;
                    return rotacionar(subarvore);
                case 1:
                    subarvore->ftBalanco = 0;
                    *cresceu = 0;
                    break;
            }
        }
    } else {
        //Inserir na direita
        subarvore->direito = inserir(subarvore->direito, valor, cresceu);

        if(*cresceu){
            //Propriedade que se aplica a todos os nós
            switch (subarvore->ftBalanco) {
                case 0:
                    subarvore->ftBalanco = 1;
                    *cresceu = 1;
                    break;
                case -1:
                    subarvore->ftBalanco = 0;
                    *cresceu = 0;
                    break;
                case 1:
                    //TESTAR ESSE CASO
                    *cresceu = 0;
                    return rotacionar(subarvore);
            }
        }
    }

    return subarvore;
}

arvore remover (tipo_dado valor, arvore raiz, int *diminuiu) {
    if(raiz == NULL) {
        *diminuiu = 0;
        return NULL;
    }

    if(raiz->valor == valor) {
        *diminuiu = 1;

        if(raiz->esquerdo == NULL && raiz->direito == NULL){
            free(raiz);
            return NULL;
        }

        if(raiz->esquerdo != NULL && raiz->direito == NULL){
            arvore esquerdo = raiz->esquerdo;
            free(raiz);
            return esquerdo;
        }

        if(raiz->direito != NULL && raiz->esquerdo == NULL){
            arvore direito = raiz->direito;
            free(raiz);
            return direito;
        }

        if(raiz->esquerdo != NULL && raiz->direito != NULL){
            arvore maiorElemento = maiorNo(raiz->esquerdo);
            raiz->valor = maiorElemento->valor;

            //Erro está aqui, o fator de balanço não é atualizado nesse returnn da função remover
            raiz->esquerdo = remover(maiorElemento->valor, raiz->esquerdo, diminuiu);

            return raiz;
        }
    }

    if(valor > raiz->valor){
        raiz->direito = remover(valor, raiz->direito, diminuiu);
        //     verifica se a árvore diminuiu e ajusta os fatores de balanço

        if(*diminuiu){
            //Propriedade que se aplica a todos os nós
            switch (raiz->ftBalanco) {
                case 0:
                    raiz->ftBalanco = -1;
                    *diminuiu = 0;
                    break;
                case -1:
                    *diminuiu = 1;
                    return rotacionar(raiz);
                case 1:
                    raiz->ftBalanco = 0;
                    *diminuiu = 1;
                    break;
            }
        }
    }else{
        raiz->esquerdo = remover(valor, raiz->esquerdo, diminuiu);
        if(*diminuiu){
            //Propriedade que se aplica a todos os nós
            switch (raiz->ftBalanco) {
                case 0:
                    raiz->ftBalanco = 1;
                    *diminuiu = 0;
                    break;
                case -1:
                    raiz->ftBalanco = 0;
                    *diminuiu = 1;
                    break;
                case 1:
                    *diminuiu = 1;
                    return rotacionar(raiz);
            }
        }
    }


    return raiz;
}

int altura(arvore a){
    if (a == NULL)
        return 0;
    return a->ftBalanco;
}

int fatorDeBalanco(arvore a)
{
    if (a == NULL)
        return 0;
    return altura(a->direito) - altura(a->esquerdo);
}

int max(int maxEsquerdo, int maxDireito){
    return (maxEsquerdo > maxDireito) ? maxEsquerdo : maxDireito;
}
