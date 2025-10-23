// prova_completa_treegen.c
// ======================================================
// Arquivo contendo todas as funções de:
// - Listas genéricas encadeadas
// - Árvores binárias (TAD_Arvore)
// - Árvores genéricas (TAD_TreeGen)
// - Manipulação básica de arquivos
// Explicações detalhadas em comentários.
// ======================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////
// ================== //
//    LISTAS GENÉRICAS //
// ================== //
///////////////////////

typedef struct Listagen
{
    void *info;            // Ponteiro para informação genérica
    struct Listagen *prox; // Próximo elemento da lista
} Listagen;

// Cria uma lista vazia
Listagen *lstgen_cria() { return NULL; }

// Verifica se a lista está vazia
int lstgen_vazia(Listagen *l) { return l == NULL; }

// Insere elemento no início
Listagen *lstgen_insere(Listagen *l, void *elemento)
{
    Listagen *novo = (Listagen *)malloc(sizeof(Listagen));
    if (!novo)
    {
        printf("Memória insuficiente!\n");
        exit(1);
    }
    novo->info = elemento;
    novo->prox = l;
    return novo;
}

// Percorre lista aplicando função processa
void lstgen_percorre(Listagen *l, void (*processa)(void *))
{
    while (l != NULL)
    {
        processa(l->info);
        l = l->prox;
    }
}

// Busca elemento usando função compara
void *lstgen_busca(Listagen *l, int (*compara)(void *, void *), void *dado)
{
    while (l != NULL)
    {
        if (compara(l->info, dado))
            return l->info;
        l = l->prox;
    }
    return NULL;
}

// Retira elemento da lista usando função compara
Listagen *lstgen_retira(Listagen *l, int (*compara)(void *, void *), void *dado)
{
    Listagen *p = l, *ant = NULL;
    while (p != NULL)
    {
        if (compara(p->info, dado))
        {
            if (ant == NULL)
            {
                Listagen *temp = p->prox;
                free(p);
                return temp;
            }
            else
            {
                ant->prox = p->prox;
                free(p);
                return l;
            }
        }
        ant = p;
        p = p->prox;
    }
    return l;
}

// Libera toda a lista e os elementos
void lstgen_libera(Listagen *l)
{
    while (l != NULL)
    {
        free(l->info);
        Listagen *temp = l->prox;
        free(l);
        l = temp;
    }
}

// Filtra elementos usando critério
Listagen *lstgen_filtra(Listagen *l, int (*criterio)(void *))
{
    Listagen *nova = lstgen_cria();
    for (Listagen *p = l; p != NULL; p = p->prox)
        if (criterio(p->info))
            nova = lstgen_insere(nova, p->info);
    return nova;
}

// Duplica lista usando função de cópia
Listagen *lstgen_duplica(Listagen *l, void *(*duplica)(void *))
{
    Listagen *nova = lstgen_cria();
    for (Listagen *p = l; p != NULL; p = p->prox)
        nova = lstgen_insere(nova, duplica(p->info));
    return nova;
}

// Ordena lista usando selection sort e função compara
Listagen *lstgen_ordena(Listagen *l, int (*compara)(void *, void *))
{
    for (Listagen *p = l; p != NULL; p = p->prox)
        for (Listagen *q = p->prox; q != NULL; q = q->prox)
            if (compara(p->info, q->info))
            {
                void *aux = q->info;
                q->info = p->info;
                p->info = aux;
            }
    return l;
}

// Grava lista em CSV usando função cria_linha_csv
int lstgen_grava_csv(Listagen *l, char *nome_arquivo_csv, char *(*cria_linha_csv)(void *))
{
    FILE *fp = fopen(nome_arquivo_csv, "wt");
    if (!fp)
    {
        printf("Erro ao abrir arquivo %s\n", nome_arquivo_csv);
        return 0;
    }
    for (Listagen *p = l; p != NULL; p = p->prox)
    {
        char *linha = cria_linha_csv(p->info);
        fputs(linha, fp);
        free(linha);
    }
    fclose(fp);
    return 1;
}

// Carrega lista de CSV usando função cria_elemento
Listagen *lstgen_carrega_csv(char *nome_arquivo_csv, void *(*cria_elemento)(char *))
{
    FILE *fp = fopen(nome_arquivo_csv, "rt");
    if (!fp)
    {
        printf("Erro ao abrir arquivo %s\n", nome_arquivo_csv);
        return NULL;
    }
    Listagen *l = lstgen_cria();
    char linha[121];
    while (fgets(linha, 121, fp) != NULL)
    {
        void *elem = cria_elemento(linha);
        if (!elem)
            continue;
        l = lstgen_insere(l, elem);
    }
    fclose(fp);
    return l;
}

///////////////////////
// ================== //
//      ARVORE        //
// ================== //
///////////////////////

typedef struct Arv
{
    char info;
    struct Arv *sae;
    struct Arv *sad;
} Arv;

// Cria árvore vazia
Arv *arv_criavazia(void) { return NULL; }

// Cria nó com info e subárvores
Arv *arv_cria(char c, Arv *e, Arv *d)
{
    Arv *nova = (Arv *)malloc(sizeof(Arv));
    if (!nova)
    {
        printf("Memória insuficiente\n");
        exit(1);
    }
    nova->info = c;
    nova->sae = e;
    nova->sad = d;
    return nova;
}

