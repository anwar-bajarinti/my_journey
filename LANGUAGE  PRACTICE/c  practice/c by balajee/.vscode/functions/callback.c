#include<stdio.h>
void add(int a,int b)
{
    printf("add=%d",a+b);
}
void sub(int a,int b)
{
    printf(" sub=%d",a-b);
}
void display(void (*ptr)(int ,int))
{
    ptr(5,4);
}
void main()
{
    display(add);
    display(sub);
}