#include <stdio.h>
#define MAX 20

int main()
{
    int Nx, Ny, n, k;
    int x[MAX], y[MAX], sum;

    printf("Enter length of x: ");
    scanf("%d",&Nx);
    printf("Enter x:\n");
    for(n=0;n<Nx;n++) scanf("%d",&x[n]);

    printf("Enter length of y: ");
    scanf("%d",&Ny);
    printf("Enter y:\n");
    for(n=0;n<Ny;n++) scanf("%d",&y[n]);

    printf("Cross-correlation:\n");
    for(k=-(Ny-1);k<=Nx-1;k++)
    {
        sum = 0;
        for(n=0;n<Nx;n++)
            if(n-k>=0 && n-k<Ny)
                sum += x[n]*y[n-k];

        printf("k=%d : %d\n",k,sum);
    }

    return 0;
}
