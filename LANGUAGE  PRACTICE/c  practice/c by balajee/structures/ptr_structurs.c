#include <stdio.h>
#include <conio.h>  // for getch()

struct a {
    int b;
    char c;
    char str[50];
};

int main() {
    struct a temp;
    struct a* ptr = &temp;

    printf("Enter integer b: ");
    scanf("%d", &ptr->b);

    // getch reads a single character without waiting for Enter
    printf("Press any character key for c: ");
    ptr->c = getch();  // char input silently
    printf("\nYou pressed: ");
    putchar(ptr->c);   // show it using putchar
    printf("\n");

    // flush newline before gets
    getchar();  // consumes leftover '\n' from scanf

    printf("Enter a string: ");
    gets(ptr->str);  // read string input

    // display output
    printf("\n--- Output ---\n");
    printf("Integer b = %d\n", ptr->b);
    printf("Character c = ");
    putchar(ptr->c);
    printf("\n");
    printf("String = ");
    puts(ptr->str);  // print string using puts

    return 0;
}
