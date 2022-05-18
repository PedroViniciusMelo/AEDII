#include <stdio.h>
#include <stdlib.h>
#include "rb.h"
#include <string.h>

arvore no_null;

int inicializarTabela(tabela *tab){
    inicializar(&tab->indices);

    tab->arquivo_dados = fopen(DATABASE_FILE, "a+");
    tab->indices = carregar_arquivo(INDEXES_FILE, tab->indices);

    return tab->arquivo_dados != NULL ? 1 : 0;
}

dado * ler_dados() {
    dado *novo = (dado *) malloc(sizeof(dado));
    char *buffer = (char *) malloc(sizeof(char ) * 256);

    getchar();
    printf("Código: ");
    scanf("%d", &novo->chave);
    getchar();

    printf("Titulo: ");
    fgets(buffer, 255,  stdin);
    tirar_enter(buffer);
    novo->titulo = strdup(buffer);

    printf("Autor: ");
    fgets(buffer, 255,  stdin);
    tirar_enter(buffer);
    novo->autor = strdup(buffer);

    printf("Ano: ");
    scanf("%d", &novo->ano);
    getchar();

    free(buffer);

    return novo;
}

void adicionarLivro (tabela *tabela, dado *livro){
    //Significa que o arquivo foi aberto com sucesso
    if(tabela->arquivo_dados != NULL){
        //Cria um novo índice
        tipo_dado * indice = (tipo_dado *) malloc(sizeof (tipo_dado));
        indice->chave = livro->chave;
        fseek(tabela->arquivo_dados, 0L, SEEK_END);

        //Procura a posição final do arquivo e adiciona ao índice
        indice->indice = ftell(tabela->arquivo_dados);

        //Estratégia para salvar o livro
        char * format = "%d|%s|%s|%d\n";
        fprintf(tabela->arquivo_dados, format, livro->chave, livro->titulo, livro->autor, livro->ano);

        adicionar(indice, &tabela->indices);
    }
}

void tirar_enter(char *string) {
    string[strlen(string) -1] = '\0';
}

void finalizar (tabela *tab) {
    fclose(tab->arquivo_dados);
    salvar_arquivo(INDEXES_FILE, tab->indices);
}

void salvar_arquivo(char *nome, arvore a) {
    FILE *arq;
    arq = fopen(nome, "wb");
    if(arq != NULL) {
        salvar_auxiliar(a, arq);
        fclose(arq);
    }
}

void salvar_auxiliar(arvore raiz, FILE *arq){
    if(raiz != NULL) {
        if(arq != NULL){
            fwrite(raiz->valor, sizeof(tipo_dado), 1, arq);
            salvar_auxiliar(raiz->esquerdo, arq);
            salvar_auxiliar(raiz->direito, arq);
        }
    }
}

dado * buscar_livro(tabela *table, int chave){
    if (table->arquivo_dados != NULL) {
        arvore temp = table->indices;

        while (temp != NULL) {
            if (temp->valor->chave == chave) {
                dado *livro = (dado *) malloc(sizeof(dado));
                char *buffer = (char *) malloc(456 * sizeof(char));

                fseek(table->arquivo_dados, temp->valor->indice, SEEK_SET);
                fgets(buffer, 456, table->arquivo_dados);

                char *tempString;

                tempString = strtok(buffer, "|");
                livro->chave = atoi(tempString) ;
                tempString = strtok(NULL, "|");
                livro->titulo = strdup(tempString);
                tempString = strtok(NULL, "|");
                livro->autor = strdup(tempString);
                tempString = strtok(NULL, "|");
                livro->ano = atoi(tempString);

                free(buffer);

                return livro;
            } else {
                if (chave > temp->valor->chave)
                    temp = temp->direito;
                else
                    temp = temp->esquerdo;
            }
        }
    }

    return NULL;
}


