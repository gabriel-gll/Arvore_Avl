#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    int valor;
    struct no *esquerdo, *direito;
    short altura;
    char nome[30];
}No;


No* novoNo(int x);

short maior(short a, short b);

short alturaDoNo(No *no);

short fatorDeBalanceamento(No *no);

No* rotacaoEsquerda(No *r);

No* rotacaoDireita(No *r);

No* rotacaoEsquerdaDireita(No *r);

No* rotacaoDireitaEsquerda(No *r);

No* balancear(No *raiz);

No* inserir(No *raiz, int x, char nome[30]);

No* remover(No *raiz, int chave,int x);

void imprimir(No *raiz, int nivel);

No* editar(No *raiz, int buscar, int novo_valor, char nome[30]);

void editar_string(No *raiz, int buscar, char nome[30]);

int quantidade_de_no(No *raiz);

void imprimir_ordenado(No *raiz);

void desalocar_arvore(No *raiz);

No* buscar_imprimir(No *raiz, int buscar);

void limpar_tela();


int main(){

    int opcao, valor,buscar,novo_valor;
    char nome[30];
    No *raiz = NULL;
    No *aux;

    do{
        printf("\n\t\t\t         ARVORE AVL\n");
        printf("\t\t\t\t         Escolha uma opcao das seguintes:\n");
        printf("\t\t\t\t         0 - Fechar programa\n\n");
        printf("\t\t\t\t         1 - Inserir No\n\n");
        printf("\t\t\t\t         2 - Remover No\n\n");
        printf("\t\t\t\t         3 - Imprimir em formato de Arvore\n\n");
        printf("\t\t\t\t         4 - Editar todos os componentes do No\n\n");
        printf("\t\t\t\t         5 - Editar apenas a string do No\n\n");
        printf("\t\t\t\t         6 - Imprimir a quantidade de Nos da Arvore\n\n");
        printf("\t\t\t\t         7 - Imprimir de forma ordenada\n\n");
        printf("\t\t\t\t         8 - Imprimir a altura da Arvore\n\n");
        printf("\t\t\t\t         9 - Buscar um No e imprimir os componentes desse No\n\n");
        printf("\t\t\t\t         10 - Limpar a tela\n");
        scanf("%d", &opcao);

        switch(opcao){
        case 0:
            printf("Saida");
            desalocar_arvore(raiz);
            break;
        case 1:
            printf("Digite o valor a ser inserido:\n");
            scanf("%d", &valor);
            printf("Digite a string a ser inserida\n");
            fflush(stdin);
            fgets(nome,30,stdin);
            nome[strcspn(nome, "\n")]=0;
            raiz = inserir(raiz, valor, nome);
            break;
        case 2:
            printf("Digite o valor a ser removido:\n");
            scanf("%d", &valor);
            raiz = remover(raiz, valor,0);
            break;
        case 3:
            imprimir(raiz, 1);
            break;
        case 4:
            printf("O estado atual da arvore: \n");
            imprimir(raiz,1);
            printf("\nDigite o valor do elemento a ser editado:\n");
            scanf("%d",&buscar);
            printf("Digite o valor que substituira o valor do elemento que foi escolhido\n");
            scanf("%d",&novo_valor);
            printf("Digite a nova string que substituira a string do elemento\n");
            fflush(stdin);
            fgets(nome,30,stdin);
            nome[strcspn(nome, "\n")]=0;
            raiz=editar(raiz,buscar,novo_valor,nome);
            break;
        case 5:
            printf("O estado atual da arvore: \n");
            imprimir(raiz,1);
            printf("\nDigite o valor do elemento a ser editado:\n");
            scanf("%d",&buscar);
            printf("Digite a nova string que subsitituira a string do elemento\n");
            fflush(stdin);
            fgets(nome,30,stdin);
            nome[strcspn(nome,"\n")]=0;
            editar_string(raiz,buscar,nome);
            break;
        case 6:
            if(raiz == NULL){
                printf("A arvore esta vazia\n");
            }
            else{
                printf("A quantidade de Nos da Arvore e : %d", quantidade_de_no(raiz));
            }
            break;
        case 7:
            if(raiz){
                printf("\nO que esta dentro dos parenteses representa um No\n");
            }
            imprimir_ordenado(raiz);
            break;
        case 8:
            if(raiz == NULL){
                printf("A arvore esta vazia\n");
            }
            printf("Altura da arvore: %d\n",alturaDoNo(raiz));
            break;
        case 9:
            if(raiz == NULL){
                printf("A arvore esta vazia, nao existe nenhum No para ser buscado\n");
            }
            else{
                printf("Digite o valor do No para as informacoes desse no serem impressas\n");
                scanf("%d",&buscar);
                aux=buscar_imprimir(raiz,buscar);
            }
            if(aux == NULL){
                printf("Este No nao existe na arvore\n");
            }else{
                printf("O No foi encontrardo\n");
                printf("O valor do No e: %d a string do No e: %s",aux->valor,aux->nome);
            }
            break;
        case 10:
            limpar_tela();
            break;
        default:
            printf("Esta opcao nao existe!!\n");
        }

    }while(opcao != 0);

    return 0;
}


