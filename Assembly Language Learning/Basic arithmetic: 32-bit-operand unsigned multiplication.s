# Multiplication in ASM
# To compile: gcc ./FILENAME.s -m32 -o ./OUT_FILENAME

/* INSTRUCTION : 
	MUL <source>
-----------------------------------------------------
| oprands size | destination register | result form |
-----------------------------------------------------
|    8 bits    |        AL            |     AX      |
|   16 bits    |        AX            |   DX:AX     |
|   32 bits    |        EAX           |  EDX:EAX    | * our program shows this case
-----------------------------------------------------
*/

.section .data
lnums:
	.int 1352117890, 723890
res_output:
	.asciz "%lld = %d * %d\n"

.section .text
.globl main
main:
	movl lnums, %eax
	mull lnums + 4

	pushal
	movl %esp, %ebp
	subl $20, %esp
	movl lnums + 4, %ebx   # do not do 'memory to memory' moving
	movl %ebx, -4(%ebp)
	movl lnums, %ebx
	movl %ebx, -8(%ebp)
	movl %edx, -12(%ebp)
	movl %eax, -16(%ebp)
	movl $res_output, -20(%ebp)
	call printf
	addl $20, %esp
	popal

exit:
	movl $1, %eax
	movl $0, %ebx
	int $0x80