arvore carregar_arquivo(char *nome, arvore a) {
    FILE *arq;
    arq = fopen(nome, "rb");
    tipo_dado * temp;
    if(arq != NULL) {
        temp = (tipo_dado *) malloc(sizeof(tipo_dado));

        while(fread(temp, sizeof(tipo_dado), 1, arq)) {
            adicionar(temp, &a);
            temp = (tipo_dado *) malloc(sizeof(tipo_dado));
        }
        fclose(arq);
    }

    return a;
}

/*
Inicializa a árvore vazia com a raiz = null e inicializa o nó nulo duplo preto que será utilizado no método remover.
*/
void inicializar(arvore *raiz) {
    *raiz = NULL;
    no_null = (arvore) malloc(sizeof(struct no_bst));
    no_null->cor = DUPLO_PRETO;
    no_null->esquerdo = NULL;
    no_null->direito = NULL;
}

/* Adiciona um novo elemento na árvore.
Parâmetros:
    valor   - elemento a ser adicionado
    raiz    - árvore onde o elemento será adicionado.
              Observe que este parâmetro é um ponteiro de ponteiro
*/
void adicionar(tipo_dado *valor, arvore *raiz) {
    arvore posicao, pai, novo;
    //utiliza-se *raiz, por ser um ponteiro de ponteiro
    posicao = *raiz;
    pai = NULL;

    /*navega na árvore até encontrar a posição vaga apropriada para o elemento,
        nesta "descida" é necessário manter o ponteiro para o pai, pois após encontrar
        a posição vaga (NULL) não seria possível navegar para o pai com o ponteiro posicao->pai */
    while (posicao != NULL) {
        pai = posicao;
        //Modificação aqui para comparar as chaves
        if (valor->chave > posicao->valor->chave)
            posicao = posicao->direito;
        else
            posicao = posicao->esquerdo;
    }

    //Após achar a posição, inicializa o novo elemento
    novo = (arvore) malloc(sizeof(struct no_bst));
    novo->valor = valor;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    novo->pai = pai;
    novo->cor = VERMELHO;

    //Atualiza a raiz da árvore, caso esteja inserindo o primeiro elemento
    //Observe novamente o uso do ponteiro de ponteiro
    if (eh_raiz(novo))
        *raiz = novo;
    else {
        //Se não for a raiz, é preciso realizar a ligação do pai(direita ou esquerda) com o novo elemento, pegamos
        //O elemento pai para modificação pois estamos na iteração em que o elemento é nulo.
        if (valor->chave > pai->valor->chave)
            pai->direito = novo;
        else
            pai->esquerdo = novo;
    }

    //Após inserir, verifica e ajusta a árvore resultante
    ajustar(raiz, novo);
}


/* Verifica se a árvore está obedecendo todas as regras da RB e aplica as correções necessárias após a inserção.
Parâmetros:
    raiz - raiz (absoluta) da árvore
    elemento - nó recentemente inserido que pode ter causado o desajuste da árvore
*/
void ajustar(arvore *raiz, arvore elemento) {
    //A árvore está desajustada se tanto o elemento quanto o seu pai estiverem com a cor vermelha
    //Utilizamos um while para continuar a verificação até chegar a raiz, quando necessário
    while (cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO) {
        //caso 1: Cor do tio é vermelha, desce o preto do avô
        if (cor(tio(elemento)) == VERMELHO) {
            tio(elemento)->cor = PRETO;
            elemento->pai->cor = PRETO;
            elemento->pai->pai->cor = VERMELHO;
            //Continua a verificação a partir do avô, que mudou para vermelho e pode ter
            //gerado uma sequência vermelho-vermelho
            elemento = elemento->pai->pai;
            continue;
        } else {
            //Tio é preto
            //caso 2a: rotação simples direita
            if (eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)) {
                rotacao_simples_direita(raiz, elemento->pai->pai);
                elemento->pai->cor = PRETO;
                elemento->pai->direito->cor = VERMELHO;
                continue;
            }
            //caso 2b: rotação simples esquerda
            if (eh_filho_direito(elemento) && eh_filho_direito(elemento->pai)) {
                rotacao_simples_esquerda(raiz, elemento->pai->pai);
                elemento->pai->cor = PRETO;
                elemento->pai->esquerdo->cor = VERMELHO;
                continue;
            }
            //caso 3a: rotação dupla direita
            if (eh_filho_direito(elemento) && eh_filho_esquerdo(elemento->pai)) {
                rotacao_dupla_direita(raiz, elemento->pai->pai);
                elemento->cor = PRETO;
                elemento->direito->cor = VERMELHO;
                continue;
            }
            //caso 3b: rotação dupla esquerda
            if (eh_filho_esquerdo(elemento) && eh_filho_direito(elemento->pai)) {
                rotacao_dupla_esquerda(raiz, elemento->pai->pai);
                elemento->cor = PRETO;
                elemento->esquerdo->cor = VERMELHO;
                continue;
            }
        }

    }
    //Após todas as correções a raiz pode ter ficado na cor vermelha, portanto passamos ela novamente para cor preta
    (*raiz)->cor = PRETO;
}

