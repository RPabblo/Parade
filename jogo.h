#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

typedef struct pilha Pilha;
typedef struct lista Lista;


Carta * criar_carta(int valor, char naipe);

void distribuir_cartas(Pilha *baralho, Lista *mao, Lista *mesa);

void tela(Pilha *baralho, Lista *mao, Lista *mesa, Lista *colecao_jogador, Lista *colecao_pc);

void jogador_joga(Pilha *baralho, Lista *mao, Lista *mesa, Lista *colecao_jogador);

void pc_joga(Pilha *baralho, Lista *mesa, Lista *colecao_pc);

#endif // JOGO_H_INCLUDED
