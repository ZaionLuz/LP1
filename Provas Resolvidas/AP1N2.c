/*
Considerando a TAD Tabela Hash de alunos vista em sala, conforme abaixo:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

typedef struct aluno
{
    int mat;
    char nome[81];
    char email[51];
    struct aluno *prox;
} Aluno;

typedef Aluno *TABELA[N];

/*
QUESTÃO 1 (3,0 pontos)

Implemente uma função que retorne a quantidade de elementos que colidiram
e foram inseridos na mesma posição da tabela hash.

Assinatura:
int hsh_qtd_colisao(TABELA tab, int indice);
*/

int hsh_qtd_colisao(TABELA tab, int indice)
{
    int contador = 0;
    Aluno *aux = tab[indice];

    while (aux != NULL)
    {
        contador++;
        aux = aux->prox;
    }

    return contador;
}

/*
QUESTÃO 2 (3,0 pontos)

Implemente uma função que retorne o índice que tem o maior número de colisões
em uma tabela hash.

Assinatura:
int hsh_maior_colisao(TABELA tab);
*/

int hsh_maior_colisao(TABELA tab)
{
    int i;
    int maior = 0;
    int indice_maior = 0;

    for (i = 0; i < N; i++)
    {
        int contador = 0;
        Aluno *aux = tab[i];

        while (aux != NULL)
        {
            contador++;
            aux = aux->prox;
        }

        if (contador > maior)
        {
            maior = contador;
            indice_maior = i;
        }
    }

    return indice_maior;
}

/*
QUESTÃO 3 (4,0 pontos)

Implemente uma função que crie uma CÓPIA PROFUNDA de toda a tabela hash,
incluindo todos os nós encadeados.

A função deve alocar uma nova tabela e novos nós para todos os alunos,
copiando corretamente todos os dados.

Assinatura:
Aluno** hsh_clone(Aluno **tab, int TAM);
*/

Aluno **hsh_clone(Aluno **tab, int TAM)
{
    int i;

    /* Aloca a nova tabela hash */
    Aluno **nova_tabela = (Aluno **)malloc(TAM * sizeof(Aluno *));

    if (nova_tabela == NULL)
    {
        return NULL;
    }

    /* Inicializa todas as posições da nova tabela */
    for (i = 0; i < TAM; i++)
    {
        nova_tabela[i] = NULL;
    }

    /* Percorre cada índice da tabela original */
    for (i = 0; i < TAM; i++)
    {
        Aluno *atual = tab[i];
        Aluno *ultimo = NULL;

        /* Percorre a lista encadeada daquele índice */
        while (atual != NULL)
        {
            /* Cria um novo nó (cópia profunda) */
            Aluno *novo = (Aluno *)malloc(sizeof(Aluno));

            if (novo == NULL)
            {
                return nova_tabela; /* em prova, isso é aceitável */
            }

            /* Copia os dados */
            novo->mat = atual->mat;
            strcpy(novo->nome, atual->nome);
            strcpy(novo->email, atual->email);
            novo->prox = NULL;

            /* Insere na nova lista */
            if (nova_tabela[i] == NULL)
            {
                nova_tabela[i] = novo;
            }
            else
            {
                ultimo->prox = novo;
            }

            ultimo = novo;
            atual = atual->prox;
        }
    }

    return nova_tabela;
}
