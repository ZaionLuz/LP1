#include <stdlib.h>
#include <stdlib.h>

// Pilha com Lista

typedef struct lista
{
    float info;
    struct lista *prox;
} Lista;

typedef struct pilha
{
    Lista *primeiro;
} Pilha;

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

// Fila com Lista

typedef struct lista
{
    float info;
    struct lista *prox;
} Lista;

typedef struct fila
{
    Lista *ini;
    Lista *fim;
} Fila;

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

// Listas Genericas

struct listagen
{
    void *info;
    struct listagen *prox;
};

typedef struct listagen Listagen;

Listagen *lstgen_cria()
{
    return NULL;
}

int lstgen_vazia(Listagen *l)
{
    return l == NULL;
}

Listagen *lstgen_insere(Listagen *l, void *elemento)
{
    Listagen *nova = (Listagen *)malloc(sizeof(Listagen));

    nova->info = elemento;
    nova->prox = l;

    return nova;
}

void lstgen_percorre(Listagen *l, void (*processa)(void *))
{
    Listagen *percorre;

    for (percorre = l; percorre != NULL; percorre = percorre->prox)
        processa(percorre->info);
}

void *lstgen_busca(Listagen *l, int (*compara)(void *, void *), void *dado)
{
    Listagen *p = l;

    while (p != NULL)
    {
        if (compara(p->info, dado))
            return p->info;
        p = p->prox;
    }

    return NULL;
}

Listagen *lstgen_retira(Listagen *l, int (*compara)(void *, void *), void *dado)
{
    Listagen *p = l;
    Listagen *ant = NULL;

    while (p != NULL)
    {

        if (compara(p->info, dado))
        {

            if (ant == NULL)
            {
                Listagen *temp = p->prox;
                free(p);
                l = temp;
            }
            else
            {
                ant->prox = p->prox;
                free(p);
            }

            return l;
        }

        ant = p;
        p = p->prox;
    }

    return l;
}

Listagen *lstgen_duplica(Listagen *l, void *(*duplica)(void *))
{
    Listagen *nova_lista = lstgen_cria();
    for (Listagen *p = l; p != NULL; p = p->prox)
        nova_lista = lstgen_insere(nova_lista, duplica(p->info));

    return nova_lista;
}

void lstgen_libera(Listagen *l)
{
    Listagen *p = l;

    while (p != NULL)
    {
        free(p->info);
        Listagen *guardador = p->prox;
        free(p);
        p = guardador;
    }
}

Listagen *lstgen_filtra(Listagen *l, int (*criterio)(void *))
{
    Listagen *nova_lista = lstgen_cria();
    Listagen *p = l;

    while (p != NULL)
    {
        if (criterio(p->info))
            nova_lista = lstgen_insere(nova_lista, p->info);
        p = p->prox;
    }

    return nova_lista;
}

Listagen *lstgen_ordena(Listagen *l, int (*compara)(void *, void *))
{
    for (Listagen *p = l; p != NULL; p = p->prox)
    {
        Listagen *q = p->prox;
        while (q != NULL)
        {
            if (compara(p->info, q->info))
            {
                void *aux = q->info;
                q->info = p->info;
                p->info = aux;
            }
            q = q->prox;
        }
    }

    return l;
}