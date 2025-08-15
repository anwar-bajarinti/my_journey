#include<stdio.h>
#include<string.h>
int main(){
  int a=1234567;
  int rev=0;
  while(a!=0){
    rev=rev*10+a%10;
    a=a/10;
  }
  printf("rev=%d",rev);

    return 0;

}