#ifndef RB_H
#define RB_H
#include <stdio.h>
#define INDEXES_FILE "db/indexes.dat"
#define DATABASE_FILE "db/db.txt"

enum cor { VERMELHO, PRETO, DUPLO_PRETO };

typedef struct livro {
    char *titulo;
    char *autor;
    int ano;
    int chave;
} dado;

//Índice
typedef struct indice {
    int chave;
    long indice;
} tipo_dado;

typedef struct no_bst {
    tipo_dado *valor;
    enum cor cor;
    struct no_bst *esquerdo, *direito, *pai;
} no_bst;

typedef no_bst * arvore;

//Tabela de índices
typedef struct tabela {
    FILE *arquivo_dados;
    arvore indices;
} tabela;


int inicializarTabela(tabela *tab);
void inicializar(arvore *raiz);
void finalizar(tabela *tab);

void adicionar(tipo_dado *valor, arvore *raiz);
void adicionarLivro(tabela *tab, dado *livro);

dado * buscar_livro(tabela *table, int chave);

void remover (int valor, arvore *raiz);


//FUnção auxiliar para pegar os dados do livro
dado *ler_dados();
void tirar_enter(char *string);

dado *procurarLivro(tabela *tab, int chave);
void salvar_auxiliar(arvore raiz, FILE *arq);

//Arquivos
arvore carregar_arquivo(char *nome, arvore a);
void salvar_arquivo(char *nome, arvore a);

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//Funções auxilaires da RBT, desconsiderar
int altura(arvore raiz);
int maior(int a, int b);
tipo_dado *maior_elemento(arvore raiz);
tipo_dado *menor_elemento(arvore raiz);
void pre_order(arvore raiz, tabela *tab);
void pos_order(arvore raiz, tabela *tab);
void in_order(arvore raiz, tabela *tab);

void imprimir_elemento(arvore raiz, tabela *tab);
void imprimir(arvore raiz, tabela *tab);


//Funções de rotação da BST, desconsiderar
void ajustar(arvore *raiz, arvore elemento);
void reajustar(arvore *raiz, arvore elemento);
void rotacao_simples_direita(arvore *raiz, arvore pivot);
void rotacao_simples_esquerda(arvore *raiz, arvore pivo);
void rotacao_dupla_direita(arvore *raiz, arvore pivot);
void rotacao_dupla_esquerda(arvore *raiz, arvore pivot);

enum cor cor(arvore elemento);
int eh_raiz(arvore elemento);
int eh_filho_esquerdo(arvore elemento);
int eh_filho_direito(arvore elemento);
arvore irmao(arvore elemento);
arvore tio(arvore elemento);
void retira_duplo_preto(arvore *raiz, arvore elemento);

#endif
