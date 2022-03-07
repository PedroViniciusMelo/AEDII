#ifndef BST_H
#define BST_H
typedef struct no
{
    int valor;
    struct no* esq, *dir;
} no ;

typedef no* arvore;

arvore inserir(arvore a, int v);
void preorder(arvore a);
//função remover
//calcular altura da árvore
#endif