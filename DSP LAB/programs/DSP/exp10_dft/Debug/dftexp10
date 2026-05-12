#include<stdio.h>
#include<math.h>
int main()
 {
	 int i,N,k,x[20];
	 float pi=3.14,z[20],y[20];
	 printf("enter a input sequence");
	 scanf("%d",&N);
	 printf(" enter a sequence");
	 for(i=0;i<N;i++)
	 { scanf("%d",&x[i]);
	 }
	 for(k=0;k<N;k++)
	 { y[k]=0;
	   z[k]=0;
	   for(i=0;i<N;i++)
	      { y[k]=y[k]+x[i]*cos((2*pi*i*k)/N);
	        z[k]=z[k]+x[i]*sin((2*pi*i*k)/N);
	      }
         printf(" %f -j%f",y[k],z[k]);
		 }
 return 0;
 }