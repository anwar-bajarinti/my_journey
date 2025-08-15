#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
 
 int a[20]={2,3,4,5,6,7};
 char v[20]={};
 sprintf(v,"%d",a);
 printf("%s",v);

 return 0;

}