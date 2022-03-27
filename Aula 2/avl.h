#ifndef AVL_H
#define AVL_H

typedef int tipo_dado;

typedef struct no {
    tipo_dado valor;
    int ftBalanco;
    struct no *esquerdo, *direito;
} no;

typedef no *arvore;

void imprimir(arvore raiz);
arvore inserir(arvore subarvore, tipo_dado valor, int *cresceu);
arvore remover(tipo_dado n, arvore a, int* diminuiu);
arvore busca(tipo_dado n, arvore a);
arvore menorNo(arvore a);
arvore maiorNo(arvore a);

#endif