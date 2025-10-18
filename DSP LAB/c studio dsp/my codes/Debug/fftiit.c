#include <stdio.h>
#include <math.h>
#define N 8
#define PI 3.1416

typedef struct {
    float real, imag;
} complex;

int main() {
    complex x[N], temp, w, t;
    int i, j, k, m, n1, n2;

    // Input sequence
    float input[N] = {1, 2, 3, 4, 2, 1, 0, 0};
    for (i = 0; i < N; i++) {
        x[i].real = input[i];
        x[i].imag = 0;
    }

    // Bit reversal
    j = 0;
    for (i = 1; i < N - 1; i++) {
        m = N / 2;
        while (j >= m) {
            j -= m;
            m /= 2;
        }
        j += m;
        if (i < j) {
            temp = x[i];
            x[i] = x[j];
            x[j] = temp;
        }
    }

    // FFT computation
    n2 = 1;
    for (k = 1; k <= log2(N); k++) {
        n1 = n2;
        n2 = n2 * 2;
        for (j = 0; j < n1; j++) {
            w.real = cos(2 * PI * j / n2);
            w.imag = -sin(2 * PI * j / n2); // negative sign for forward FFT
            for (i = j; i < N; i += n2) {
                // Butterfly computation
                t.real = w.real * x[i + n1].real - w.imag * x[i + n1].imag;
                t.imag = w.real * x[i + n1].imag + w.imag * x[i + n1].real;

                x[i + n1].real = x[i].real - t.real;
                x[i + n1].imag = x[i].imag - t.imag;

                x[i].real += t.real;
                x[i].imag += t.imag;
            }
        }
    }

    // Output FFT results
    printf("FFT Output:\n");
    for (i = 0; i < N; i++) {
        printf("X[%d] = %.3f + j%.3f\n", i, x[i].real, x[i].imag);
    }

    return 0;
}
