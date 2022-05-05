#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int opcao;
    tabela tabela;
    inicializarTabela(&tabela);
    dado *livro;

    while(1){
        scanf("%d", &opcao);
        switch (opcao) {
            int valor;
            case 1:
                printf("%d\n", altura(tabela.indices));
                break;
            case 2:
                adicionarLivro(&tabela, ler_dados());
                break;
            case 3:
                printf("%d\n", maior_elemento(tabela.indices)->chave);
                break;
            case 4:
                printf("%d\n", menor_elemento(tabela.indices)->chave);
                break;
            case 5:
                pre_order(tabela.indices, &tabela);
                printf("\n");
                break;
            case 6:
                in_order(tabela.indices, &tabela);
                printf("\n");
                break;
            case 7:
                pos_order(tabela.indices, &tabela);
                printf("\n");
                break;
            case 10:
                salvar_arquivo("db/dados.dat", tabela.indices);
                break;
            case 11:
                printf("Informe a chave: ");
                scanf("%d", &valor);
                printf("%d", valor);
                livro = buscar_livro(&tabela, valor);
                if(livro != NULL){
                    printf("[chave : %d, titulo: %s, autor: %s, ano: %d ]\n", livro->chave, livro->titulo, livro->autor, livro->ano);
                }else{
                    printf("NOT FOUND \n");
                }
                break;
            case 99:
                finalizar(&tabela);
                exit(0);
        }
    }
}