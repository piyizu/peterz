# compile this simply using gcc
# gcc ./FILENAME.s -m32 -o ./OUT_FILENAME

# The code is from the book: Professional Assembly Language

.section .data
output:
    .asciz "The value is %d\n"
values:
    .int 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60

.section .text
.globl main
main:
    movl $0, %edi
loop:
    movl values(, %edi, 4), %eax
    pushl %eax
    pushl $output # '$' before a label means the address of the label
    # pushed from the last argument to the first in printf()
    call printf
    addl $8, %esp # pushing will decrease %esp value
    inc %edi
    cmpl $11, %edi
    jne loop
    
    movl $0, %ebx
    movl $1, %eax
    int $0x80

