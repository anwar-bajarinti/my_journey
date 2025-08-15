#include<stdio.h>
#define N 5
int queue[N];
int rear=-1;
int front=-1;
void enqueue(int);
void dequeue();
void display();
void peek();
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
    if(rear==N-1)
    {
        printf("\n queue full");
    }
    else if(rear==-1&&front==-1)
    {
        rear=front=0;
        queue[rear]=x;
    }
    else
    {
        rear++;
        queue[rear]=x;
    }
}
void dequeue()
{   if(front>rear) printf(" \nunderflow");
    if(front==rear)
    {
        printf("\n  %d",queue[front]);
            front++;
        return;
    }
    if(front==-1&&rear==-1)
    {
        printf("\n queue empty");
    }
    front++;
}
void peek()
{
    printf("\n peek=%d",queue[front]);
}
void display()
{
    int i;
    for(i=front;i<=rear;i++)
    {
        printf(" %d\t",queue[i]);
    }
}