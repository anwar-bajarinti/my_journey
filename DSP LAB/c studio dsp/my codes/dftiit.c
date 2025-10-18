			 #include <stdio.h>
#include <math.h>

int main() {
    int N, i, k;
    float pi = 3.1416;
    int x[20];
    float y[20], z[20];

    printf("Enter the length of input sequence N: ");
    scanf("%d", &N);

    printf("Enter the values of input sequence x(n):\n");
    for (i = 0; i < N; i++) {
        scanf("%d", &x[i]);
    }

    printf("The values of output sequence X[k]:\n");
    for (k = 0; k < N; k++) {
        y[k] = 0;
        z[k] = 0;
        for (i = 0; i < N; i++) {
            y[k] += x[i] * cos((2 * pi * i * k) / N);
            z[k] += x[i] * sin((2 * pi * i * k) / N);
        }
        printf("X[%d] = %.2f - j%.2f\n", k, y[k], z[k]);
    }

    return 0;
}