#include <stdio.h>
#include <stdlib.h>

void create();
void rev();
void display();

int count1 = 0;

struct node {
    int data;
    struct node *next;
    struct node *prev;
} *head = NULL, *tail = NULL, *newnode, *temp;

int main() {
    create();
    
    display();
    rev();
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
void rev()
{
    struct node *current,*nextnode;
    current=head;
    while(current!=NULL)
    {
        nextnode=current->next;
        current->next=current->prev;
        current->prev=nextnode;
        current=nextnode;
    }
    temp=head;
    head=tail;
    tail=temp;
}