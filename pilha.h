#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

typedef struct pilha {
    Carta *topo;
    Carta *fundo;
} Pilha;

Pilha * criar_pilha();

void preencher_pilha(Pilha *pilha);

int inserir_topo(Pilha *pilha, Carta *carta);

void imprimir_pilha(Pilha *pilha);

int remover_pilha(Pilha *pilha, Carta *carta);

void embaralhar(Pilha *pilha);

int tamanho_pilha(Pilha *pilha);

#endif // PILHA_H_INCLUDED
