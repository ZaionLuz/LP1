#ifndef TAD_Lista_Heterogenea_H
#define TAD_Lista_Heterogenea_H

typedef struct retangulo
{
    float base;
    float altura;
} Retangulo;

typedef struct triangulo
{
    float base;
    float altura;
} Triangulo;

typedef struct circulo
{
    float raio;
} Circulo;

#define RET 0
#define TRI 1
#define CIR 2

typedef struct listahet
{
    int tipo;
    void *info;
    struct listahet *prox;
} Listahet;

Listahet* cria_ret(float base,float altura);
Listahet* cria_tri(float base,float altura);
Listahet* cria_cir(float raio);
float area(Listahet*p);
float max_area(Listahet*l);

#define PI 3.14

#endif