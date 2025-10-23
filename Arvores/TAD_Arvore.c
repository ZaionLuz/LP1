#include "TAD_Arvore.h"
#include <stdlib.h>
#include <stdio.h>

Arv *arv_criavazia(void)
{
    return NULL;
}

Arv *arv_cria(char c, Arv *e, Arv *d)
{
    Arv *nova = (Arv *)malloc(sizeof(Arv));
    if (!nova)
    {
        printf("Não foi posivel alocar memoria\n");
        exit(1);
    }

    nova->info = c;
    nova->sae = e;
    nova->sad = d;

    return nova;
}

Arv *arv_libera(Arv *a)
{
    if (!arv_vazia(a))
    {
        arv_libera(a->sae);
        arv_libera(a->sad);
        free(a);
    }
    return NULL;
}

int arv_vazia(Arv *a)
{
    return a == NULL;
}

int arv_pertence(Arv *a, char c)
{
    if (arv_vazia(a))
        return 0;

    else
        return arv_pertence(a->sae, c) || arv_pertence(a->sad, c) || a->info == c;
}

void arv_imprime(Arv *a)
{
    if (arv_vazia(a))
        return; // se a árvore é vazia, não imprime nada e sai da função

    printf("info: %c\n", a->info);
    arv_imprime(a->sae);
    arv_imprime(a->sad);
}

int arv_altura(Arv *a)
{
    if (arv_vazia(a))
        return -1;
    else
    {
        int altura_sae = arv_altura(a->sae);
        int altura_sad = arv_altura(a->sad);
        int max = altura_sad > altura_sae ? altura_sad : altura_sae;
        return 1 + max;
    }
}

int arv_qtd_letra_min(Arv *a)
{
    if (arv_vazia(a))
        return 0;
    else if ('a' <= a->info && a->info <= 'z')
        return 1 + arv_qtd_letra_min(a->sae) + arv_qtd_letra_min(a->sad);
    else
        return arv_qtd_letra_min(a->sae) + arv_qtd_letra_min(a->sad);
}

int arv_qtd_folhas(Arv *a)
{
    if (arv_vazia(a))
    {
        return 0;
    }
    else
    {
        int total_folhas = arv_qtd_folhas(a->sae) + arv_qtd_folhas(a->sad);
        if (total_folhas)
            return total_folhas;
        else
            return 1;
    }
}