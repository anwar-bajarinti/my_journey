#include <stdio.h>

int main()
{
    int i, j, n;

    printf("Enter length of sequence: ");
    scanf("%d", &n);

    int x[n], h[n], y[n];

    printf("Enter x sequence:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &x[i]);
    }

    printf("Enter h sequence:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &h[i]);
    }

    // Initialize output
    for(i = 0; i < n; i++)
    {
        y[i] = 0;
    }

    // Circular convolution
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            int k = i - j;
            if(k < 0)
                k = k + n;

            y[i] += x[j] * h[k];
        }
    }

    printf("Output sequence y:\n");
    for(i = 0; i < n; i++)
    {
        printf("%d ", y[i]);
    }

    return 0;
}