// Libera árvore recursivamente
Arv *arv_libera(Arv *a)
{
    if (a != NULL)
    {
        arv_libera(a->sae);
        arv_libera(a->sad);
        free(a);
    }
    return NULL;
}

// Verifica se árvore está vazia
int arv_vazia(Arv *a) { return a == NULL; }

// Verifica se info pertence à árvore
int arv_pertence(Arv *a, char c)
{
    if (arv_vazia(a))
        return 0;
    return a->info == c || arv_pertence(a->sae, c) || arv_pertence(a->sad, c);
}

// Imprime árvore (pré-ordem)
void arv_imprime(Arv *a)
{
    if (arv_vazia(a))
        return;
    printf("info: %c\n", a->info);
    arv_imprime(a->sae);
    arv_imprime(a->sad);
}

// Altura da árvore
int arv_altura(Arv *a)
{
    if (arv_vazia(a))
        return -1;
    int esq = arv_altura(a->sae), dir = arv_altura(a->sad);
    return 1 + (esq > dir ? esq : dir);
}

// Conta folhas
int arv_qtd_folhas(Arv *a)
{
    if (arv_vazia(a))
        return 0;
    int total = arv_qtd_folhas(a->sae) + arv_qtd_folhas(a->sad);
    return total == 0 ? 1 : total;
}

// Conta letras minúsculas
int arv_qtd_letra_min(Arv *a)
{
    if (arv_vazia(a))
        return 0;
    int total = arv_qtd_letra_min(a->sae) + arv_qtd_letra_min(a->sad);
    if (a->info >= 'a' && a->info <= 'z')
        total++;
    return total;
}

///////////////////////
// ================== //
//     TREEGEN        //
// ================== //
///////////////////////

typedef struct Node
{
    void *info;
    struct Node *left;
    struct Node *right;
} Node;

// Cria árvore vazia
Node *tree_create_empty() { return NULL; }

// Cria nó genérico
Node *tree_create_node(void *info, Node *lst, Node *rst)
{
    Node *novo = (Node *)malloc(sizeof(Node));
    if (!novo)
    {
        printf("Erro de memória\n");
        exit(1);
    }
    novo->info = info;
    novo->left = lst;
    novo->right = rst;
    return novo;
}

// Verifica se árvore genérica está vazia
int tree_empty(Node *root) { return root == NULL; }

// Libera árvore genérica recursivamente
void tree_free(Node *root)
{
    if (!root)
        return;
    tree_free(root->left);
    tree_free(root->right);
    free(root->info);
    free(root);
}

// Executa operação em todos os elementos da árvore
void tree_map(Node *root, void(operation)(void *))
{
    if (!root)
        return;
    operation(root->info);
    tree_map(root->left, operation);
    tree_map(root->right, operation);
}

// Copia nó
Node *tree_copy_node(Node *original)
{
    if (!original)
        return NULL;
    void *novo_info = malloc(sizeof(original->info));
    memcpy(novo_info, original->info, sizeof(original->info));
    Node *novo = tree_create_node(novo_info, tree_copy_node(original->left), tree_copy_node(original->right));
    return novo;
}

// Busca genérica (comparação retorna 1 se achar)
void *tree_search(Node *root, int (*compare)(void *, void *), void *value)
{
    if (!root)
        return NULL;
    if (compare(root->info, value))
        return root->info;
    void *res = tree_search(root->left, compare, value);
    if (res)
        return res;
    return tree_search(root->right, compare, value);
}

// Filtra árvore criando nova árvore apenas com elementos que passam no critério
Node *tree_filter(Node *root, int (*criteria)(void *))
{
    if (!root)
        return NULL;
    Node *left = tree_filter(root->left, criteria);
    Node *right = tree_filter(root->right, criteria);
    if (criteria(root->info))
        return tree_create_node(root->info, left, right);
    // Se não passa, funde subárvores
    if (left && !right)
        return left;
    if (!left && right)
        return right;
    if (left && right)
    {
        Node *temp = left;
        while (temp->right)
            temp = temp->right;
        temp->right = right;
        return left;
    }
    return NULL;
}

// Altura árvore genérica
int tree_height(Node *root)
{
    if (!root)
        return -1;
    int l = tree_height(root->left);
    int r = tree_height(root->right);
    return 1 + (l > r ? l : r);
}

// Conta nós
int tree_count(Node *root)
{
    if (!root)
        return 0;
    return 1 + tree_count(root->left) + tree_count(root->right);
}

// In-Order Print genérico usando função print
void tree_print_inorder(Node *root, void (*print_elem)(void *))
{
    if (!root)
        return;
    tree_print_inorder(root->left, print_elem);
    print_elem(root->info);
    tree_print_inorder(root->right, print_elem);
}

///////////////////////
// ================== //
// ARQUIVOS SIMPLES   //
// ================== //
///////////////////////

void save_text_file(char *filename, char *content)
{
    FILE *fp = fopen(filename, "wt");
    if (!fp)
    {
        printf("Erro ao abrir %s\n", filename);
        return;
    }
    fprintf(fp, "%s", content);
    fclose(fp);
}

char *read_text_file(char *filename)
{
    FILE *fp = fopen(filename, "rt");
    if (!fp)
    {
        printf("Erro ao abrir %s\n", filename);
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    char *buf = malloc(size + 1);
    fread(buf, 1, size, fp);
    buf[size] = '\0';
    fclose(fp);
    return buf;
}
