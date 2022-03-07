#ifndef BST_H
#define BST_H
typedef struct no {
    int valor;
    struct no *esquerdo, *direito;
} no;

typedef no *arvore;

arvore inserir(arvore subarvore, int valor);

void preorder(arvore a);
void inorder(arvore a);
void posorder(arvore a);
void reverso(arvore a);
int qtdPrimo(arvore a);
//função remover
//calcular altura da árvore
//função de posorder
//função inorder
#endif