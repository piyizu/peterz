# Use quad-word integers
# To compile: gcc ./FILENAME.s -m32 -o ./OUT_FILENAME
.section .data
nums:
	.quad 0xFFFFDFFFFFFFFFFD, 0xFFFFFFFFFFFFFFFF, -32
	#     −35184372088835     -1                  -32
	#   need to convert to hex             -32 in [-2^31, 2^31 - 1], rightly converted
	#              all will be stored in 'little endian' mode
output:
	.asciz "%lld\n"

.section .text
.globl main
main:
	movl $nums, %eax

	pushal
	pushl 4(%eax) # higher 4 bytes in higher address
	pushl (%eax)
	pushl $output
	call printf
	addl $12, %esp
	popal

	pushal
	pushl 12(%eax)
	pushl 8(%eax)
	pushl $output
	call printf
	addl $12, %esp
	popal

	pushal
	pushl 20(%eax)
	pushl 16(%eax)
	pushl $output
	call printf
	addl $12, %esp
	popal
	
exit:
	movl $1, %eax
	movl $0, %ebx
	int $0x80
