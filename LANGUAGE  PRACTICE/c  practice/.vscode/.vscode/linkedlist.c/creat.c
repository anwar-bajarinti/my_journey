#include<stdio.h>
#include<stdlib.h>
void main()
{
    struct node{
        int data;
        struct node *next;
    };
    struct node *head,*newnode,*temp;
   
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
    printf("elements are ");
    temp=head;
    while(temp!=0)
    {
        printf("%d-->",temp->data);
        temp=temp->next;
    }
}