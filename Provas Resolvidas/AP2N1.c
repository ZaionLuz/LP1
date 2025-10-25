/*
Instituto Federal do Ceará – Campus Aracati
Disciplina: Linguagem de Programação I
Professor: [Raimundo Valter]
Aluno: Zaion Araújo
Avaliação: AP2 - Árvores Genéricas e Arquivos
Data: 2025.1

Descrição:
Implementação de três funções para manipulação de árvores binárias genéricas:
1) Aplicar uma operação a todos os elementos da árvore.
2) Buscar um nó que satisfaça uma condição.
3) Liberar toda a memória da árvore.
*/

#include <stdio.h>
#include <stdlib.h>

/* Estrutura genérica que representa um nó de uma árvore binária */
typedef struct node
{
    void *info;       // Ponteiro genérico para os dados armazenados
    struct node *lst; // Ponteiro para o filho à esquerda
    struct node *rst; // Ponteiro para o filho à direita
} Node;

/* ============================================================
   1) tree_map
   Aplica uma operação (função callback) a todos os elementos da árvore.

   Protótipo:
       void tree_map(Node* root, void (*operation)(void*));

   Parâmetros:
       - root: ponteiro para o nó raiz da árvore
       - operation: função callback que será aplicada a cada elemento

   Estratégia:
       Percorre a árvore em ordem (in-order traversal),
       aplicando a operação a cada nó.
   ============================================================ */
void tree_map(Node *root, void (*operation)(void *))
{
    if (!root)
        return;                     // Caso base: árvore vazia
    tree_map(root->lst, operation); // Percorre subárvore esquerda
    operation(root->info);          // Aplica operação no nó atual
    tree_map(root->rst, operation); // Percorre subárvore direita
}

/* ============================================================
   2) tree_search
   Busca o primeiro nó cujo valor satisfaça uma condição definida
   por uma função callback.

   Protótipo:
       Node* tree_search(Node* root, int (*condition)(void*));

   Parâmetros:
       - root: ponteiro para a raiz da árvore
       - condition: função callback que retorna 1 (verdadeiro)
         se o nó atender à condição desejada

   Estratégia:
       Percorre a árvore em ordem e retorna o primeiro nó que
       satisfaz a condição.
   ============================================================ */
Node *tree_search(Node *root, int (*condition)(void *))
{
    if (!root)
        return NULL; // Caso base

    // Busca na subárvore esquerda
    Node *found = tree_search(root->lst, condition);
    if (found)
        return found;

    // Verifica o nó atual
    if (condition(root->info))
        return root;

    // Busca na subárvore direita
    return tree_search(root->rst, condition);
}

/* ============================================================
   3) tree_free
   Libera toda a memória ocupada pela árvore binária,
   retornando uma árvore vazia (NULL).

   Protótipo:
       Node* tree_free(Node* root);

   Parâmetros:
       - root: ponteiro para a raiz da árvore

   Estratégia:
       Percorre a árvore em pós-ordem (post-order traversal)
       para garantir que os filhos sejam liberados antes do pai.
   ============================================================ */
Node *tree_free(Node *root)
{
    if (!root)
        return NULL; // Caso base

    // Libera subárvores primeiro
    tree_free(root->lst);
    tree_free(root->rst);

    // Libera o dado (se necessário)
    free(root->info);

    // Libera o próprio nó
    free(root);

    return NULL; // Retorna árvore vazia
}
