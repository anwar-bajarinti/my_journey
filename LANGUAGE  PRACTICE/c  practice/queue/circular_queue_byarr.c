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
    
    enqueue(10);
    enqueue(20);
    
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
    if((rear+1)%N==front)
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
        rear=(rear+1)%N;
        queue[rear]=x;
    }
}
void dequeue()
{   if(front==rear)  
    {front=rear=-1;
    }
    if(front==-1&&rear==-1)
    {
        printf("\n queue empty");
    }
   else{
    front=(front+1)%N;
   }
}
void peek()
{
    printf("\n peek=%d",queue[front]);
}
void display()
{int i=front;
    while(i!=rear)
    {
        printf(" %d\t",queue[i]);
        i=(i+1)%N;
    }
    printf(" %d",queue[rear]);
}