#include <stdio.h>

#define MAX 60

int main()
{
    int m, n, N;
    int x[MAX], h[MAX], y[MAX];
    int i, j, k;

    printf("Enter length of x: ");
    scanf("%d", &m);

    printf("Enter length of h: ");
    scanf("%d", &n);

    N = m + n - 1;

    // Read x and zero-pad
    printf("Enter x sequence:\n");
    for(i = 0; i < m; i++)
        scanf("%d", &x[i]);
    for(i = m; i < N; i++)
        x[i] = 0;

    // Read h and zero-pad
    printf("Enter h sequence:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &h[i]);
    for(i = n; i < N; i++)
        h[i] = 0;

    // Circular convolution gives linear convolution
    for(i = 0; i < N; i++)
    {
        y[i] = 0;
        for(j = 0; j < N; j++)
        {
            k = i - j;
            if(k < 0)
                k = k + N;

            y[i] += x[j] * h[k];
        }
    }

    printf("Linear convolution result:\n");
    for(i = 0; i < N; i++)
        printf("%d ", y[i]);

    return 0;
}
