#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "carta.h"
#include "jogo.h"
#include "lista.h"
#include "pilha.h"


struct carta {
    struct face Face;
    struct carta *proximo;
};

Pilha * criar_pilha()
{
    Pilha *nova_pilha = malloc(sizeof(Pilha));

    if(nova_pilha == NULL) {
        printf("Erro ao alocar pilha.\n");
        return;
    }

    nova_pilha->fundo = NULL;
    nova_pilha->topo = NULL;

    return nova_pilha;
}

void preencher_pilha(Pilha *pilha)
{
    if(pilha == NULL) {
        printf("Inicializacao da pilha falfou.\n");
        return;
    }

    Carta *carta = NULL;
    char naipes[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int i, j;

    for(i = 0; i < 11; i++)
    {
        for(j = 0; j < 6; j++)
        {
            carta = criar_carta(i, naipes[j]);
            inserir_topo(pilha, carta);
        }
    }
}


int inserir_topo(Pilha *pilha, Carta *carta)
{
    if(pilha == NULL) {
        printf("Pilha nao alocada;\n");
        return 1;
    }

    if(pilha->topo == NULL) {
        pilha->fundo = carta;
        pilha->topo = carta;
        return;
    }

    carta->proximo = pilha->topo;
    pilha->topo = carta;

    return 0;
}


void imprimir_pilha(Pilha *pilha)
{
    if(pilha == NULL || pilha->topo == NULL)
        return;

    Carta *temp = pilha->topo;

    while(temp != NULL) {
        printf("%d %c\n", temp->Face.valor, temp->Face.naipe);
        temp = temp->proximo;
    }
    printf("\n");
}


int remover_pilha(Pilha *pilha, Carta *carta)
{
    Carta *temp =  pilha->topo;

    // Se a pilha nao alocada ou estiver vazia
    if(pilha == NULL || pilha->topo == NULL)
        return 1;

    // Se há somente uma  carta na pilha
    if(pilha->topo == pilha->fundo && temp == carta) {
        free(temp);
        pilha->fundo = NULL;
        pilha->topo = NULL;
        return 0;
    }

    if(carta == pilha->topo) {
        pilha->topo = pilha->topo->proximo;
        free(temp);
        return 0;
    }

    while(temp->proximo != NULL && temp->proximo != carta)
        temp = temp->proximo;

    if(temp->proximo == carta) {
        free(temp->proximo);
        temp->proximo = carta->proximo;
    }

    // Se, após a remoção, restar apenas uma carta
    if(temp->proximo == NULL) {
        pilha->fundo = temp;
    }

    return 0;
}


void embaralhar(Pilha *pilha)
{
    if(pilha == NULL || pilha->topo == NULL)
        return;

    Pilha *nova_pilha = criar_pilha();
    Carta *temp = NULL;

    int i, j, n;

    for(i = 66; i > 0; --i)
    {
        n = rand() % i;
        temp = pilha->topo;

        for(j = 0; j < n; j++)
            temp = temp->proximo;

        inserir_topo(nova_pilha, criar_carta(temp->Face.valor, temp->Face.naipe));
        remover_pilha(pilha, temp);
    }

    pilha->topo = nova_pilha->topo;
    pilha->fundo = nova_pilha->fundo;
    free(nova_pilha);
}


int tamanho_pilha(Pilha *pilha)
{
    if(pilha == NULL || pilha->topo == NULL)
        return 0;

    Carta *temp = pilha->topo;
    int cont = 0;

    while(temp != NULL) {
        cont += 1;
        temp = temp->proximo;
    }

    return cont;
}

