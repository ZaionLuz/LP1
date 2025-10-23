#ifndef __TAD_Arvore_H__
#define __TAD_Arvore_H__

struct arv
{
    char info;
    struct arv *sae;
    struct arv *sad;
};

typedef struct arv Arv;

Arv *arv_criavazia(void);
Arv *arv_cria(char c, Arv *e, Arv *d);
Arv *arv_libera(Arv *a);
int arv_vazia(Arv *a);
int arv_pertence(Arv *a, char c);
void arv_imprime(Arv *a);
int arv_altura(Arv *a);
int arv_qtd_letra_min(Arv *a);
int arv_qtd_folhas(Arv *a);

#endif