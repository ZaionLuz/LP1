#include "TAD_TabelaHash.h"
#include <stdlib.h>
#include <stdio.h>

static int hash(int mat)
{
    return (mat % N);
}

Aluno *hsh_busca(Aluno **tab, int mat)
{
    int h = hash(mat);

    while ((tab[h] != NULL))
    {
        if (tab[h]->matricula == mat)
            return tab[h];
        h = (h + 1) % N;
    }
    return NULL;
}

Aluno *hsh_insere(Aluno **tab, int mat, char *nome, char *tel, char *email)
{
    int h = hash(mat);
    while (tab[h] != NULL)
    {
        if (tab[h]->matricula == mat)
            break;
        h = (h + 1) % N;
    }

    if (tab[h] == NULL)
    {
        tab[h] = (Aluno *)malloc(sizeof(Aluno));
        tab[h]->matricula = mat;
    }

    strcpy(tab[h]->nome, nome);
    strcpy(tab[h]->email, email);
    strcpy(tab[h]->telefone, tel);

    return tab[h];
}

int hsh_remove(Aluno **tab, int mat)
{
    int h = hash(mat);

    while (tab[h] != NULL)
    {
        if (tab[h]->matricula == mat)
        {
            free(tab[h]);
            tab[h] = NULL;
            return 1; // removido com sucesso
        }
        h = (h + 1) % N;
    }

    return 0; // não encontrado
}

int hsh_atualiza(Aluno **tab, int mat, char *nome, char *tel, char *email)
{
    int h = hash(mat);

    while (tab[h] != NULL)
    {
        if (tab[h]->matricula == mat)
        {
            // Atualiza os campos do aluno existente
            strcpy(tab[h]->nome, nome);
            strcpy(tab[h]->telefone, tel);
            strcpy(tab[h]->email, email);
            return 1; // sucesso
        }
        h = (h + 1) % N;
    }

    return 0; // matrícula não encontrada
}

void hsh_lista_todos(Aluno **tab)
{
    for (int i = 0; i < N; i++)
    {
        if (tab[i] != NULL)
        {
            printf("Posição %d:\n", i);
            printf("  Matrícula: %d\n", tab[i]->matricula);
            printf("  Nome: %s\n", tab[i]->nome);
            printf("  Telefone: %s\n", tab[i]->telefone);
            printf("  Email: %s\n", tab[i]->email);
            printf("-----------------------------\n");
        }
    }
}

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

Aluno *hsh_busca_por_nome(Aluno **tab, char *nome)
{
    for (int i = 0; i < N; i++)
    {
        if (tab[i] != NULL && strcmp(tab[i]->nome, nome) == 0)
        {
            return tab[i]; // achou o aluno
        }
    }

    return NULL; // não encontrado
}

void hsh_limpa_tabela(Aluno **tab)
{
    if (tab == NULL)
        return;

    for (int i = 0; i < N; i++)
    {
        Aluno *atual = tab[i];
        while (atual != NULL)
        {
            Aluno *tmp = atual->prox; // guarda o próximo nó
            free(atual);              // libera o nó atual
            atual = tmp;              // vai para o próximo
        }
        tab[i] = NULL; // zera a posição da tabela
    }

    free(tab); // libera o vetor de ponteiros da tabela
    tab = NULL;
}

float hsh_fator_carga(Aluno **tab)
{
    int total = 0;

    for (int i = 0; i < N; i++)
    {
        Aluno *atual = tab[i];
        while (atual != NULL)
        {
            total++; // conta cada nó da lista
            atual = atual->prox;
        }
    }

    return (float)total / N; // fator de carga
}

int hsh_vazia(Aluno **tab)
{
    if (tab == NULL)
        return 1; // tabela não existe, considera vazia

    for (int i = 0; i < N; i++)
    {
        Aluno *atual = tab[i];
        if (atual != NULL) // encontrou pelo menos um aluno
            return 0;
    }

    return 1; // nenhuma posição tem aluno
}

int hsh_exporta_arquivo(Aluno **tab, char *filename, char *(*escrever_linha_csv)(void *))
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
        return 0; // falha ao abrir arquivo

    for (int i = 0; i < N; i++)
    {
        Aluno *atual = tab[i];
        while (atual != NULL)
        {
            char *linha = escrever_linha_csv(atual); // converte Aluno em string CSV
            fprintf(fp, "%s\n", linha);
            free(linha); // libera a string se foi alocada dinamicamente
            atual = atual->prox;
        }
    }

    fclose(fp);
    return 1; // sucesso
}

int hsh_importa_arquivo(Aluno **tab, char *filename, void *(*ler_linha_csv)(char *))
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
        return 0; // falha ao abrir arquivo

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp))
    {
        Aluno *novo = (Aluno *)ler_linha_csv(buffer); // converte linha CSV em struct Aluno*
        if (novo != NULL)
        {
            // insere no hash (precisa de função de inserção)
            int h = hash(novo->matricula);
            novo->prox = tab[h]; // insere no início da lista
            tab[h] = novo;
        }
    }

    fclose(fp);
    return 1; // sucesso
}
