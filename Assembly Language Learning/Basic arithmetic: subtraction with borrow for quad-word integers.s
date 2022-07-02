# Basic Arithmetic: subtraction (with borrow) for quadword signed integers
# To compile: gcc ./FILENAME.s -m32 -o ./OUT_FILENAME

.section .data
qnums:
	.quad 5456546413215, -123458975455
	#       eax:ebx          ecx:edx
res_output:
	.asciz "%lld = %lld - %lld\n"

.section .text
.globl main
main:
	# little endian mode: higher address stores a more significant digit
	movl qnums, %ebx
	movl qnums + 4, %eax
	movl qnums + 8, %edx
	movl qnums + 12, %ecx
	
	# the order matters: first encountered (in the output string), last pushed
	movl %esp, %ebp
	subl $28, %esp
	movl %ecx, -4(%ebp)
	movl %edx, -8(%ebp)
	movl %eax, -12(%ebp)
	movl %ebx, -16(%ebp)

	subl %edx, %ebx
	sbbl %ecx, %eax
	movl %eax, -20(%ebp)
	movl %ebx, -24(%ebp)
	movl $res_output, -28(%ebp)

	call printf
	
	addl $28, %esp

exit:
	movl $1, %eax
	movl $0, %ebx
	int $0x80
/* 
	The instruction for addition with carry is ADC, whose usage is similar to that of SBB. 
	Remember to add an appropriate suffix (b, w or l) after those instructions when using them.
*/