/* Realiza a rotação simples direita
Antes da rotação: 
cor(p) = Preto
cor(u) = cor(v) = Vermelho

       p             u
      / \           / \
     u  t2   =>    v   p
    / \               / \
   v  t1             t1 t2

Após aa rotação: 
cor(u) = Preto
cor(v) = cor(p) = Vermelho
*/
void rotacao_simples_direita(arvore *raiz, arvore pivot) {
    arvore u, t1;
    u = pivot->esquerdo;
    t1 = u->direito;

    /*Para fazer a ligação da raiz da sub-árvore resultante com o seu pai, é preciso saber se o pivot p era um filho esquerdo ou direito*/
    int posicao_pivo_esq = eh_filho_esquerdo(pivot);

    //Atualização dos ponteiros
    pivot->esquerdo = t1;
    if (t1 != NULL)
        t1->pai = pivot;

    u->direito = pivot;

    u->pai = pivot->pai;
    pivot->pai = u;



    //Se não existir árvore acima de u, u passa a ser a raiz da árvore
    if (eh_raiz(u))
        *raiz = u;
    else {
        //Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
        if (posicao_pivo_esq)
            u->pai->esquerdo = u;
        else
            u->pai->direito = u;
    }
}

void rotacao_dupla_direita(arvore *raiz, arvore pivot) {
    arvore u = pivot->esquerdo;
    arvore v = u->direito;

    arvore t2 = v->esquerdo;
    arvore t3 = v->direito;
    arvore t4 = pivot->direito;

    int posicao_pivo_esq = eh_filho_esquerdo(pivot);

    pivot->esquerdo = v;
    v->esquerdo = u;
    u->direito = t2;

    pivot->esquerdo = t3;
    v->direito = pivot;

    if (t2 != NULL) {
        t2->pai = u;
    }

    if (t3 != NULL) {
        t3->pai = pivot;
    }

    if (t4 != NULL) {
        t4->pai = pivot;
    }

    v->pai = pivot->pai;
    pivot->pai = v;
    u->pai = v;

    //Se não existir árvore acima de u, u passa a ser a raiz da árvore
    if (eh_raiz(v))
        *raiz = v;
    else {
        //Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
        if (posicao_pivo_esq)
            v->pai->esquerdo = v;
        else
            v->pai->direito = v;
    }
}

