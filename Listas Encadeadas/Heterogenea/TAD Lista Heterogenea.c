#include <stdio.h>
#include <stdlib.h>
#include "TAD Lista Heterogenea.h"

Listahet *cria_ret(float base, float altura)
{
    Retangulo *r;
    Listahet *p;

    r = (Retangulo *)malloc(sizeof(Retangulo));
    r->base = base;
    r->altura = altura;

    p = (Listahet *)malloc(sizeof(Listahet));
    p->tipo = RET;
    p->info = r;
    p->prox = NULL;

    return p;
}

Listahet *cria_tri(float base, float altura)
{
    Triangulo *t;
    Listahet *p;

    t = (Triangulo *)malloc(sizeof(Triangulo));
    t->base = base;
    t->altura = altura;

    p = (Listahet *)malloc(sizeof(Listahet));
    p->tipo = TRI;
    p->info = t;
    p->prox = NULL;

    return p;
}

Listahet *cria_cir(float raio)
{
    Circulo *c;
    Listahet *p;

    c = (Circulo *)malloc(sizeof(Circulo));
    c->raio = raio;

    p = (Listahet *)malloc(sizeof(Listahet));
    p->tipo = CIR;
    p->info = c;
    p->prox = NULL;

    return p;
}

float area(Listahet *p)
{
    float a;

    switch (p->tipo)
    {
    case RET:
    {
        Retangulo *r = (Retangulo *)p->info;
        a = r->base * r->altura;
        break;
    }

    case TRI:
    {
        Triangulo *t = (Triangulo *)p->info;
        a = (t->altura * t->base) / 2;
        break;
    }

    case CIR:
    {
        Circulo *c = (Circulo *)p->info;
        a = PI * c->raio * c->raio;
        break;
    }
    }
    return a;
}

float max_area(Listahet *l)
{
    float amax = 0.0;
    Listahet *p;
    for (p = l; p != NULL; p = p->prox)
    {
        float a = area(p);
        if (a > amax)
            amax = a;
    }
    return amax;
}