#include<stdio.h>
void oddfind(int *a,int *total);
int main()
{
    int a[100];
    int total=0;
    oddfind(a,&total);
    printf("odd numbers are");
    for(int i=0;i<total;i++){
        printf("%d\n",a[i]);
    }
}
void oddfind(int *a,int *total){
    int idx=0;
    for(int i=10;i<=99;i++){
        
        if(i%2!=0){
            int n=i;
            int sum=0;
            while(n!=0){
                sum=sum+n%10;
                n=n/10;
                }
                if(sum==7){
                    (*total)++;
                    a[idx]=i;
                    idx++;

                }
                
                
            }
            
        }
    }
