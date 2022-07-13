// inline ASM example, using registers

#include <stdio.h>
#include <string.h>

int main() {
        char src[32] = "I am learning ASM.\n";
        char dest[32] = {0} ;
        int length = 1 + strlen(src);

        asm volatile( // 'volatile' is necessary, as the code produces no output and would be ignored by the compiler
                "rep movsb"
                : // output is empty
                : "S"(src), "D"(dest), "c"(length) // input init.: %esi <-- src, %edi <-- dest, %ecx <-- length
                : // additional changed registers: empty
        );

        printf("%s", dest);
        return 0;
}
