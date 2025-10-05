/*1) Em um navegador web, o histórico de navegação pode ser implementado utilizando duas pilhas:
undo: armazena as páginas visitadas em ordem cronológica (a página atual está no topo)
redo: armazena as páginas das quais o usuário voltou, permitindo avançar novamente
Considerando a implementação da TAD Pilha Genérica com lista encadeada:

/*/
typedef struct lista
{
    void *info;
    struct lista *prox;
} Lista;
typedef struct pilha
{
    Lista *topo;
} Pilha;

// Funções disponíveis : Pilha *pilha_criar();

int pilha_vazia(Pilha *p);
void pilha_empilhar(Pilha *p, void *elemento);
void *pilha_desempilhar(Pilha *p);
void *pilha_topo(Pilha *p);

// E considerando que a função abrir_pagina já está implementada :

char *abrir_pagina(char *endereco_pagina, Pilha *undo)
{
    printf("Abrindo página: %s\n", endereco_pagina);
    pilha_empilhar(undo, endereco_pagina);
    return endereco_pagina;
}

/*
Sua tarefa é implementar as funções:

a) (2.5 pontos)
* Retorna a página anterior do histórico (pilha undo),
* armazenando a página atual na pilha redo.
* Retorna a nova página a ser exibida ou NULL se não houver histórico.
*/

char *voltar_pagina(Pilha *undo, Pilha *redo)
{
    if (pilha_vazia(undo))
        return NULL;                              // Nenhuma página
    char *pagina_atual = pilha_desempilhar(undo); // Remove página atual

    if (pilha_vazia(undo))
    {
        // Não há página anterior, volta a empilhar a atual e retorna NULL
        pilha_empilhar(undo, pagina_atual);
        return NULL;
    }

    pilha_empilhar(redo, pagina_atual);           // Guarda a atual no redo
    char *nova_pagina = (char *)pilha_topo(undo); // Nova página atual

    printf("Voltando para página: %s\n", nova_pagina);
    return nova_pagina;
}

/*b) (2.5 pontos)

* Retorna a próxima página do histórico (pilha redo),
* armazenando a página atual na pilha undo.
* Retorna a nova página a ser exibida ou NULL se não houver páginas para avançar.
*/

char *avancar_pagina(Pilha *undo, Pilha *redo)
{
    if (pilha_vazia(redo))
        return NULL; // Nada para avançar

    char *proxima_pagina = (char *)pilha_desempilhar(redo);
    pilha_empilhar(undo, proxima_pagina); // Coloca no histórico

    printf("Avançando para página: %s\n", proxima_pagina);
    return proxima_pagina;
}

/*
2) (5,0 pontos) Considere a TAD_LISTAGEN, que implementa uma lista genérica com as seguintes ope
rações básicas:
*/

struct listagen
{
    void *info;
    struct listagen *prox;
};
typedef struct listagen Listagen;
// Funções disponíveis:
Listagen *lstgen_cria();
int lstgen_vazia(Listagen *l);
Listagen *lstgen_insere(Listagen *l, void *elemento);
void lstgen_percorre(Listagen *l, void (*processa)(void *));
void *lstgen_busca(Listagen *l, int (*compara)(void *, void *), void *dado);
Listagen *lstgen_retira(Listagen *l, int (*compara)(void *, void *), void *dado);
Listagen *lstgen_duplica(Listagen *l, void *(*duplica)(void *));
void lstgen_libera(Listagen *l);

/* Sua tarefa é implementar a função :

     * Filtra os elementos da lista com base em um critério
     * Retorna uma nova lista contendo apenas os elementos que satisfazem o critério
     * A lista original permanece inalterada
     *
     * @param l: lista original
     * @param criterio: função callback que retorna 1 se o elemento deve ser mantido,
     * 0 caso contrário.
     * @return: nova lista com elementos filtrados (deve ser liberada com lstgen_libera)
     */

Listagen *lstgen_filtra(Listagen *l, int (*criterio)(void *))
{
    Listagen *nova = lstgen_cria();
    Listagen *p;

    for (p = l; p != NULL; p = p->prox)
    {
        if (criterio(p->info))
        {
            nova = lstgen_insere(nova, p->info);
        }
    }

    return nova;
}