void rotacao_dupla_esquerda(arvore *raiz, arvore pivot) {
    arvore u = pivot->direito;
    arvore v = u->esquerdo;
    arvore t2 = v->esquerdo;
    arvore t3 = v->direito;
    arvore t4 = u->direito;

    int posicao_pivo_esq = eh_filho_esquerdo(pivot);

    pivot->direito = v;
    v->direito = u;
    u->esquerdo = t3;

    pivot->direito = t2;
    v->esquerdo = pivot;

    if (t2 != NULL) {
        t2->pai = pivot;
    }

    if (t3 != NULL) {
        t3->pai = u;
    }

    if (t4 != NULL) {
        t4->pai = u;
    }
    v->pai = pivot->pai;

    pivot->pai = v;
    u->pai = v;

    //Se não existir árvore acima de u, u passa a ser a raiz da árvore
    if (eh_raiz(v))
        *raiz = v;
    else {
        //Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
        if (posicao_pivo_esq)
            v->pai->esquerdo = v;
        else
            v->pai->direito = v;
    }
}

void rotacao_simples_esquerda(arvore *raiz, arvore pivot) {
    arvore u, t1;
    u = pivot->direito;
    t1 = u->esquerdo;

    /*Para fazer a ligação da raiz da sub-árvore resultante com o seu pai, é preciso saber se o pivot p era um filho esquerdo ou direito*/
    int posicao_pivo_esq = eh_filho_esquerdo(pivot);

    //Atualização dos ponteiros
    pivot->direito = t1;
    if (t1 != NULL)
        t1->pai = pivot;

    u->esquerdo = pivot;

    u->pai = pivot->pai;
    pivot->pai = u;



    //Se não existir árvore acima de u, u passa a ser a raiz da árvore
    if (eh_raiz(u))
        *raiz = u;
    else {
        //Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
        if (posicao_pivo_esq)
            u->pai->esquerdo = u;
        else
            u->pai->direito = u;
    }
}

/*Retorna a cor de um nó. Observe que, por definição, o null é preto*/
enum cor cor(arvore elemento) {
    enum cor c;
    if (elemento == NULL)
        c = PRETO;
    else
        c = elemento->cor;
    return c;
}

/*Verifica se um nó é a raiz da árvore*/
int eh_raiz(arvore elemento) {
    return (elemento->pai == NULL);
}

/*Verifica se um nó é filho esquerdo*/
int eh_filho_esquerdo(arvore elemento) {
    return (elemento->pai != NULL && elemento == elemento->pai->esquerdo);
}

int eh_filho_direito(arvore elemento) {
    return (elemento->pai != NULL && elemento == elemento->pai->direito);
}

arvore tio(arvore elemento) {
    return irmao(elemento->pai);
}

arvore irmao(arvore elemento) {
    if (eh_filho_esquerdo(elemento))
        return elemento->pai->direito;
    else
        return elemento->pai->esquerdo;
}


void imprimir(arvore raiz, tabela *tab) {
    printf("(");
    if (raiz != NULL) {
        imprimir_elemento(raiz, tab);
        imprimir(raiz->esquerdo, tab);
        imprimir(raiz->direito, tab);
    }
    printf(")");
}


int altura(arvore raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + maior(altura(raiz->direito), altura(raiz->esquerdo));
}

int maior(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}


tipo_dado * maior_elemento(arvore raiz) {
    if (raiz == NULL)
        return NULL;
    if (raiz->direito == NULL)
        return raiz->valor;
    else
        return maior_elemento(raiz->direito);
}

tipo_dado *menor_elemento(arvore raiz) {
    if (raiz == NULL)
        return NULL;
    if (raiz->esquerdo == NULL)
        return raiz->valor;
    else
        return maior_elemento(raiz->esquerdo);
}

void pre_order(arvore raiz, tabela *tab) {
    if (raiz != NULL) {
        imprimir_elemento(raiz, tab);
        pre_order(raiz->esquerdo, tab);
        pre_order(raiz->direito, tab);
    }
}

void pos_order(arvore raiz, tabela *tab) {
    if (raiz != NULL) {
        pos_order(raiz->esquerdo, tab);
        pos_order(raiz->direito, tab);
        imprimir_elemento(raiz, tab);
    }
}

