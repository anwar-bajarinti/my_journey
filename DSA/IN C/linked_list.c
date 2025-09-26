#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
};
struct node* creat(struct node* head,int data)
{
    struct node *temp=(struct node*)malloc(sizeof(struct node));
temp->next=NULL;
temp->data=data;
return temp;
}
struct node* Insertbegin(struct node *head,int data)
{
    struct node *temp=(struct node*)malloc(sizeof(struct node));
    temp->data=data;
    if(head==NULL) head=temp;
    else
    temp->next=head;
    head=temp;
    return head;
    
}
void display(struct node *head)
{
    struct node *ptr;
    ptr=head;
    while(ptr!=NULL){
        printf("%d->",ptr->data);
        ptr=ptr->next;
    }
}
int main(){
struct node *p=NULL;
p=Insertbegin(p,10);
p=Insertbegin(p,20);
p=Insertbegin(p,30);
display(p);


    return 0;
}