#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int opcao;
    tabela tabela;
    inicializarTabela(&tabela);
    dado *livro;

    printf("Sistema para modificacao de livros - AED II\nInforme a opcao desejada\n(1) - Adicionar Livro\n(2) - Buscar Livro\n");
    while(1){
        scanf("%d", &opcao);
        switch (opcao) {
            int valor;
            case 1:
                printf("Adicionar livro \n");
                adicionarLivro(&tabela, ler_dados());
                break;
            case 2:
                printf("Buscar livro \n");
                printf("Informe a chave: ");
                scanf("%d", &valor);
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