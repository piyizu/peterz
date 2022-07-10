# Floating-point arithmetic: input and add 
# to compile the code, run 
# 'gcc ./CODE_FILE_NAME.S -m32 -o ./OUTPUT_FILENAME'

.section .data
input_2_double:
	.asciz "%lf%lf"
output_res:
	.asciz "%lf\n"

.section .bss
	.lcomm double_a, 8
	.lcomm double_b, 8

.section .text
.globl main
main:
	# read two double-precision floating-point numbers from stdin
	pushal
	movl %esp, %ebp
	subl $12, %esp
	movl $input_2_double, -12(%ebp)
	movl $double_a, -8(%ebp)
	movl $double_b, -4(%ebp)
	call scanf      # call scanf for help
	addl $12, %esp
	popal

	fldl double_a
	fldl double_b
	faddp # add st(0) to st(1) and then pop st(0)
	# now the result of double_a + double_b is in st(0)
	fstl double_a

	pushal
	movl %esp, %ebp
	subl $12, %esp
	movl $output_res, -12(%ebp)
	movl double_a, %eax
	movl %eax, -8(%ebp)
	movl double_a + 4, %eax
	movl %eax, -4(%ebp)
	call printf
	addl $12, %esp
	popal
exit:
	movl $1, %eax
	movl $0, %ebx
	int $0x80
