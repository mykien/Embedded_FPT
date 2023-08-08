#include <stdio.h>

int a = 2;
#define SVST_CSR    *(int*)(a)
#define SVST_CSR2   (volatile unsigned int*)(a)

int main() {
    printf ("1.%d\n", SVST_CSR);
    printf ("2.%d", SVST_CSR2);
    return 0;
}