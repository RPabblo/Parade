// Made by: Rwann Pabblo

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "carta.h"
#include "jogo.h"
#include "lista.h"
#include "pilha.h"


int main()
{
    printf("Bem - vindo ao jogo PARADE :)\n\n");

    // Inicialização de estruturas
    srand(time(NULL));

    Pilha *baralho = criar_pilha();
    Lista *mao = criar_lista();
    Lista *mesa = criar_lista();

    preencher_pilha(baralho);
    embaralhar(baralho);
    distribuir_cartas(baralho, mao, mesa);

    Lista colecao_jogador[6];
    Lista colecao_pc[6];

    int i, n;
    for(i = 0; i < 6; i++) {
        colecao_jogador[i].primeiro = NULL;
        colecao_pc[i].primeiro = NULL;
    }

    tela(baralho, mao, mesa, colecao_jogador, colecao_pc);

    // Loop principal, onde a maior parte do jogo acontece
    for(i = 0; i < 28; i++) {
        jogador_joga(baralho, mao, mesa, colecao_jogador);

        if(todas_as_cores(colecao_jogador) == 6) {
            tela(baralho, mao, mesa, colecao_jogador, colecao_pc);

            printf("Coletou todas as cores.\nVoce perdeu :(\n\n");
            return 0;
        }

        pc_joga(baralho, mesa, colecao_pc);
        tela(baralho, mao, mesa, colecao_jogador, colecao_pc);
    }

    printf("\n\nFIM DE JOGO\n\n=============\n");


    if(zeros(mao) == 2 && contagem_de_pontos(mao, colecao_jogador, colecao_pc) == 0)
        printf("2 zeros na mao e 0 pontos.\nVITORIA PERFEITA!!!\n");

    else if(zeros(mao) == 2)
        printf("2 zeros na mao.\nVITORIA!\n");

    else {
        baixar_na_mesa(mao, colecao_jogador);
        contagem_de_pontos(mao ,colecao_jogador, colecao_pc);
    }

    printf("\n================================================================================\n");

    return 0;
}
