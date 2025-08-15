#include<stdio.h>
void memchn(int *x,int *y,int z);
int main()
{
    int a[5]={1,2,3,4,5};
    int b[5];
    memchn(a,b,5);
    for(int i=0;i<5;i++){
    printf("array b[%d]=%d\n",i,b[i]);
    }
    return 0;
}
void memchn(int *x,int *y,int z)
{
    int i;
    for(i=0;i<z;i++)
    {
        y[i]=x[i];
    }
}