void in_order(arvore raiz, tabela *tab) {
    if (raiz != NULL) {
        in_order(raiz->esquerdo, tab);
        imprimir_elemento(raiz, tab);
        in_order(raiz->direito, tab);
    }
}

void imprimir_elemento(arvore raiz, tabela *tab) {
    dado * temp = (dado *) malloc (sizeof(dado));
	fseek(tab->arquivo_dados, raiz->valor->indice, SEEK_SET);
	fread(temp, sizeof(dado), 1, tab->arquivo_dados);
	printf("[chave : %d, titulo: %s, autor: %s, ano: %d ]\n", raiz->valor->chave, temp->titulo, temp->autor, temp->ano);
	free(temp);
}

void remover(int valor, arvore *raiz) {
    arvore posicao;
    posicao = *raiz;

    while (posicao != NULL) {
        if (valor == posicao->valor->chave) {
            //elemento possui dois filhos
            if (posicao->esquerdo != NULL && posicao->direito != NULL) {
                posicao->valor = maior_elemento(posicao->esquerdo);
                remover(posicao->valor->chave, &(posicao->esquerdo));
                break;
            }

            //O elemento possui apenas um filho (direito)
            if (posicao->esquerdo == NULL && posicao->direito != NULL) {
                //O seu filho direito sobe para a posição do elemento  a ser removido e recebe a cor preta
                arvore elementoDireita = posicao->direito;
                posicao->valor = elementoDireita->valor;
                posicao->cor = PRETO;
                posicao->direito = NULL;

                free(elementoDireita);

                break;
            }


            //O elemento possui apenas um filho (esquerdo)
            if (posicao->direito == NULL && posicao->esquerdo != NULL) {
                arvore elementosEsquerdo = posicao->esquerdo;
                posicao->valor = elementosEsquerdo->valor;
                posicao->cor = PRETO;
                posicao->esquerdo = NULL;

                free(elementosEsquerdo);
                break;
            }

            //O elemento não possui filhos
            if (posicao->esquerdo == NULL && posicao->direito == NULL) {
                //Remover raiz sem filhos
                if (eh_raiz(posicao)) {
                    *raiz = NULL;
                    free(posicao);
                    break;
                }

                //Remover elemento que não possui filhos e não é raiz
                //Se for vermelho, apenas remove atualizando o ponteiro
                //correspondente do pai
                if (posicao->cor == VERMELHO) {
                    if (eh_filho_esquerdo(posicao))
                        posicao->pai->esquerdo = NULL;
                    else
                        posicao->pai->direito = NULL;
                    free(posicao);
                    break;
                } else {
                    //Se o elemento for preto, substitui pelo duplo preto e depois ajusta a árvore
                    no_null->cor = DUPLO_PRETO;
                    no_null->pai = posicao->pai;
                    if (eh_filho_esquerdo(posicao))
                        posicao->pai->esquerdo = no_null;
                    else
                        posicao->pai->direito = no_null;
                    free(posicao);
                    reajustar(raiz, no_null);
                    break;
                }
            }
        }
        if (valor > posicao->valor->chave)
            posicao = posicao->direito;
        else
            posicao = posicao->esquerdo;
    }
}

/*Realiza a correção da árvore após a remoção de um elemento preto que não possui filhos, ou seja, elimina o nó null o duplo-preto.*/

