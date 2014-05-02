/*
    Autor: Vinicius Henrique Marangoni
    Data: 05/02/2014

    Por favor, caso for utilizar, nao tire os creditos
*/

#include <stdio.h>
#include <stdlib.h>

struct arvore{
    int n;

    struct arvore *esquerda;
    struct arvore *direita;
    struct arvore *pai;
};

struct arvore *raiz = NULL;

void menu();
void insere();
void exibir_pre(struct arvore*);
void exibir_pos(struct arvore*);
void exibir_ordenado(struct arvore*);
void remove_p();
void remover(struct arvore*);
struct arvore* menor_direita(struct arvore*);
struct arvore* buscar(int);
void limpar_arvore(struct arvore*);
int altura(struct arvore*);

int main(){
    struct arvore *b;
    int op, n;

    while(1){
        menu();

        scanf("%d", &op);
        getchar();

        switch(op){
            case 1: insere();
                    break;

            case 2: remove_p();
                    printf("Pronto!\n");
                    getchar();
                    break;

            case 3: printf("Digite o numero a procurar: ");
                    scanf("%d", &n);
                    getchar();

                    b = buscar(n);

                    if(b){
                        printf("Elemento encontrado: %d\n", b->n);
                    }

                    else{
                        printf("Elemento nao encontrado!\n");
                    }

                    b = NULL;
                    getchar();
                    break;

            case 4: exibir_pre(raiz);
                    printf("\nPronto!\n");
                    getchar();
                    break;

            case 5: exibir_pos(raiz);
                    printf("\nPronto!\n");
                    getchar();
                    break;

            case 6: exibir_ordenado(raiz);
                    printf("\nPronto!\n");
                    getchar();
                    break;

            case 7: printf("Altura da arvore: %d\n", altura(raiz));
                    getchar();
                    break;

            case 8: if(raiz){
                        limpar_arvore(raiz);
                        printf("Arvore limpa!\n");
                    }

                    else{
                        printf("A arvore ja estava limpa!\n");
                    }

                    getchar();
                    break;

            case 9: if(raiz){
                        limpar_arvore(raiz);
                    }

                    exit(0);

            default: printf("Opcao incorreta!\n");
                     getchar();
                     break;
        }
    }
}

void menu(){
    system("clear");

    printf("###############################################\n");
    printf("#----------[Arvore Binaria de Busca]----------#\n");
    printf("###############################################\n\n");

    printf("1 - Inserir\n");
    printf("2 - Remover\n");
    printf("3 - Buscar\n");
    printf("4 - Exibir - Pre Ordem\n");
    printf("5 - Exibir - Pos Ordem\n");
    printf("6 - Exibir - Ordenado\n");
    printf("7 - Altura da arvore\n");
    printf("8 - Limpar Arvore\n");
    printf("9 - Sair\n\n");

    printf("Digite uma opcao: ");

}

void insere(){
    struct arvore *aux1, *aux2;
    int n;

    printf("Digite o numero a inserir: ");
    scanf("%d", &n);
    getchar();

    if(!raiz){
        raiz = (struct arvore*) malloc(sizeof(struct arvore));

        if(!raiz){
            printf("Erro ao alocar =(\n");
            exit(1);
        }

        raiz->n = n;
        raiz->esquerda = NULL;
        raiz->direita = NULL;
        raiz->pai = NULL;
    }

    else{
        aux1 = raiz;
        aux2 = aux1;

        while(aux2){
            if(n < aux2->n){
                aux2 = aux2->esquerda;

                if(!aux2){
                    aux1->esquerda = (struct arvore*) malloc(sizeof(struct arvore));

                    if(!aux1->esquerda){
                        printf("Erro ao alocar =(\n");
                        exit(1);
                    }

                    aux2 = aux1->esquerda;

                    aux2->esquerda = NULL;
                    aux2->direita = NULL;
                    aux2->pai = aux1;
                    aux2->n = n;
                    aux2 = NULL;
                }
                else{
                    aux1 = aux2;
                }
            }

            else{
                aux2 = aux2->direita;

                if(!aux2){
                    aux1->direita = (struct arvore*) malloc(sizeof(struct arvore));

                    if(!aux1->direita){
                        printf("Erro ao alocar =(\n");
                        exit(1);
                    }

                    aux2 = aux1->direita;

                    aux2->esquerda = NULL;
                    aux2->direita = NULL;
                    aux2->pai = aux1;
                    aux2->n = n;
                    aux2 = NULL;
                }

                else{
                    aux1 = aux2;
                }
            }
        }
    }

    printf("Elemento Inserido!\n");
    getchar();
}

