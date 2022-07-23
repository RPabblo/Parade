#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct lista {
    struct carta *primeiro;
} Lista;

Lista * criar_lista();

int inserir_lista(Lista *lista, Carta *carta);

int remover_qualquer(Lista *lista, Carta *carta);

int acessar_indice(Lista *lista, int indice);

int tamanho_lista(Lista *lista);

int soma_valores(Lista *lista);

void imprimir_lista(Lista *lista);

void imprimir_colecao(Lista *colecao);

int inserir_colecao(Lista *lista, Carta *carta);

int todas_as_cores(Lista *colecao);

int zeros(Lista *mao);

int contagem_de_pontos(Lista *mao, Lista *colecao_jogador, Lista *colecao_pc);

void baixar_na_mesa(Lista *mao, Lista *colecao_jogador);

#endif // LISTA_H_INCLUDED
