/*
Caça-palavras

Descrição
Implemente um programa que simule um jogo de "caça-palavras". O programa deve representar uma matriz de caracteres de dimensão
m×n e buscar a ocorrência de palavras nessa matriz. As palavras podem estar nas seguintes direções:
Horizontal (esquerda para direita ou direita para esquerda)
Vertical (cima para baixo ou baixo para cima)
Diagonal (nas quatro direções possíveis)

Funcionamento
O programa deve ler a dimensão da matriz e seus caracteres de um arquivo
O formato do arquivo é:
Primeira linha: dois inteiros
m e n (dimensões da matriz)
Linhas seguintes:
m linhas com n caracteres cada

Exemplo de arquivo:
text
5 5
SARXE
LIVRT
YAIXA
RADIO
XZALA

Em seguida, o programa deve ler uma palavra digitada pelo usuário
Realizar a busca na matriz em todas as direções possíveis
Imprimir uma mensagem indicando se a palavra foi encontrada ou não
Se encontrada, mostrar as posições
(i,j) ocupadas pelos caracteres da palavra

Saída Esperada
Se a palavra for encontrada: indicar todas as posições onde ocorre
Se não for encontrada: informar que a palavra não está na matriz*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

int main()
{
    FILE *fp = fopen("caca_palavras.txt", "r");
    if (!fp)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    int m, n;
    fscanf(fp, "%d %d", &m, &n);
    if (m > MAX || n > MAX)
    {
        printf("Dimensões excedem o tamanho máximo.\n");
        return 1;
    }

    char matriz[MAX][MAX + 1]; // +1 para o '\0'
    fscanf(fp, "\n");          // consome o \n depois do números
    for (int i = 0; i < m; i++)
    {
        fgets(matriz[i], MAX + 1, fp); // lê linha inteira
        if (matriz[i][strlen(matriz[i]) - 1] == '\n')
            matriz[i][strlen(matriz[i]) - 1] = '\0'; // remove '\n'
    }
    fclose(fp);

    printf("Matriz lida:\n");
    for (int i = 0; i < m; i++)
        printf("%s\n", matriz[i]);

    char palavra[50];
    printf("Digite a palavra a buscar: ");
    scanf("%49s", palavra);
    int tam = strlen(palavra);

    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int found = 0;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matriz[i][j] == palavra[0])
            {
                for (int dir = 0; dir < 8; dir++)
                {
                    int k, ni = i, nj = j;
                    for (k = 0; k < tam; k++)
                    {
                        if (ni < 0 || ni >= m || nj < 0 || nj >= n)
                            break;
                        if (matriz[ni][nj] != palavra[k])
                            break;
                        ni += dx[dir];
                        nj += dy[dir];
                    }
                    if (k == tam)
                    {
                        found = 1;
                        printf("Palavra encontrada nas posições:\n");
                        ni = i;
                        nj = j;
                        for (k = 0; k < tam; k++)
                        {
                            printf("(%d,%d) ", ni, nj);
                            ni += dx[dir];
                            nj += dy[dir];
                        }
                        printf("\n");
                        goto fim; // encontra a primeira ocorrência
                    }
                }
            }
        }
    }

fim:
    if (!found)
        printf("Palavra não encontrada na matriz.\n");

    return 0;
}
