#include<stdio.h>
#include<stdlib.h>
#define N 5
int top=-1;
int stack[N];
void pop();
void push(int);
void display();
void peek();
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
void push(int data)
{ 
    if(top==N-1)
    {
        printf(" \nstack over flow");
    }
    top++;
    stack[top]=data;
}
void pop()
{
    if(top==-1) printf(" \nstack  underflow");
    else
    {
        printf(" \npopped data=%d",stack[top]);
        top--;
    }
}
void peek()
{
    if (top==-1)
    {
        printf(" \nstack empty");
    }
    else
    {
        printf(" \npeek data=%d",stack[top]);
    }
}
void display()
{
    int i;
    printf(" \n data are");
    for(i=top;i>=0;i--)
{
    printf("%d\t",stack[i]);
}
}