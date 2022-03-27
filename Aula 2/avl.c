#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

arvore busca(tipo_dado n, arvore a){
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

arvore maiorNo(arvore a){
    if(a != NULL){
        if(a->direito == NULL){
            return a;
        }
        return maiorNo(a->direito);
    }
    return NULL;
}

arvore menorNo(arvore a){
    if(a != NULL){
        if(a->esquerdo == NULL){
            return a;
        }
        return menorNo(a->esquerdo);
    }
    return NULL;
}

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

arvore rotacaoDuplaDireita(arvore pivot){
    arvore u = pivot->esquerdo;
    arvore v = u->direito;
    arvore t1 = u->esquerdo;
    arvore t2 = v->esquerdo;
    arvore t3 = v->direito;
    arvore t4 = pivot->direito;

    pivot->esquerdo = v;
    v->esquerdo = u;
    u->direito = t2;

    pivot->esquerdo = t3;
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

    pivot->direito = v;
    v->direito = u;
    u->esquerdo = t3;

    pivot->direito = t2;
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
    if(pivot->ftBalanco > 0){
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
            case -1:
                return rotacaoDireita(pivot);
            case 1:
                return rotacaoDuplaDireita(pivot);
        }
    }
}

arvore inserir(arvore subarvore, tipo_dado valor, int *cresceu){
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

            raiz->esquerdo = remover(maiorElemento->valor, raiz->esquerdo, diminuiu);

            if(*diminuiu == 1){
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
                        if(raiz->direito->ftBalanco != 0){
                            *diminuiu = 1;
                        }else{
                            *diminuiu = 0;
                        }
                        return rotacionar(raiz);
                }
            }

            return raiz;
        }
    }

    if(valor < raiz->valor){
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
                    if(raiz->direito->ftBalanco != 0){
                        *diminuiu = 1;
                    }else{
                        *diminuiu = 0;
                    }

                    return rotacionar(raiz);
            }
        }
    }else{
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
                    if(raiz->esquerdo->ftBalanco != 0){
                        *diminuiu = 1;
                    }else{
                        *diminuiu = 0;
                    }
                    return rotacionar(raiz);
                case 1:
                    raiz->ftBalanco = 0;
                    *diminuiu = 1;
                    break;
            }
        }
    }


    return raiz;
}