// A funcao cria um novo no
No* novoNo(int x){
    No *novo = malloc(sizeof(No));

    if(novo){
        novo->valor = x;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->altura = 0;
    }
    else
        printf("\nERRO ao alocar nó em novoNo!\n");
    return novo;
}

// A funcao compara a altura de dois nos e retorna a maior altura
short maior(short a, short b){
    return (a > b)? a: b;
}


//  Retorna a altura de um nó ou -1 caso ele seja null
short alturaDoNo(No *no){
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

//   Calcula e retorna o fator de balanceamento de um nó
short fatorDeBalanceamento(No *no){
    if(no)
        return (alturaDoNo(no->esquerdo) - alturaDoNo(no->direito));
    else
        return 0;
}

// --------- ROTACOES ---------------------------

// Funcao para a rotacao a esquerda
No* rotacaoEsquerda(No *r){
    No *y, *f;

    y = r->direito;
    f = y->esquerdo;

    y->esquerdo = r;
    r->direito = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

    return y;
}

// Funcao para a rotação a direita
No* rotacaoDireita(No *r){
    No *y, *f;

    y = r->esquerdo;
    f = y->direito;

    y->direito = r;
    r->esquerdo = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

    return y;
}

No* rotacaoEsquerdaDireita(No *r){
    r->esquerdo = rotacaoEsquerda(r->esquerdo);
    return rotacaoDireita(r);
}

No* rotacaoDireitaEsquerda(No *r){
    r->direito = rotacaoDireita(r->direito);
    return rotacaoEsquerda(r);
}

// Funcao para executar o balanceamento da arvore
No* balancear(No *raiz){
    short fb = fatorDeBalanceamento(raiz);

    // Rotação à esquerda
    if(fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0)
        raiz = rotacaoEsquerda(raiz);

    // Rotação à direita
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0)
        raiz = rotacaoDireita(raiz);

    // Rotação dupla à esquerda
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);

    // Rotação dupla à direita
    else if(fb < -1 && fatorDeBalanceamento(raiz->direito) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}

