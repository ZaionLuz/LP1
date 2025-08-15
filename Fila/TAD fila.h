#ifndef FILA_H
#define FILA_H

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

Fila *fila_cria(void);
void fila_enfileira(Fila *fila, float valor);
float fila_desinfileira(Fila *fila);
int fila_vazia(Fila *fila);
void fila_libera(Fila *fila);

#endif