#include <stdio.h>
#include <stdlib.h>
#include "TAD fila.h"

Fila *fila_cria(void)
{
    Fila *nova = (Fila *)malloc(sizeof(Fila));

    nova->ini = nova->fim = NULL;
    return nova;
}

void fila_enfileira(Fila *fila, float valor)
{
    Lista *nova = (Lista *)malloc(sizeof(Lista));
    nova->info = valor;
    nova->prox = NULL;

    if (fila->fim != NULL)
        fila->fim->prox = nova;
    else
    {
        fila->ini = nova;
        fila->fim = nova;
    }
}

float fila_desinfileira(Fila *fila)
{
    Lista *temporaria;
    float valor;

    if (fila_vazia(fila))
    {
        printf("Lista vazia otario\n");
        exit(1);
    }

    temporaria = fila->ini;
    valor = temporaria->info;
    fila->ini = temporaria->prox;

    if (fila->ini == NULL)
        fila->fim = NULL;

    free(temporaria);

    return (valor);
}

int fila_vazia(Fila *fila)
{
    return fila->ini == NULL;
}

void fila_libera(Fila *fila)
{
    Lista *percorrer = fila->ini;

    while (percorrer != NULL)
    {
        Lista *guardador = percorrer->prox;
        free(percorrer);
        percorrer = guardador;
    }

    free(fila);
}