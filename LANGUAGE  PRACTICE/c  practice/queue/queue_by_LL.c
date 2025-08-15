#include<stdio.h>
#include<stdlib.h>
void enqueue(int);
void dequeue();
void display();
void peek();
struct node
{
    int data;
    struct node *next;
};
struct node *rear=NULL;
struct node *front=NULL;
void main()
{
    enqueue(10);
    enqueue(20);
    display();
    dequeue();
    peek();
    dequeue();
    dequeue();
}
void enqueue(int x)
{
    struct node *newnode;
    newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=x;
    newnode->next=NULL;
    if(rear==NULL&&front==NULL)
    {
        rear=front=newnode;
    }
    else{
        rear->next=newnode;
        rear=newnode;
    }
}
void dequeue()
{
    if(rear==NULL&&front==NULL)
    {
        printf(" \nqueue is empty");
    }
    else
    {
        struct node *temp;
        temp=front;
        front=front->next;
        if(front == NULL) // If the queue becomes empty after dequeuing
        {
            rear = NULL;
            printf(" \nqueue is empty");
        }
        free(temp);
    }
}
void display()
{
    if(rear==NULL&&front==NULL)
    {
        printf(" \nqueue is empty");
    }
    else 
    {
        struct node *temp;
        temp=front;
        while(temp!=NULL)
        {
            printf("%d\t",temp->data);
            temp=temp->next;
        }
    }
}
void peek()
{
    if(rear==NULL&&front==NULL)
    {
        printf(" \nqueue is empty");
    }
    else{
        printf("\n peek is %d",front->data);
    }
}