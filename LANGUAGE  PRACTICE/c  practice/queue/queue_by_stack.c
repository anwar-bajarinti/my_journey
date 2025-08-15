#include<stdio.h>
#define N 5
int s1[N];
int s2[N];
int top1=-1;
int top2=-1;
void push1(int data);
void push2(int data);
int pop1();
int pop2();
int count=0;
void display();
void main()
{
    enqueue(10);
    enqueue(20);
    display();
    dequeue();
    dequeue();
    dequeue();

}
void enqueue( int data)
{
    push1(data);
    count++;
}
void dequeue()
{ if (top1==-1)
    {
        printf(" \n queue empty");
        return;
    }
    int i=0;
    for(i;i<count;i++)
    {
        int a=pop1();
        push2(a);
    }
    count--;
    for(i=0;i<count;i++)
    {
         int b=pop2();
        push1(b);
    }
}
void push1(int data)
{
    s1[++top1]=data;
}
void push2(int data)
{
    s2[++top2]=data;
}
int pop1()
{
    return s1[top1--];
}
int pop2()
{
    return s2[top2--];
}
void display()
{
    int i=0;
    printf("\n elements are....");
    for(i;i<=top1;i++)
    {
        printf("%d\t",s1[i]);
    }
}