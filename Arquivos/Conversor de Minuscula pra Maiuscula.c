#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    char arquivo_entrada[121];
    char arquivo_saida[121];
    char c;

    printf("Digite o nome do arquivo de entrada: "); //Digita o nome do arquivo ja existente
    scanf("%120s", arquivo_entrada);

    printf("Digite o nome do arquivo de saida: ");  //Digita o nome do arquivo q quer criar
    scanf("%120s", arquivo_saida);

    FILE *e = fopen(arquivo_entrada, "rt"); //Abre  o arquivo de entrada para leitura de texto (rt=read text)
    if (!e)
    {
        printf("Problemas ao abrir o arquivo: %s\n", arquivo_entrada);
        exit(1);
    }

    FILE *s = fopen(arquivo_saida, "wt"); //Abre o arquivo de saida para escrita de texto (wt=write text)
    if (!s)
    {
        printf("Problema ao abrir o arquivo: %s\n", arquivo_saida);
        exit(1);
    }

    while ((c = fgetc(e)) != EOF) //Atribuimos a variavel de e para c enquanto o arquivo n chegar no fim (EOF=End of file)
    {
        fputc(toupper(c), s);
    }

    fclose(e);
    fclose(s);

    return 0;
}
