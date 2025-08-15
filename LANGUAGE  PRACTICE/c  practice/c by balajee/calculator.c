#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check(char *x)
{
    int i = 0;
    while (x[i] != '\0')
    {
        if (x[i] == '\n')
        {
            i++;  // Just skip the newline
            continue;
        }
        if (x[i] < '0' || x[i] > '9')
        {
            return 0;
        }
        i++;
    }
    return 1;
}

void add(int a, int b)
{
    printf("Addition is = %d\n", a + b);
}
void sub(int a, int b)
{
    printf("Subtraction is = %d\n", a - b);
}
void mul(int a, int b)
{
    printf("Multiplication is = %d\n", a * b);
}
void divide(int a, int b)
{
    if (b == 0)
    {
        printf("Error: Division by zero!\n");
        return;
    }
    printf("Quotient is = %d\n", a / b);
    printf("Remainder is = %d\n", a % b);
}

int main()
{
    char a[51];
    char op;
    char decision[10];

    do
    {
        int num1, num2;

        printf("Enter number 1: ");
        fgets(a, sizeof(a), stdin);
        if (!check(a))
        {
            printf("Invalid input! Please enter only digits.\n");
            return 0;
        }
        num1 = atoi(a);

        printf("Enter number 2: ");
        fgets(a, sizeof(a), stdin);
        if (!check(a))
        {
            printf("Invalid input! Please enter only digits.\n");
            return 0;
        }
        num2 = atoi(a);

        printf("Choose operation (+, -, *, /): ");
        scanf(" %c", &op);  

        switch (op)
        {
        case '+':
            add(num1, num2);
            break;
        case '-':
            sub(num1, num2);
            break;
        case '*':
            mul(num1, num2);
            break;
        case '/':
            divide(num1, num2);
            break;
        default:
            printf("Invalid operation!\n");
        }

        printf("Type 'exit' to quit or anything else to continue: ");
        scanf("%s", decision);
        getchar();  
    } while (strcmp(decision, "exit") != 0);

    return 0;
}
