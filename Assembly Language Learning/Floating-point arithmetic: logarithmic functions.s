# Floating-point arithmetic: calculate pi * 2 ^ 16 * log_13(27)
# to compile the code, run 
# 'gcc ./CODE_FILE_NAME.S -m32 -o ./OUTPUT_FILENAME'

.section .data
N:
	.double 27
base13:
	.double 13
scale_exp:
	.int 16
res_output:
	.asciz "%lf\n"

.section .text
.globl main
main:
loop:
	finit

	fld1 # load 1 onto the stack
	fldl N
	fyl2x # st(0) = st(1) * log2 ( st(0) ) and st(1) is freed

	fld1
	fldl base13
	fyl2x

	# log_base(N) = log_2(N) / log_2(base)

	fdivr %st(1) # it is st(1) instead of st(2)

	# pi * 7 ^ pi = pi * 2 ^ (log_2(7^pi)) = pi * 2 ^ (pi * log_2(7))
	fildl scale_exp
	fldpi
	fscale # st(0) = st(0) * 2 ^ ( RoundTowardsZero(st(1)) ) and st(1) is NOT freed

	fmul %st(2) # it is st(2) where log_13(27) has been placed

	pushal
	movl %esp, %ebp
	subl $12, %esp
	movl $res_output, -12(%ebp)
	fstl -8(%ebp)
	call printf
	addl $12, %esp
	popal
exit:
	movl $1, %eax
	movl $0, %ebx
	int $0x80
