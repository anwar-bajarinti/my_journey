#include<stdio.h>
#include<stdlib.h>
void create();
 void display();
struct node
{
    int data;
    struct node *next;
    struct node *prev;
}*head,*newnode,*temp;
void main()
{
    head=0;
    create();
   display();
}

 void create()
{
int choice=1;
while(choice)
{
newnode=(struct node*)malloc(sizeof(struct node));
newnode->next=0;
newnode->prev=0;
printf(" enter a data\n");
scanf("%d",&newnode->data);
if(head==0)
{
    head=temp=newnode;
}
else{
    temp->next=newnode;
    newnode->prev=temp;
    temp=newnode;
}
printf("\n do you want to add");
scanf("%d",&choice);
}
}
void display()
{
    temp=head;
    while(temp!=0)
    {
        printf("<--%d-->",temp->data);
        temp=temp->next;
    }
}