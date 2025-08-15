#include<stdio.h>
void fill(int *x);
int main()
{
    int a[10];
    fill(a);
    printf("the aray isl\n");
    for(int i=0;i<5;i++){
        printf("%d\n",a[i]);
    }
}
void fill(int *x){
    for(int i=0;i<10;i++){
        x[i]=2*i;
            }
}