#include<stdio.h>
void add(char a,int l1,char b,int l2,char *c);
void main(){
    char a[6]="hello";
    char b[5]="boss";
    char c[]={};
    add(a,6,b,5,*c);
    printf("array is ");
    printf("%s",c);
    }
void add(char a,int l1,char b,int l2,char *c){
    for(int i=0;i<l1;i++){
        c[i]=a[i];
    }
    for(i;i<l2;i++){
        c[i]=b[i];
    }
}