// Insere o um novo no
No* inserir(No *raiz, int x, char nome[30]){
    if(raiz == NULL){
        No *novo=(No*)malloc(sizeof(No));
        novo->valor=x;
        strcpy(novo->nome,nome);
        novo->esquerdo=NULL;
        novo->direito=NULL;
        novo->altura=0;
        return novo;
    } // arvore vazia
    else{ // insercao sera a esquerda ou a direita
        if(x < raiz->valor)
            raiz->esquerdo = inserir(raiz->esquerdo, x, nome);
        else if(x > raiz->valor)
            raiz->direito = inserir(raiz->direito, x, nome);
        else
            printf("\nInsercao nao realizada!\nO elemento %d a existe!\n", x);
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo no inserido
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

    // Verifica se e necessario fazer o balanceamento da arvore
    raiz = balancear(raiz);

    return raiz;
}

//  Função para remover um no da arvore binaria balanceada pode ser necessario rebalancear a arvore e a raiz
No* remover(No *raiz, int chave, int x) {
    if(raiz == NULL){
        printf("Valor nao encontrado!\n");
        return NULL;
    } else { // procura o no a remover
        if(raiz->valor == chave) {
            // remove nos folhas 
            if(raiz->esquerdo == NULL && raiz->direito == NULL) {
                free(raiz);
                if(x == 0){
                    printf("Elemento folha removido: %d !\n", chave);
                }
                return NULL;
            }
            else{
                // remover nos que possuem 2 filhos
                if(raiz->esquerdo != NULL && raiz->direito != NULL){
                    No *aux = raiz->esquerdo;
                    while(aux->direito != NULL)
                        aux = aux->direito;
                    raiz->valor = aux->valor;
                    aux->valor = chave;
                    printf("Elemento trocado: %d !\n", chave);
                    raiz->esquerdo = remover(raiz->esquerdo, chave,x);
                    return raiz;
                }
                else{
                    // remover nos que possuem apenas 1 filho
                    No *aux;
                    if(raiz->esquerdo != NULL)
                        aux = raiz->esquerdo;
                    else
                        aux = raiz->direito;
                    free(raiz);
                    printf("Elemento com 1 filho removido: %d !\n", chave);
                    return aux;
                }
            }
        } else {
            if(chave < raiz->valor)
                raiz->esquerdo = remover(raiz->esquerdo, chave,x);
            else
                raiz->direito = remover(raiz->direito, chave,x);
        }

        // Recalcula a altura de todos os nos entre a raiz e o novo no inserido
        raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

        // Verifica se e necessario fazer o balanceamento da arvore
        raiz = balancear(raiz);

        return raiz;
    }
}
// Funcao para imprimir a arvore
void imprimir(No *raiz, int nivel){
    int i;
    if(raiz){
        imprimir(raiz->direito, nivel + 1);
        printf("\n\n");

        for(i = 0; i < nivel; i++)
            printf("\t");

        printf("%d-%s", raiz->valor, raiz->nome);
        imprimir(raiz->esquerdo, nivel + 1);
    }
}
// Funcao para editar os componentes do no
No* editar(No *raiz, int buscar, int novo_valor, char nome[30]){
    raiz=remover(raiz,buscar,1);
    raiz=inserir(raiz,novo_valor,nome);
    return raiz;
}
// Funcao para editar apenas a string do no
void editar_string(No *raiz, int buscar, char nome[30]){
    if(raiz == NULL){
        printf("Esse codigo nao existe\n");
    }
    else{
        if(raiz->valor == buscar){
            strcpy(raiz->nome,nome);
        }
        else{
            if(buscar > raiz->valor){
                return editar_string(raiz->direito,buscar,nome);
            }
            else{
                return editar_string(raiz->esquerdo,buscar,nome);
            }
        }
    }
}

// Funcao para contar a quantidade de nos da arvore
int quantidade_de_no(No *raiz){
    if(raiz == NULL){
        return 0;
    }
    else{
        return quantidade_de_no(raiz->esquerdo)+quantidade_de_no(raiz->direito)+1;
    }
}

// Funcao para imprimir de forma ordenada a arvore
void imprimir_ordenado(No *raiz){
    if(raiz){
        imprimir_ordenado(raiz->esquerdo);
        printf("(Valor: %d string: %s) ",raiz->valor,raiz->nome);
        imprimir_ordenado(raiz->direito);
    }
}

// Desaloca a arvore
void desalocar_arvore(No *raiz){
    if(raiz != NULL){
        desalocar_arvore(raiz->direito);
        desalocar_arvore(raiz->esquerdo);
        free(raiz);
    }
}

// Funcao para buscar e imprimir um no caso esse no n exista sera informado que o no nao consta na arvore
No* buscar_imprimir(No *raiz, int buscar){
    if(raiz == NULL){
        return raiz;
    }
    else{
        if(raiz->valor == buscar){
            return raiz;
        }
        else{
            if(buscar > raiz->valor){
                return buscar_imprimir(raiz->direito,buscar);
            }
            else{
                return buscar_imprimir(raiz->esquerdo,buscar);
            }
        }
    }
}

// Funcao para limpar a tela
void limpar_tela(){
#ifdef __linux__
    system("clear");
#elif _WIN32
    system("cls");
#else
#endif
}