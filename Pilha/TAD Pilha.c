#include <stdio.h>
#include <stdlib.h>
#include "TAD Pilha.h"

Pilha *pilha_cria(void)
{
    Pilha *novo = (Pilha *)malloc(sizeof(Pilha));

    novo->primeiro = NULL;

    return novo;
}

void pilha_push(Pilha *pilha, float valor)
{
    Lista *nova = (Lista *)malloc(sizeof(Lista));

    nova->info = valor;
    nova->prox = pilha->primeiro;
    pilha->primeiro = nova;
}

float pilha_pop(Pilha *pilha)
{
    Lista *guardador;
    float valor;

    if (pilha == NULL)
    {
        printf("Pilha vazia otario\n");
        exit(1);
    }

    guardador = pilha->primeiro;
    valor = guardador->info;
    pilha->primeiro = guardador->prox;
    free(guardador);
    return valor;
}

int pilha_vazia(Pilha *pilha)
{
    return pilha->primeiro == NULL;
}

void pilha_libera(Pilha *pilha)
{
    Lista *percorrer = pilha->primeiro;

    while (percorrer != NULL)
    {
        Lista *guardador = percorrer->prox;
        free(percorrer);
        percorrer = guardador;
    }
    free(pilha);
}