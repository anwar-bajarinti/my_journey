#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

// Function to create binary tree
struct node* create() {
    int x;
    struct node *newnode;

    printf("\nEnter data (-1 for no node): ");
    scanf("%d", &x);

    if (x == -1)
        return NULL;

    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = x;

    printf("Enter left child of %d", x);
    newnode->left = create();

    printf("Enter right child of %d", x);
    newnode->right = create();

    return newnode;
}

// Preorder traversal (optional)
void preorder(struct node *root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

int main() {
    struct node *root = NULL;
    root = create();

    printf("\nPreorder traversal: ");
    preorder(root);

    return 0;
}
