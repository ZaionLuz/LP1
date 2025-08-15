#include <stdio.h>
#include <stdlib.h>
#include "TAD fila.c"

int main() {
    Fila *minhaFila = fila_cria();

    fila_enfileira(minhaFila, 10.5);
    fila_enfileira(minhaFila, 20.0);
    fila_enfileira(minhaFila, 30.3);

    printf("Desenfileirando: %.2f\n", fila_desinfileira(minhaFila));
    printf("Desenfileirando: %.2f\n", fila_desinfileira(minhaFila));

    fila_enfileira(minhaFila, 40.1);

    printf("Desenfileirando: %.2f\n", fila_desinfileira(minhaFila));
    printf("Desenfileirando: %.2f\n", fila_desinfileira(minhaFila));

    if (fila_vazia(minhaFila))
        printf("A fila está vazia.\n");
    else
        printf("A fila ainda tem elementos.\n");

    fila_libera(minhaFila);

    return 0;
}
