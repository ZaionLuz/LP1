#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Provaveis Questões sobre Tabela Hash a cair na Prova

typedef struct aluno
{
    int matricula;
    char nome[81];
    char telefone[13];
    char email[51];
    struct aluno *prox;
} Aluno;

// 1. Calcula o hash de uma chave primária
static int hash(int mat)
{
    return (mat % N);
}

// 2. Busca um aluno por matrícula e retorna o ponteiro para a estrutura, caso exista.
Aluno *hsh_busca(Aluno **tab, int mat)
{
    int h = hash(tab);
    Aluno *atual = tab[h];

    while (atual != NULL)
    {
        if (atual->matricula == mat)
            return atual;
        atual = atual->prox;
    }

    return NULL;
}

// 3. Insere um aluno na tabela de dispersão, caso a matrícula já exista, atualizar os dados do aluno.
Aluno *hsh_insere(Aluno **tab, int mat, char *nome, char *tel, char *email)
{
    int h = hash(tab);
    Aluno *atual = tab[h];

    while (atual != NULL)
    {
        if (atual->matricula == mat)
        {
            strcpy(atual->nome, nome);
            strcpy(atual->telefone, tel);
            strcpy(atual->email, email);
            return atual;
        }
        atual = atual->prox;
    }
    Aluno *novo = (Aluno *)malloc(sizeof(Aluno));

    if (!novo)
        return 0;

    novo->matricula = mat;
    strcpy(novo->nome, nome);
    strcpy(novo->telefone, tel);
    strcpy(novo->email, email);

    novo->prox = tab[h];
    tab[h] = novo;

    return novo;
}

// 4. Remover aluno pela matrícula
int hsh_remove(Aluno **tab, int mat)
{
    int h = hash(tab);
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
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return 0;
}

// 5. Atualizar dados de um aluno
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

// 6. Listar todos os alunos
void hsh_lista_todos(Aluno **tab)
{
    for (int i = 0; i < N; i++)
    {
        Aluno *atual = tab[i];
        if (atual != NULL)
        {
            printf("Posicao: %d\n", i + 1);

            while (atual != NULL)
            {
                printf("Matricula: %d\n", atual->matricula);
                printf("Nome: %s\n", atual->nome);
                printf("Telefone: %s\n", atual->telefone);
                printf("Email: %s\n", atual->email);
            }
            atual = atual->prox;
        }
    }
}

// 7. Contar número de alunos na tabela
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

// 8. Buscar aluno por nome (busca parcial)
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

// 9. Limpar/liberar toda a tabela
void hsh_limpa_tabela(Aluno **tab)
{
    if (tab == NULL)
        return;

    for (int i = 0; i < N; i++)
    {
        Aluno *atual = tab[i];
        while (atual != NULL)
        {
            Aluno *guardador = atual->prox;
            free(atual);
            atual = guardador;
        }
        tab[i] = NULL;
    }
    free(tab);
}

// 10. Calcular fator de carga da tabela
float hsh_fator_carga(Aluno **tab)
{
    int total = hsh_conta_alunos(tab);
    return (float)total / N;
}

// 11. Verificar se tabela está vazia
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
