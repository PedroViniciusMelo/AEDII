#ifndef BST_H
#define BST_H
typedef struct no {
    int valor;
    struct no *esquerdo, *direito;
} no;

typedef no *arvore;

arvore inserir(arvore subarvore, int valor);

void preorder(arvore a);
//função remover
//calcular altura da árvore
//função de posorder
//função inorder
#endif