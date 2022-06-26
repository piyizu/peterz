# gcc ./FILENAME.s -m32 -o ./OUT_FILENAME

.section .data
ar:
    .int -100, -3, -8, -2, -1, -1000, -999, -1000, -88, -76
res_output:
    .asciz "The maximum in the array is %d\n"
loop_output:
    .asciz "Index equals %d and so far the maximum is %d\n"

.section .text
.globl main
main:
    movl ar, %ebx
    movl $1, %edi
loop_in_array:
        movl ar(, %edi, 4), %eax
        cmp %ebx, %eax # cmp operation will not change the original values
        cmovg %eax, %ebx # using cmovg instead of cmova for signed value comparison
        # it is better to use conditional Move between registers

        pushl %ebx
        pushl %edi
        pushl $loop_output
        call printf
        addl $12, %esp

        inc %edi
        cmp $10, %edi
        jne loop_in_array
    
    pushl %ebx
    pushl $res_output
    call printf
    addl $8, %esp

    movl $1, %eax
    movl $0, %ebx
    int $0x80
