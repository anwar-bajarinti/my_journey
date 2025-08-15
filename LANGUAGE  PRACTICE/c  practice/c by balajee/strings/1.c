#include<stdio.h>
char* fun()
{
     
    return "Noty";
}
void main()
{
    char *ptr;
   
    ptr=fun();
    ptr[0]='z';
    printf("%s",ptr);
}