void reajustar(arvore *raiz, arvore elemento) {
//	cor(irmao(elemento)->direito), cor(irmao(elemento)->esquerdo));
    //caso 1
    if (eh_raiz(elemento)) {
        retira_duplo_preto(raiz, elemento);
        return;
    }

    //caso 2
    if (cor(elemento->pai) == PRETO &&
        cor(irmao(elemento)) == VERMELHO &&
        cor(irmao(elemento)->direito) == PRETO &&
        cor(irmao(elemento)->esquerdo) == PRETO) {
        //Verifica se é o caso 2 esquerdo ou direito
        if (eh_filho_esquerdo(elemento))
            rotacao_simples_esquerda(raiz, elemento->pai);
        else
            rotacao_simples_direita(raiz, elemento->pai);
        elemento->pai->pai->cor = PRETO;
        elemento->pai->cor = VERMELHO;

        //Atenção à chamada recursiva do reajustar.
        //O caso 2 não remove o duplo-preto
        reajustar(raiz, elemento);
        return;
    }

    //caso 3
    if (cor(elemento->pai) == PRETO &&
        cor(irmao(elemento)) == PRETO &&
        cor(irmao(elemento)->direito) == PRETO &&
        cor(irmao(elemento)->esquerdo) == PRETO) {
        //Verificar e remover o no_null
        //Chamada recursiva para eliminar o duplo preto do elemento P
        elemento->pai->cor = DUPLO_PRETO;
        irmao(elemento)->cor = VERMELHO;

        retira_duplo_preto(raiz, elemento);
        reajustar(raiz, elemento->pai);

        return;
    }

    //caso 4
    if (cor(elemento->pai) == VERMELHO &&
        cor(irmao(elemento)) == PRETO &&
        cor(irmao(elemento)->direito) == PRETO &&
        cor(irmao(elemento)->esquerdo) == PRETO) {
        //Verificar e remover o no_null

        elemento->pai->cor = PRETO;
        irmao(elemento)->cor = VERMELHO;

        retira_duplo_preto(raiz, elemento);

        return;
    }

    // Casos 5 e 6 ficam mais fáceis separando o esquerdo do direito
    //caso 5a
    if (cor(elemento->pai->direito) == PRETO &&
        cor(elemento->pai->direito->esquerdo) == VERMELHO &&
        cor(elemento->pai->direito->direito) == PRETO) {

        rotacao_simples_direita(raiz, irmao(elemento));
        irmao(elemento)->cor = PRETO;
        irmao(elemento)->direito->cor = VERMELHO;

        reajustar(raiz, elemento);
        return;
    }

    //caso 5b
    if (cor(elemento->pai->esquerdo) == PRETO &&
        cor(elemento->pai->esquerdo->esquerdo) == PRETO &&
        cor(elemento->pai->esquerdo->direito) == VERMELHO) {

        rotacao_simples_esquerda(raiz, irmao(elemento));
        irmao(elemento)->cor = PRETO;
        irmao(elemento)->esquerdo->cor = VERMELHO;

        reajustar(raiz, elemento);
        return;
    }

    //caso 6a
    if (cor(elemento->pai->direito) == PRETO &&
        cor(elemento->pai->direito->direito) == VERMELHO) {
        enum cor hold_cor = elemento->pai->cor;
        rotacao_simples_esquerda(raiz, elemento->pai);

        elemento->pai->pai->cor = hold_cor;
        elemento->pai->cor = PRETO;
        irmao(elemento->pai)->cor = PRETO;

        retira_duplo_preto(raiz, elemento);

        return;
    }

    //caso 6b
    if (cor(elemento->pai->esquerdo) == PRETO &&
        cor(elemento->pai->esquerdo->esquerdo) == VERMELHO) {

        enum cor hold_cor = elemento->pai->cor;
        rotacao_simples_direita(raiz, elemento->pai);

        elemento->pai->pai->cor = hold_cor;
        elemento->pai->cor = PRETO;
        irmao(elemento->pai)->cor = PRETO;

        retira_duplo_preto(raiz, elemento);
        return;
    }
}

void retira_duplo_preto(arvore *raiz, arvore elemento) {
    if (elemento == no_null) {
        if (eh_raiz(elemento)) {
            *raiz = NULL;
        } else {
            if (eh_filho_esquerdo(elemento)) {
                elemento->pai->esquerdo = NULL;
            } else {
                elemento->pai->direito = NULL;
            }
        }
    } else {
        elemento->cor = PRETO;
    }
}

