#include<stdio.h>
#include<stdlib.h>
void push(int);
void pop();
void peek();
void display();
struct node
{
    int data;
    struct node *next;
}*top=0;
void main()
{
push(10);
push(20);
pop();
display();
peek();
pop();
pop();

}
void push(int x)
{
    struct node*newnode;
    newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=x;
   newnode->next=top;
   top=newnode;
}
void pop()
{ if(top==0)
    {
        printf(" \nemplty");
        return;
    }
    struct node *temp;
    temp=top;
    printf(" \npopped data %d",top->data);
    top=top->next;
    free(temp);
}
void peek()
{
    printf(" \npeek data %d",top->data);
}
void display()
{
    struct node *temp;
    temp=top;
    while(temp!=0)
    {
        printf("\n%d",temp->data);
        temp=temp->next;
    }
}