#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
};
struct node *head,*newnode,*temp;


void main()
{head=0;
    int data=1,pos,i=1,count=1;
   
    int choice=1;
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

    newnode=(struct node*)malloc(sizeof(struct node));
    printf(" \nenter a data to insert at beginning \n");
    scanf("%d",&data);
    newnode->data=data;
    newnode->next=head;
    head=newnode;
    newnode=(struct node*)malloc(sizeof(struct node));
    printf(" enter a data to insert at end \n");
    scanf("%d",&data);
    newnode->data=data;
    temp=head;
    newnode->next=0;
    while(temp->next!=0)
    {
        temp=temp->next;
    }
    temp->next=newnode;
    temp=head;
    while(temp!=0)
    { count++;
        temp=temp->next;
    }
    
    printf(" enter postion at you want to add");
    scanf("%d",&pos);
    temp=head;
    if(pos>count)
    {
        printf(" invalid postion");
    }
    else{
    newnode=(struct node*)malloc(sizeof(struct node));
    printf(" enter a data to insert at given position \n");
    scanf("%d",&data);
    newnode->data=data;
    temp=head;
    i=1;
    while(i<pos)
    {
        temp=temp->next;
        i++;
    }
    newnode->next=temp->next;
    temp->next=newnode;
 }
 printf("elements are ");
    temp=head;
    while(temp!=0)
    {
        printf("%d-->",temp->data);
        temp=temp->next;
    }

}
