#include <stdio.h>
#include "TAD_Arvore.c"

#include <stdio.h>
#include <stdlib.h>
#include "TAD_Arvore.h"

int main()
{
    // Cria uma árvore manualmente
    // Exemplo de estrutura:
    //        A
    //       / \            /
    //      B   C
    //         / \         /
    //        D   E

    Arv *a = arv_cria('A',
                      arv_cria('B', arv_criavazia(), arv_criavazia()),
                      arv_cria('C',
                               arv_cria('D', arv_criavazia(), arv_criavazia()),
                               arv_cria('E', arv_criavazia(), arv_criavazia())));

    printf("Arvore criada!\n\n");

    printf("Impressao da arvore:\n");
    arv_imprime(a);

    printf("\n\nTestando arv_pertence:\n");
    printf("Existe o elemento 'C'? %s\n", arv_pertence(a, 'C') ? "Sim" : "Nao");
    printf("Existe o elemento 'Z'? %s\n", arv_pertence(a, 'Z') ? "Sim" : "Nao");

    printf("\nLiberando memoria...\n");
    a = arv_libera(a);

    if (arv_vazia(a))
        printf("Arvore liberada com sucesso!\n");

    return 0;
}
