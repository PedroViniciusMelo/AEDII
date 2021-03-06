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
int altura(arvore a);
int max(int maxEsquerdo, int maxDireito);
int sucessor(int n, arvore a);
void caminho(int n, arvore a);
arvore remover(int n, arvore a);
arvore busca(int n, arvore a);
arvore menorNo(arvore a);
arvore maiorNo(arvore a);
//função remover
//calcular altura da árvore
//função de posorder
//função inorder
#endif