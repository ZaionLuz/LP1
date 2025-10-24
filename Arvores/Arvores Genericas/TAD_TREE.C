#include "TAD_TreeGen.h"
#include <stdlib.h>
#include <stdio.h>

/*IS IT EMPTY?*/
int tree_empty(Node *root)
{
    return root == NULL;
}

/*CREATE AN EMPTY TREE*/
Node *tree_create_empty()
{
    return NULL;
}

/*CREATE A NODE*/
Node *tree_create_node(void *info, Node *lst, Node *rst)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node)
        return NULL;
    node->info = info;
    node->left = lst;
    node->right = rst;
    return node;
}

/*INSERT A NODE*/
Node *tree_insert_node(Node *root, Node *new_node, int(compare)(void *, void *))
{
    if (!root)
        return new_node;
    if (compare(new_node->info, root->info) < 0)
        root->left = tree_insert_node(root->left, new_node, compare);
    else
        root->right = tree_insert_node(root->right, new_node, compare);
    return root;
}

/*FREE A TREE*/
void tree_free(Node *root)
{
    if (!root)
        return;
    tree_free(root->left);
    tree_free(root->right);
    free(root->info);
    free(root);
}

/*PERFORM OPERATION IN A TREE*/
void tree_map(Node *root, void(operation)(void *))
{
    if (!root)
        return;
    tree_map(root->left, operation);
    operation(root->info);
    tree_map(root->right, operation);
}

/*COPY A NODE*/
Node *tree_copy_node(Node *original)
{
    if (!original)
        return NULL;
    Node *copy = (Node *)malloc(sizeof(Node));
    if (!copy)
        return NULL;
    copy->info = original->info;
    copy->left = original->left;
    copy->right = original->right;
    return copy;
}

/*FILTER ELEMENTS IN THE TREE INTO A LIST*/
Listagen *tree_filter_as_list(Node *root, int(condition)(void *), void *(copy_info)(void *))
{
    if (!root)
        return NULL;
    Listagen *list = NULL;
    if (condition(root->info))
        list = listagen_insere(list, copy_info(root->info));
    Listagen *left = tree_filter_as_list(root->left, condition, copy_info);
    Listagen *right = tree_filter_as_list(root->right, condition, copy_info);
    list = listagen_concat(listagen_concat(left, list), right);
    return list;
}

/*FILTER ELEMENTS IN THE TREE CREATING A NEW TREE*/
Node *tree_filter(Node *root, int(condition)(void *), void *(copy_info)(void *), int(compare)(void *, void *))
{
    if (!root)
        return NULL;
    Node *filtered = NULL;
    if (condition(root->info))
    {
        Node *new_node = tree_create_node(copy_info(root->info), NULL, NULL);
        filtered = tree_insert_node(filtered, new_node, compare);
    }
    Node *left = tree_filter(root->left, condition, copy_info, compare);
    Node *right = tree_filter(root->right, condition, copy_info, compare);

    if (left)
        filtered = tree_insert_node(filtered, left, compare);
    if (right)
        filtered = tree_insert_node(filtered, right, compare);
    return filtered;
}

/*VERIFIES THE HEIGHT OF THE NODE*/
int tree_get_height(Node *node)
{
    if (!node)
        return 0;
    int lh = tree_get_height(node->left);
    int rh = tree_get_height(node->right);
    return (lh > rh ? lh : rh) + 1;
}

/*ROTATES THE TREE TO THE RIGHT*/
Node *rotate_right(Node *root)
{
    if (!root || !root->left)
        return root;
    Node *new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;
    return new_root;
}

/*ROTATES THE TREE TO THE LEFT*/
Node *rotate_left(Node *root)
{
    if (!root || !root->right)
        return root;
    Node *new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    return new_root;
}

/*INSERTS A NEW NODE WHILE BALANCING THE TREE*/
Node *tree_insert_balanced(Node *root, Node *new_node, int(compare)(void *, void *))
{
    if (!root)
        return new_node;

    if (compare(new_node->info, root->info) < 0)
        root->left = tree_insert_balanced(root->left, new_node, compare);
    else
        root->right = tree_insert_balanced(root->right, new_node, compare);

    int balance = tree_get_height(root->left) - tree_get_height(root->right);

    if (balance > 1 && compare(new_node->info, root->left->info) < 0)
        return rotate_right(root);
    if (balance < -1 && compare(new_node->info, root->right->info) > 0)
        return rotate_left(root);
    if (balance > 1 && compare(new_node->info, root->left->info) > 0)
    {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    if (balance < -1 && compare(new_node->info, root->right->info) < 0)
    {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    return root;
}

/*TREE SEARCH*/
Node *tree_search(Node *root, int(condition)(void *))
{
    if (!root)
        return NULL;
    if (condition(root->info))
        return root;
    Node *found = tree_search(root->left, condition);
    if (found)
        return found;
    return tree_search(root->right, condition);
}

/*WRITE IN ORDER*/
void write_inorder(Node *new_node, FILE *fp, char *(*create_line)(void *))
{
    if (!new_node)
        return;
    write_inorder(new_node->left, fp, create_line);
    char *line = create_line(new_node->info);
    if (line)
    {
        fprintf(fp, "%s\n", line);
        free(line);
    }
    write_inorder(new_node->right, fp, create_line);
}

/*TREE TO FILE*/
void tree_to_file(Node *root, char *file_name, char *(create_line)(void *))
{
    if (!root || !file_name)
        return;
    FILE *fp = fopen(file_name, "w");
    if (!fp)
        return;
    write_inorder(root, fp, create_line);
    fclose(fp);
}

/*LOAD A BINARY TREE FROM A TEXT FILE*/
Node *tree_load_from_file(char *file_name, void *(read_line)(char *), int(compare)(void *, void *))
{
    if (!file_name || !read_line || !compare)
        return NULL;
    FILE *fp = fopen(file_name, "r");
    if (!fp)
        return NULL;

    Node *root = NULL;
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), fp))
    {
        void *data = read_line(buffer);
        Node *node = tree_create_node(data, NULL, NULL);
        root = tree_insert_balanced(root, node, compare);
    }
    fclose(fp);
    return root;
}
