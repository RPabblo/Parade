#include <stdio.h>
#include <stdlib.h>

#include "carta.h"
#include "jogo.h"
#include "lista.h"
#include "pilha.h"


typedef struct carta {
    struct face Face;
    struct carta *proximo;
}Carta;


Carta * criar_carta(int valor, char naipe)
{
    Carta *nova_carta = malloc(sizeof(Carta));
    nova_carta->Face.valor = valor;
    nova_carta->Face.naipe = naipe;
    nova_carta->proximo = NULL;

    return nova_carta;
}


void distribuir_cartas(Pilha *baralho, Lista *mao, Lista *mesa)
{
    if(mao == NULL || mesa == NULL || baralho == NULL)
        return;

    Carta *carta = NULL;
    int i;

    for(i = 0; i < 5; i++) {
        carta = criar_carta(baralho->topo->Face.valor, baralho->topo->Face.naipe);

        inserir_lista(mao, carta);
        remover_pilha(baralho, baralho->topo);

        carta = criar_carta(baralho->topo->Face.valor, baralho->topo->Face.naipe);

        inserir_lista(mesa, carta);
        remover_pilha(baralho, baralho->topo);
    }
}


void tela(Pilha *baralho, Lista *mao, Lista *mesa, Lista *colecao_jogador, Lista *colecao_pc)
{
    int i;

    printf("\n-----------------------------------------------------------------------------------------------\n\n");
    printf("Mesa:  [Nova Carta] -> ");
    imprimir_lista(mesa);
    printf(" | %d cartas\n\n", tamanho_pilha(baralho));

    printf("Sua colecao:\n");
    imprimir_colecao(colecao_jogador);

    //printf("---------------\nColecao do PC\n");
    //imprimir_colecao(colecao_pc);

    printf("---------------\nSua mao:  ");
    imprimir_lista(mao);
    printf("\n    ");
    for(i = 1; i < tamanho_lista(mao) + 1; i++)
        printf("        %d", i);

    printf("\n\n");

}


void jogador_joga(Pilha *baralho, Lista *mao, Lista *mesa, Lista *colecao_jogador)
{
    Carta *nova_carta = NULL, *temp = NULL;
    int i, j, n, escolha;
    printf("Escolha qual carta da sua mao sera a NOVA CARTA...\n->");
    scanf("%d", &escolha);
    while( getchar() != '\n' );

    // Verifica se a carta escolhida é valida
    if(escolha <= 0 || escolha > tamanho_lista(mao))
        return jogador_joga(baralho, mao, mesa, colecao_jogador);

    // Se sim, adiciona a carta escolhida à mesa e remove-a da mão do jogador.
    temp = mao->primeiro;

    for(i = 0; i < escolha - 1; i++)
        temp = temp->proximo;

    nova_carta = criar_carta(temp->Face.valor, temp->Face.naipe);
    inserir_lista(mesa, nova_carta);
    remover_qualquer(mao, temp);


    // Primeiro, protege as cartas necessárias
    n = mesa->primeiro->Face.valor;
    temp = mesa->primeiro;

    for(j = 0;  j < n + 1 && temp != NULL; j++)
        temp = temp->proximo;

    // Caso hajam cartas não protegidas, move para a coleção as cartas de mesmo naipe e/ou com valor igual ou menor que a carta escolhida
    if(temp != NULL) {
        while(temp != NULL) {
            if(temp->Face.naipe == mesa->primeiro->Face.naipe || temp->Face.valor <= mesa->primeiro->Face.valor) {
                nova_carta = criar_carta(temp->Face.valor, temp->Face.naipe);
                inserir_colecao(colecao_jogador, nova_carta);
                remover_qualquer(mesa, temp);
            }
            temp = temp->proximo;
        }
    }

    Carta *nova_carta2= criar_carta(baralho->topo->Face.valor, baralho->topo->Face.naipe);
    inserir_lista(mao, nova_carta2);
    remover_pilha(baralho, baralho->topo);

    printf("\n");
}


void pc_joga(Pilha *baralho, Lista *mesa, Lista *colecao_pc)
{
    Carta *nova_carta = criar_carta(baralho->topo->Face.valor, baralho->topo->Face.naipe);
    inserir_lista(mesa, nova_carta);

    printf("O PC jogou. Tirou a carta [%d %c] do topo do baralho e colocou no fim da fila.\n", mesa->primeiro->Face.valor, mesa->primeiro->Face.naipe);

    Carta *temp = mesa->primeiro;
    int i, n = mesa->primeiro->Face.valor;

    // Primeiro, protege as cartas necessárias
    for(i = 0; i < n + 1 && temp != NULL; i++)
        temp = temp->proximo;

    // Caso hajam cartas não protegidas, move para a coleção as cartas de mesmo naipe e/ou com valor igual ou menor que a carta escolhida
    if(temp !=  NULL) {
        while(temp != NULL) {
           if(temp->Face.naipe == mesa->primeiro->Face.naipe || temp->Face.valor <= mesa->primeiro->Face.valor) {
                nova_carta = criar_carta(temp->Face.valor, temp->Face.naipe);
                inserir_colecao(colecao_pc, nova_carta);
                remover_qualquer(mesa, temp);
            }
            temp = temp->proximo;
        }
    }

    remover_pilha(baralho, baralho->topo);
}

