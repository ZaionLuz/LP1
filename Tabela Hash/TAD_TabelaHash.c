#include "TAD_TabelaHash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int hash(int mat)
{
    return mat % N;
}

/* ------------------- BUSCA ------------------- */
Aluno *hsh_busca(Aluno **tab, int mat)
{
    int h = hash(mat);
    Aluno *atual = tab[h];

    while (atual != NULL)
    {
        if (atual->matricula == mat)
            return atual;
        atual = atual->prox;
    }

    return NULL;
}

/* ------------------- INSERE ------------------- */
Aluno *hsh_insere(Aluno **tab, int mat, char *nome, char *tel, char *email)
{
    int h = hash(mat);
    Aluno *atual = tab[h];

    // Verifica se já existe aluno com a mesma matrícula
    while (atual != NULL)
    {
        if (atual->matricula == mat)
        {
            // Atualiza dados existentes
            strcpy(atual->nome, nome);
            strcpy(atual->telefone, tel);
            strcpy(atual->email, email);
            return atual;
        }
        atual = atual->prox;
    }

    // Insere novo aluno no início da lista
    Aluno *novo = (Aluno *)malloc(sizeof(Aluno));
    if (novo == NULL)
        return NULL;

    novo->matricula = mat;
    strcpy(novo->nome, nome);
    strcpy(novo->telefone, tel);
    strcpy(novo->email, email);
    novo->prox = tab[h];
    tab[h] = novo;

    return novo;
}

/* ------------------- REMOVE ------------------- */
int hsh_remove(Aluno **tab, int mat)
{
    int h = hash(mat);
    Aluno *atual = tab[h];
    Aluno *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->matricula == mat)
        {
            if (anterior == NULL)
                tab[h] = atual->prox;
            else
                anterior->prox = atual->prox;

            free(atual);
            return 1; // sucesso
        }

        anterior = atual;
        atual = atual->prox;
    }

    return 0; // não encontrado
}

/* ------------------- ATUALIZA ------------------- */
int hsh_atualiza(Aluno **tab, int mat, char *nome, char *tel, char *email)
{
    Aluno *aluno = hsh_busca(tab, mat);
    if (aluno == NULL)
        return 0;

    strcpy(aluno->nome, nome);
    strcpy(aluno->telefone, tel);
    strcpy(aluno->email, email);
    return 1;
}

/* ------------------- LISTA TODOS ------------------- */
void hsh_lista_todos(Aluno **tab)
{
    for (int i = 0; i < N; i++)
    {
        Aluno *atual = tab[i];
        if (atual != NULL)
        {
            printf("Posição %d:\n", i);
            while (atual != NULL)
            {
                printf("  Matrícula: %d\n", atual->matricula);
                printf("  Nome: %s\n", atual->nome);
                printf("  Telefone: %s\n", atual->telefone);
                printf("  Email: %s\n", atual->email);
                printf("-----------------------------\n");
                atual = atual->prox;
            }
        }
    }
}

/* ------------------- CONTA ALUNOS ------------------- */
int hsh_conta_alunos(Aluno **tab)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        Aluno *atual = tab[i];
        while (atual != NULL)
        {
            count++;
            atual = atual->prox;
        }
    }
    return count;
}

/* ------------------- BUSCA POR NOME ------------------- */
Aluno *hsh_busca_por_nome(Aluno **tab, char *nome)
{
    for (int i = 0; i < N; i++)
    {
        Aluno *atual = tab[i];
        while (atual != NULL)
        {
            if (strcmp(atual->nome, nome) == 0)
                return atual;
            atual = atual->prox;
        }
    }
    return NULL;
}

/* ------------------- LIMPA TABELA ------------------- */
void hsh_limpa_tabela(Aluno **tab)
{
    if (tab == NULL)
        return;

    for (int i = 0; i < N; i++)
    {
        Aluno *atual = tab[i];
        while (atual != NULL)
        {
            Aluno *tmp = atual->prox;
            free(atual);
            atual = tmp;
        }
        tab[i] = NULL;
    }

    free(tab);
}

/* ------------------- FATOR DE CARGA ------------------- */
float hsh_fator_carga(Aluno **tab)
{
    int total = hsh_conta_alunos(tab);
    return (float)total / N;
}

/* ------------------- VERIFICA VAZIA ------------------- */
int hsh_vazia(Aluno **tab)
{
    if (tab == NULL)
        return 1;

    for (int i = 0; i < N; i++)
    {
        if (tab[i] != NULL)
            return 0;
    }
    return 1;
}

/* ------------------- EXPORTA ARQUIVO ------------------- */
int hsh_exporta_arquivo(Aluno **tab, char *filename, char *(*escrever_linha_csv)(void *))
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
        return 0;

    for (int i = 0; i < N; i++)
    {
        Aluno *atual = tab[i];
        while (atual != NULL)
        {
            char *linha = escrever_linha_csv(atual);
            fprintf(fp, "%s\n", linha);
            free(linha);
            atual = atual->prox;
        }
    }

    fclose(fp);
    return 1;
}

/* ------------------- IMPORTA ARQUIVO ------------------- */
int hsh_importa_arquivo(Aluno **tab, char *filename, void *(*ler_linha_csv)(char *))
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
        return 0;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp))
    {
        Aluno *novo = (Aluno *)ler_linha_csv(buffer);
        if (novo != NULL)
        {
            int h = hash(novo->matricula);
            novo->prox = tab[h];
            tab[h] = novo;
        }
    }

    fclose(fp);
    return 1;
}
