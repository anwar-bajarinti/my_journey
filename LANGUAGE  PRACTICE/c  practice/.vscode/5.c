#include<stdio.h>
#include<string.h>
int main(){
 char str[20]="12345600";
 int a[20];
 for(int i=0;str[i]!='\0';i++){
    a[i]=(int)str[i]-'0';
    printf("loop =%d\n",i);
 }
 a[8]=2;
 for(int i=0;i<=8;i++){
    printf("%d=%d\n",i,a[i]);
 }
    return 0;

}