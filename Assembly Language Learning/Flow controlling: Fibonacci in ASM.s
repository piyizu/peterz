# fibonacci in ASM
# To compile: gcc ./FILENAME.s -m32 -o ./OUT_FILENAME

.section .data
output:
	.asciz "%d\n"

.section .text
.globl main
main:
	movl $0, %eax # fib_var 1
	movl $1, %ebx # fib_var 2
	movl $45, %ecx # counter (reverse order)
fibonacci:
	cmp %eax, %ebx
	jl cond_ebx_lessthan_eax
	addl %ebx, %eax
	pushal # push all the general register values onto the stack. 'pushad' is 'pushal' in GNU ASM 
	pushl %eax
	jmp fib_out
cond_ebx_lessthan_eax:
	addl %eax, %ebx
	pushal
	pushl %ebx
fib_out:
	pushl $output
	call printf
	addl $8, %esp
	popal # restore all the general register values from the stack
	
	dec %ecx
	jnz fibonacci

exit:
	movl $1, %eax
	movl $0, %ebx
	int $0x80
