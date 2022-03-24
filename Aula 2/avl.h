#ifndef AVL_H
#define AVL_H

typedef int tipo_dado;

typedef struct no {
    tipo_dado valor;
    int ftBalanco;
    struct no *esquerdo, *direito;
} no;

typedef no *arvore;

arvore inserir(arvore subarvore, int valor, int *cresceu);

void preorder(arvore a);
void inorder(arvore a);
void posorder(arvore a);
void reverso(arvore a);
int qtdPrimo(arvore a);
int altura(arvore a);
int fatorDeBalanco(arvore a);
int max(int maxEsquerdo, int maxDireito);
int sucessor(int n, arvore a);
void caminho(int n, arvore a);
arvore remover(int n, arvore a, int* diminuiu);
arvore busca(int n, arvore a);
arvore menorNo(arvore a);
arvore maiorNo(arvore a);
//função remover
//calcular ftBalanco da árvore
//função de posorder
//função inorder
#endif