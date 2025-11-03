#include "TAD_TabelaHash.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

// Funções auxiliares para export/import CSV
char *escrever_linha_csv(void *ptr)
{
    Aluno *a = (Aluno *)ptr;
    char *linha = malloc(200);
    sprintf(linha, "%d,%s,%s,%s", a->matricula, a->nome, a->telefone, a->email);
    return linha;
}

void *ler_linha_csv(char *linha)
{
    Aluno *a = malloc(sizeof(Aluno));
    char *token = strtok(linha, ",");
    if (!token)
        return NULL;
    a->matricula = atoi(token);

    token = strtok(NULL, ",");
    if (token)
        strcpy(a->nome, token);

    token = strtok(NULL, ",");
    if (token)
        strcpy(a->telefone, token);

    token = strtok(NULL, ",\n");
    if (token)
        strcpy(a->email, token);

    a->prox = NULL;
    return a;
}

int main()
{
    // Cria a tabela
    Aluno **tab = malloc(N * sizeof(Aluno *));
    for (int i = 0; i < N; i++)
        tab[i] = NULL;

    // Inserir alunos
    hsh_insere(tab, 101, "Joao", "123456789", "joao@email.com");
    hsh_insere(tab, 102, "Maria", "987654321", "maria@email.com");
    hsh_insere(tab, 103, "Pedro", "111222333", "pedro@email.com");

    printf("Lista de alunos:\n");
    hsh_lista_todos(tab);

    // Buscar por matrícula
    Aluno *a = hsh_busca(tab, 102);
    if (a)
        printf("\nAluno encontrado: %s\n", a->nome);

    // Atualizar aluno
    hsh_atualiza(tab, 103, "Pedro Silva", "444555666", "pedro.silva@email.com");

    // Buscar por nome
    a = hsh_busca_por_nome(tab, "Maria");
    if (a)
        printf("\nBusca por nome: %s - %s\n", a->nome, a->email);

    // Contar alunos
    printf("\nNúmero de alunos: %d\n", hsh_conta_alunos(tab));

    // Fator de carga
    printf("Fator de carga: %.2f\n", hsh_fator_carga(tab));

    // Exportar para arquivo
    hsh_exporta_arquivo(tab, "alunos.csv", escrever_linha_csv);
    printf("\nDados exportados para alunos.csv\n");

    // Remover um aluno
    hsh_remove(tab, 101);
    printf("\nApós remover matrícula 101:\n");
    hsh_lista_todos(tab);

    // Limpar tabela
    hsh_limpa_tabela(tab);
    printf("\nTabela limpa!\n");

    return 0;
}
