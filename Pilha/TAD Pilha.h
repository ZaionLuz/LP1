#ifndef TAD_PILHA_H
#define TAD_PILHA_H

typedef struct lista
{
    float info;
    struct lista *prox;
} Lista;

typedef struct pilha
{
    Lista *primeiro;
} Pilha;

Pilha *pilha_cria(void);
void pilha_push(Pilha *pilha, float valor);
float pilha_pop(Pilha *pilha);
int pilha_vazia(Pilha *pilha);
void pilha_libera(Pilha *pilha);

#endif