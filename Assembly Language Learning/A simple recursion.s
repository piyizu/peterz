# calculate the product of all numbers in an array
# to compile the code, run 
# 'gcc ./CODE_FILE_NAME.S -m32 -o ./OUTPUT_FILENAME'

# You should guarantee that the result be in the range of 32-bit integer

.section .data
size:
	.int 5                             # the size of the array
ar:
	.int 2, 4, 6, 8, 10  # the elements in the array
res_output:
	.asciz "The product is %d\n"

.section .text
.globl main
main:
	leal ar, %edi                       # edi as the pointer
	movl size, %ecx                     # ecx as the counter
	call rproduct

	# print the result
	pushal
	movl %esp, %ebp
	subl $8, %esp
	movl %eax, -4(%ebp)
	movl $res_output, -8(%ebp)
	call printf
	addl $8, %esp
	popal

exit:
	movl $1, %eax
	movl $0, %ebx
	int $0x80

rproduct:
	cmp $0, %ecx
	jle return_one
	
	# push (%edi) on to the stack
	subl $4, %esp
	movl (%edi), %ebx
	movl %ebx, (%esp)

	# move the pointer forward and decrease the counter
	addl $4, %edi
	subl $1, %ecx
	call rproduct
	
	# multiplication after returning and pop
	mull (%esp)
	addl $4, %esp
	ret
return_one:
	xorl %edx, %edx
	movl $1, %eax
	ret
