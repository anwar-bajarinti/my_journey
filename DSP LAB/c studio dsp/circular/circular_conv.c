#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
    int i, j, k, m, n;
    int x[30], h[30], y[30], a[30];
    
    printf("Enter the length of 1st sequence: ");
    scanf("%d", &m);
    
    printf("Enter the length of 2nd sequence: ");
    scanf("%d", &n);
    
    printf("Enter the values of 1st sequence x(n):\n");
    for(i = 0; i < m; i++)
        scanf("%d", &x[i]);
    
    printf("Enter the values of 2nd sequence h(n):\n");
    for(i = 0; i < n; i++)
        scanf("%d", &h[i]);

    // If sequences are of unequal length, make them equal by padding zeros
    if(m != n)
    {
        if(m > n)
        {
            for(i = n; i < m; i++)
                h[i] = 0;
            n = m;
        }
        else
        {
            for(i = m; i < n; i++)
                x[i] = 0;
            m = n;
        }
    }

    // Initialize output sequence
    for(i = 0; i < n; i++)
        y[i] = 0;

    // Circular Convolution process
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            k = (i - j);
            if(k < 0)
                k = k + n;
            y[i] = y[i] + x[j] * h[k];
        }
    }

    // Output result
    printf("\nCircular Convolution Output is:\n");
    for(i = 0; i < n; i++)
        printf("y[%d] = %d\n", i, y[i]);
    
    return 0;
}