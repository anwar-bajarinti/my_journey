#include <stdio.h>

// Uncomment different macros to test
#define A 10
// #define B 20

int main() {
    
    // 1. #ifdef
#ifdef A
    printf("A is defined. Value of A = %d\n", A);
#endif

    // 2. #ifndef
#ifndef B
    printf("B is not defined.\n");
#endif

    // 3. #if with condition
#if A == 10
    printf("A is equal to 10\n");
#else
    printf("A is not equal to 10\n");
#endif

    // 4. #elif
#if A == 5
    printf("A is 5\n");
#elif A == 10
    printf("A is 10 (elif block)\n");
#else
    printf("A is something else\n");
#endif

    return 0;
}
