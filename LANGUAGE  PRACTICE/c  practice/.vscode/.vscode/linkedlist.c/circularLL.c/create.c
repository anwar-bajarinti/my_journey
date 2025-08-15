#include<stdio.h>
#include<stdlib.h>
void create();
void display();

struct node
{
    int data;
    struct node *next;
}*head,*temp,*newnode;
void main(){
    create();
    display();

}
void create()
{
    head=NULL;
    temp=NULL;
    int choice=1;
    while(choice)
    {
    newnode=(struct node*)malloc(sizeof(struct node));
    printf("\n enter  a data ");
    scanf("%d",&newnode->data);
    newnode->next=NULL;
    if(head==NULL)
    {
        head=temp=newnode;
    }
    else
    {
        temp->next=newnode;
        temp=newnode;
    }
    printf(" do you want continue press 1 / 0");
    scanf("%d",&choice);
  }
  temp->next=head;

}
void display()
{
    head=temp;
    while(temp->next!=head)
    {
        printf("%d-->",temp->data);
        temp=temp->next;
    }
    printf(" %d-->",temp->data);
}