void exibir_pre(struct arvore *aux){
    if(!raiz){
        printf("Arvore vazia!");
        return;
    }

    if(aux){
        printf("%d ", aux->n);
        exibir_pre(aux->esquerda);
        exibir_pre(aux->direita);
    }
}

void exibir_pos(struct arvore *aux){
    if(!raiz){
        printf("Arvore vazia!");
        return;
    }

    if(aux){
        exibir_pos(aux->esquerda);
        exibir_pos(aux->direita);
        printf("%d ", aux->n);
    }
}

void exibir_ordenado(struct arvore *aux){
    if(!raiz){
        printf("Arvore vazia!");
        return;
    }

    if(aux){
        exibir_ordenado(aux->esquerda);
        printf("%d ", aux->n);
        exibir_ordenado(aux->direita);
    }
}

void remove_p(){
    struct arvore *aux;
    int n;

    printf("Digite o numero que deseja remover: ");
    scanf("%d", &n);
    getchar();

    aux = buscar(n);

    if(aux){
        remover(aux);
    }

    else{
        printf("O numero nao existe na arvore!\n");
    }
}

void remover(struct arvore *aux){
    struct arvore *aux2;

    if(aux != raiz){
        if(!aux->esquerda && !aux->direita){
            if(aux->n < aux->pai->n){
                aux->pai->esquerda = NULL;
            }
            else{
                aux->pai->direita = NULL;
            }

            free(aux);
        }

        else if(!aux->direita){
            if(aux->n < aux->pai->n){
                aux->pai->esquerda = aux->esquerda;
            }
            else{
                aux->pai->direita = aux->esquerda;
            }
            aux->esquerda->pai = aux->pai;
            free(aux);
        }

        else if(!aux->esquerda){
            if(aux->n < aux->pai->n){
                aux->pai->esquerda = aux->direita;
            }
            else{
                aux->pai->direita = aux->direita;
            }
            aux->direita->pai = aux->pai;
            free(aux);
        }

        else{
            aux2 = menor_direita(aux->direita);
            aux->n = aux2->n;

            remover(aux2);
        }
    }

    else{
        if(!aux->esquerda && !aux->direita){
            free(aux);
            raiz = NULL;
        }

        else if(!aux->direita){
            aux->esquerda->pai = NULL;
            raiz = aux->esquerda;
            free(aux);
        }

        else if(!aux->esquerda){
            aux->direita->pai = NULL;
            raiz = aux->direita;
            free(aux);
        }

        else{
            aux2 = menor_direita(aux->direita);
            aux->n = aux2->n;

            remover(aux2);
        }
    }
}

struct arvore* menor_direita(struct arvore *aux){
    while(aux->esquerda){
        aux = aux->esquerda;
    }

    return aux;
}

struct arvore* buscar(int n){
    struct arvore *aux;

    aux = raiz;

    while(aux && aux->n != n){
        if(n < aux->n){
            aux = aux->esquerda;
        }

        else{
            aux = aux->direita;
        }
    }

    return aux;
}

void limpar_arvore(struct arvore *aux){
    if(aux->esquerda){
        limpar_arvore(aux->esquerda);
    }

    if(aux->direita){
        limpar_arvore(aux->direita);
    }

    free(aux);
    raiz = NULL;
}

int altura(struct arvore *aux){
    if(!aux){
        return -1;
    }

    int ae = altura(aux->esquerda);
    int ad = altura(aux->direita);

    return (ae > ad) ? ae + 1: ad + 1;
}