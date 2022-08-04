// inline ASM example, using floating-point numbers

// using gcc ./FILENAME.c -m32 -Og -S to generate the assembly code
// you would find that the compiler has virtually perfectly handled floating-point values

// remember that printf accepts double-precision floating-point numbers

#include <stdio.h>
#include <string.h>

int main() {
        float radian;
        scanf("%f", &radian);

        float cosine, sine;
        asm(
                "fsincos" // denoting st(0) as x, x will be popped and sin(x) is pushed and then cos(x) is pushed
                : "=t"(cosine), "=u"(sine)
                : "0"(radian) // Referencing placeholder '0' is used instead of 't'
        );

        printf("sin(%f) = %f, cos(%f) = %f\n", radian, sine, radian, cosine);
        
        return 0;
}
