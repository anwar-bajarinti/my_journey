#include<stdio.h>
#include<stdlib.h>
void reverse();
struct node{
    int data;
    struct node *next;
};
struct node *head,*newnode,*temp;
void main()
{
   
   
    head=0;
    int choice;
    while(choice){
        newnode=(struct node*)malloc(sizeof(struct node));
        printf(" enter data=");
        scanf("%d",&newnode->data);
        newnode->next=0;
        if(head==0)
        {
            head=temp=newnode;
        }
        else
        {
            temp->next=newnode;
            temp=newnode;
        }
        printf(" do you want add press (1/0)");
        scanf("%d",&choice); 
        
    }
    printf(" before reverse elements are\n ");
    temp=head;
    while(temp!=0)
    {
        printf("%d-->",temp->data);
        temp=temp->next;
    }
    reverse();
    printf(" \nafterelements are ");
    temp=head;
    while(temp!=0)
    {
        printf("%d-->",temp->data);
        temp=temp->next;
    }
}
void reverse()
{
    struct node *prev,*current,*nextnode;
    prev=0;
    current=nextnode=head;
    while(nextnode!=0)
    {
        nextnode=nextnode->next;
        current->next=prev;
        prev=current;
        current=nextnode;
    }
    head=prev;
}