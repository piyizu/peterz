# Multiplication in ASM
# To compile: gcc ./FILENAME.s -m32 -o ./OUT_FILENAME

/* 
	INSTRUCTION:
	1. IMUL <source>
		used exactly the same as MUL
	2. IMUL <source>, <destination>
		<destination> = <source> * <destination>
		<destination> must be a 16- or 32-bit general register
	3. IMUL <immediate number>, <source>, <destination>
		<desination> = <immediate number> * <source>
		<destination> must be a general register

	We are going to show the latter two cases.
*/

.section .data
lnums:
	.int 1352117890, 723890
res_output:
	.asciz "%d = %d * %d\n"

.section .text
.globl main
main:
	movl $-455, %eax
	movl $789, %ebx

	pushal
	movl %esp, %ebp
	subl $16, %esp
	movl %ebx, -4(%ebp)
	movl %eax, -8(%ebp)
	imull %eax, %ebx  # always remember to add l, w or b at the end of the mnemonics
	movl %ebx, -12(%ebp)
	movl $res_output, -16(%ebp)
	call printf
	addl $16, %esp
	popal

	pushal
	movl %esp, %ebp
	subl $16, %esp
	movl %eax, -4(%ebp)
	movl $-412, -8(%ebp)
	imull $-412, %eax, %eax  # <source> and <destination> can be the same
	movl %eax, -12(%ebp)
	movl $res_output, -16(%ebp)
	call printf
	addl $16, %esp 
	popal
exit:
	movl $1, %eax
	movl $0, %ebx
	int $0x80
