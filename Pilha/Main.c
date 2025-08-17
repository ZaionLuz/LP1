#include <stdio.h>
#include <stdlib.h>
#include "TAD Pilha.c"

int main()
{
    Pilha *p = pilha_cria();

    printf("Pilha está vazia? %s\n", pilha_vazia(p) ? "Sim" : "Não");

    pilha_push(p, 10.5);
    pilha_push(p, 20.0);
    pilha_push(p, 30.2);

    printf("Pilha está vazia? %s\n", pilha_vazia(p) ? "Sim" : "Não");

    printf("Elemento removido: %.2f\n", pilha_pop(p));
    printf("Elemento removido: %.2f\n", pilha_pop(p));
    printf("Elemento removido: %.2f\n", pilha_pop(p));

    // Após esvaziar a pilha
    printf("Pilha está vazia? %s\n", pilha_vazia(p) ? "Sim" : "Não");

    pilha_libera(p);
    return 0;
}
