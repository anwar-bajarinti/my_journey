#include<stdio.h>
void memchn(char *x,char *y);
int main()
{
    char a[6]="anwar";
    char b[6];
    memchn(a,b);
    
    printf("array =%s\n",b);
   
    return 0;
}
void memchn(char *x,char *y)
{
    int i;
    for(i=0;x[i]!='\0';i++)
    {
        y[i]=x[i];
    }
    y[i]='\0';
}