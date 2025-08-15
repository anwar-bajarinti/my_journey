#include <stdio.h>
#include <stdlib.h>

void create();
void insert_beginning();
void insert_end();
void insert_pos();
void count();
void display();

int count1 = 0;

struct node {
    int data;
    struct node *next;
    struct node *prev;
} *head = NULL, *tail = NULL, *newnode, *temp;

int main() {
    create();
    insert_beginning();
    insert_end();
    count();
    insert_pos();
    display();
    return 0;
}

// Create Doubly Linked List
void create() {
    printf("\nEntered into create function\n");
    int choice = 1;

    while (choice) {
        newnode = (struct node*)malloc(sizeof(struct node));
        newnode->next = NULL;
        newnode->prev = NULL;

        printf("Enter data: ");
        scanf("%d", &newnode->data);

        if (head == NULL) {
            head = tail = newnode;
        } else {
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }

        count1++; // update count during creation

        printf("Do you want to add another node? (1 for yes / 0 for no): ");
        scanf("%d", &choice);
    }
}

// Display List
void display() {
    temp = head;
    printf("\nDoubly Linked List: ");
    while (temp != NULL) {
        printf("<-- %d -->", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Insert at Beginning
void insert_beginning() {
    printf("\nEntered into insert at beginning\n");

    newnode = (struct node*)malloc(sizeof(struct node));
    printf("Enter data: ");
    scanf("%d", &newnode->data);
    newnode->prev = NULL;
    newnode->next = head;

    if (head != NULL) {
        head->prev = newnode;
    } else {
        tail = newnode;  // If list was empty
    }

    head = newnode;
    count1++;
}

// Insert at End
void insert_end() {
    printf("\nEntered into insert at end\n");

    newnode = (struct node*)malloc(sizeof(struct node));
    printf("Enter data: ");
    scanf("%d", &newnode->data);
    newnode->next = NULL;
    newnode->prev = tail;

    if (tail != NULL) {
        tail->next = newnode;
    } else {
        head = newnode;  // If list was empty
    }

    tail = newnode;
    count1++;
}

// Count nodes
void count() {
    printf("\nTotal number of nodes: %d\n", count1);
}

// Insert at Specific Position
void insert_pos() {
    int pos, i = 1;
    printf("Enter the position to insert: ");
    scanf("%d", &pos);

    if (pos < 1 || pos > count1 + 1) {
        printf("Invalid position!\n");
        return;
    }

    if (pos == 1) {
        insert_beginning();
    } else if (pos == count1 + 1) {
        insert_end();
    } else {
        newnode = (struct node*)malloc(sizeof(struct node));
        printf("Enter data: ");
        scanf("%d", &newnode->data);

        temp = head;
        while (i < pos - 1) {
            temp = temp->next;
            i++;
        }

        newnode->next = temp->next;
        newnode->prev = temp;

        temp->next->prev = newnode;
        temp->next = newnode;

        count1++;
    }
}
