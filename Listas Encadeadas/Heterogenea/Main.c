#include <stdio.h>
#include <stdlib.h>
#include "TAD Lista Heterogenea.c"

int main()
{
    // Criando formas geométricas
    Listahet *r = cria_ret(4.0, 5.0);  // Área = 20.0
    Listahet *t = cria_tri(3.0, 6.0);  // Área = 18.0 (mas precisa dividir por 2)
    Listahet *c = cria_cir(2.0);       // Área ≈ 12.5664

    // Corrigindo a lista encadeada
    r->prox = t;
    t->prox = c;

    // Calcula e imprime a maior área
    float maior = max_area(r);
    printf("Maior área: %.2f\n", maior);

    // Liberação de memória
    Listahet *p = r;
    while (p != NULL)
    {
        Listahet *temp = p->prox;
        free(p->info);
        free(p);
        p = temp;
    }

    return 0;
}
