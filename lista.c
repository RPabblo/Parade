#include <stdio.h>
#include <stdlib.h>

#include "carta.h"
#include "jogo.h"
#include "lista.h"
#include "pilha.h"


struct carta {
    struct face Face;
    struct carta *proximo;
};


Lista * criar_lista()
{
    Lista *nova_lista = malloc(sizeof(Lista));

    if(nova_lista == NULL) {
        printf("Erro ao alocar lista.\n");
        return;
    }

    nova_lista->primeiro = NULL;
    return nova_lista;
}


int inserir_lista(Lista *lista, Carta *carta)
{
    if(lista == NULL)
        return 1;

    if(lista->primeiro == NULL) {
        lista->primeiro = carta;
        return 0;
    }

    carta->proximo = lista->primeiro;
    lista->primeiro = carta;
    return 0;
}


int remover_qualquer(Lista *lista, Carta *carta)
{
    if(lista == NULL || lista->primeiro == NULL)
        return 1;

    Carta *temp = lista->primeiro;

    if(temp == carta) {
        lista->primeiro = temp->proximo;
        free(temp);
        return 0;
    }

    while(temp->proximo != NULL && temp->proximo != carta)
        temp = temp->proximo;

    if(temp->proximo == carta) {
        free(temp->proximo);
        temp->proximo = carta->proximo;
    }
    return 0;
}


int acessar_indice(Lista *lista, int indice)
{
    if(lista == NULL || lista->primeiro == NULL)
        return 0;

    Carta *temp = lista->primeiro;
    int i;

    for(i = 0; i < indice && temp != NULL; i++) {
        temp = temp->proximo;
    }

    if(temp != NULL)
        printf("Carta acessada: [%d %c]", temp->Face.valor, temp->Face.naipe);

    return 0;
}



int tamanho_lista(Lista *lista)
{
    if(lista == NULL || lista->primeiro == NULL)
        return 0;

    int cont = 0;

    Carta *temp = lista->primeiro;

    while(temp != NULL) {
        cont += 1;
        temp = temp->proximo;
    }
    return cont;
}


int soma_valores(Lista *lista)
{
    if(lista == NULL || lista->primeiro == NULL)
        return 0;

    int soma = 0;

    Carta *temp = lista->primeiro;

    while(temp != NULL) {
        soma += temp->Face.valor;
        temp = temp->proximo;
    }
    return soma;
}


void imprimir_lista(Lista *lista)
{
    if(lista == NULL || lista->primeiro == NULL)
        return;

    Carta *temp = lista->primeiro;

    while(temp != NULL) {
        if(temp->proximo != NULL)
            printf("[%d %c] -> ", temp->Face.valor, temp->Face.naipe);
        else
            printf("[%d %c]", temp->Face.valor, temp->Face.naipe);
        temp = temp->proximo;
    }
}


void imprimir_colecao(Lista *colecao)
{
    int i;
    char cararcteres[] = {'A', 'B', 'C', 'D', 'E', 'F'};

    for(i = 0; i < 6; i++)
    {
        printf("%c: ", cararcteres[i]);
        imprimir_lista(&(colecao[i]));
        printf("\n\n");
    }
}


int inserir_colecao(Lista *colecao, Carta *carta)
{
    switch(carta->Face.naipe)
    {
        case 'A':
            inserir_lista(&(colecao[0]), carta);
            break;

        case 'B':
            inserir_lista(&(colecao[1]), carta);
            break;

        case 'C':
            inserir_lista(&(colecao[2]), carta);
            break;

        case 'D':
            inserir_lista(&(colecao[3]), carta);
            break;

        case 'E':
            inserir_lista(&(colecao[4]), carta);
            break;

        case 'F':
            inserir_lista(&(colecao[5]), carta);
            break;

        default:
            break;
    }

    return 0;
}


int todas_as_cores(Lista *colecao)
{
    // Retorna a quantidade de cores que a coleção possui
    int i, cont = 0;

    for(i = 0; i < 6; i++) {
        if(tamanho_lista(&(colecao[i])) > 0) {
            cont += 1;
        }
    }

    return cont;
}


int zeros(Lista *mao)
{
    Carta *temp = mao->primeiro;
    int cont = 0;

    while(temp != NULL) {
        if(temp->Face.valor == 0) {
            cont += 1;
        }
        temp = temp->proximo;
    }

    return cont;
}


void baixar_na_mesa(Lista *mao, Lista *colecao_jogador)
{
    Carta *nova_carta = NULL, *temp = NULL;
    int i, j, n, escolha1, escolha2;

    printf("Você escolherá 2 cartas para DESCARTAR\nPrimeira carta: ");
    scanf("%d", &escolha1);
    while( getchar() != '\n' );

    printf("Segunda carta: ");
    scanf("%d", &escolha2);
    while( getchar() != '\n' );

    // Verifica se as cartas escolhidas são válidas
    if(escolha1 <= 0 || escolha1 > tamanho_lista(mao) || escolha2 <= 0 || escolha2 > tamanho_lista(mao))
        return baixar_na_mesa(mao, colecao_jogador);

    temp = mao->primeiro;
    for(i = 0; i < escolha1; i++)
        temp = temp->proximo;

    // Move carta da nao para a coleção
    nova_carta = criar_carta(temp->Face.valor, temp->Face.naipe);
    inserir_colecao(colecao_jogador, temp);
    remover_qualquer(mao, temp);

    temp = mao->primeiro;
    for(i = 0; i < escolha2; i++)
        temp = temp->proximo;

    // Move carta da nao para a coleção
    nova_carta = criar_carta(temp->Face.valor, temp->Face.naipe);
    inserir_colecao(colecao_jogador, temp);
    remover_qualquer(mao, temp);
}


int contagem_de_pontos(Lista *mao, Lista *colecao_jogador, Lista *colecao_pc)
{
    Carta *temp_jogador = NULL;
    Carta *temp_pc = NULL;

    int i, pontos_jogador = 0, pontos_pc = 0;

    for(i = 0; i < 6; i++)
    {
        if(tamanho_lista(&(colecao_jogador[i])) > tamanho_lista(&(colecao_pc[i]))) {
            pontos_jogador += tamanho_lista(&(colecao_jogador[i]));
            pontos_pc += soma_valores(&(colecao_pc[i]));
        }

        else if(tamanho_lista(&(colecao_jogador[i])) < tamanho_lista(&(colecao_pc[i]))) {
            pontos_jogador += soma_valores(&(colecao_jogador[i]));
            pontos_pc += tamanho_lista(&(colecao_pc[i]));
        }

        else if(tamanho_lista(&(colecao_jogador[i])) < tamanho_lista(&(colecao_pc[i]))) {
            pontos_jogador += tamanho_lista(&(colecao_jogador[i]));
            pontos_pc += tamanho_lista(&(colecao_pc[i]));
        }
        else printf("ERRO\n");
    }

    if(pontos_jogador == 0)
        return 0;

    printf("Pontos do jogador: %d.\nPontoz do PC: %d.\n\n", pontos_jogador, pontos_pc);

    if(pontos_jogador < pontos_pc) {
        printf("Voce fez menos pontos :D\n");
        return 1;
    }

    if(pontos_jogador > pontos_pc) {
        printf("Voce fez mais pontos :(\n");
        return 2;
    }

    else
        printf("Empate. Qual a chence? 0_0\n\n");

    return 3;
}
