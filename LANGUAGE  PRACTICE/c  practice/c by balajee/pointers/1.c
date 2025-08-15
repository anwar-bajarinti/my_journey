#include<stdio.h>
void main()
{
    char str[]="welcomeltoknotty";
    char *ptr=str;
    printf("%c\n",*ptr);
    printf("%c\n",*(ptr+++1));
    printf("%c\n",*((ptr--+5)-1));
    printf("%c\n",*(++ptr+10)-32);
    printf("%c\n",*ptr);
    printf("%c %c",*++ptr,*--ptr);
}