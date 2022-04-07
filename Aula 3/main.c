#include <stdio.h>
#include <stdlib.h>
#include "rb.h"
#include <stdlib.h>
#include <string.h>

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void printBT(char* string, arvore arvore, int isRight){
    if(arvore != NULL){
        printf("%s", string);
        printf(isRight ? "├──" : "└──" );

        switch (arvore->cor) {
            case PRETO:
                printf("\x1b[30m%d\x1b[0m\n", arvore->valor);
                break;
            case VERMELHO:
                printf("\x1b[31m%d\x1b[0m\n", arvore->valor);
                break;
            case DUPLO_PRETO:
                printf("\x1b[32m%d\x1b[0m\n", arvore->valor);
                break;
        }

        printBT( concat(string, (isRight ? "│   " : "    ")), arvore->direito, 1);
        printBT(concat(string, (isRight ? "│   " : "    ")) , arvore->esquerdo, 0);
    }
}


int main(int argc, char * argv[]) {
	arvore a = NULL;
	int opcao;
	inicializar(&a);

    adicionar(20, &a);
    adicionar(15, &a);
    adicionar(8, &a);
    printBT("",a, 0);
    adicionar(25, &a);
    printBT("",a, 0);
    adicionar(30, &a);
    printBT("",a, 0);
    adicionar(40, &a);
    printBT("",a, 0);
    adicionar(7, &a);
    adicionar(24, &a);
    adicionar(14, &a);
    adicionar(9, &a);
    printBT("",a, 0);
    adicionar(19, &a);
    adicionar(43, &a);
    printBT("",a, 0);
    adicionar(11, &a);
    printBT("",a, 0);
    adicionar(1, &a);
    adicionar(33, &a);
    printBT("",a, 0);
    adicionar(38, &a);

    printBT("", a, 0);
    imprimir(a);

	/*while(1) {
		scanf("%d", &opcao);

		switch(opcao) {
				int valor;
				case 1:
						printf("%d\n", altura(a));
						break;
				case 2:
						scanf("%d", &valor);
						adicionar(valor, &a);
						break;
				case 3:
						printf("%d\n", maior_elemento(a));
						break;
				case 4:
						printf("%d\n", menor_elemento(a));
						break;
				case 5:
						pre_order(a);
						printf("\n");
						break;
				case 6:
						in_order(a);
						printf("\n");
						break;
				case 7:
						pos_order(a);
						printf("\n");
						break;
				case 8:
						scanf("%d", &valor);
						remover(valor, &a);
						break;
				case 9:
						imprimir(a);
						printf("\n");
						break;

				case 99:
						exit(0);
		}
	}*/
}
