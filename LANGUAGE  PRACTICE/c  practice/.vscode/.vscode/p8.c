#include<stdio.h>
int memchn(char *x,char *y);
int main()
{
    char a[6]="anwar";
    char b[6]="anwar";
    int c;
   c= memchn(a,b);
   if(c==0){
    printf("fail");
   }
    else
    {
        printf("success");
    }
   
   
    return 0;
}
int memchn(char *x,char *y)
{
    int i;
    for(i=0;x[i]!='\0';i++)
    {
        if(y[i]!=x[i])
        return 0;
    }
    return 1;
}