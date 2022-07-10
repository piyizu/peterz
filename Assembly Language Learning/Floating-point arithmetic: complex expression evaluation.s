# Floating-point arithmetic: calculate ((43.65/22)+(76.34*3.1))/((12.43*6)-(140.2/94.2))
# to compile the code, run 
# 'gcc ./CODE_FILE_NAME.S -m32 -o ./OUTPUT_FILENAME'

// Using x87 instructions with GAS, you should be very careful.
// Not only the order of source and destination is reversed, who they are in the
// expressions is sometimes unbelievably extraordinarily confusing.
// Our program shows a simple way to workaround such annoying problems. Using 
// unary FSUBR and FDIVR to make them more like DIV for integers.

.section .data
var_a:
	.double 43.65
var_b:
	.int 22
var_c:
	.double 76.34
var_d:
	.double 3.1
var_e:
	.double 12.43
var_f:
	.int 6
var_g:
	.double 140.2
var_h:
	.double 94.21
one:
	.double 1
res_output:
	.asciz "%lf\n"

.section .text
.globl main
main:
	finit
	fldl var_a
	fidivl var_b # st(0) = st(0) / var_b, 'l' indicates double
	fldl var_c
	fmull var_d # st(0) = st(0) * var_d
	faddp # st(1) = st(1) + st(0) and then pop

	fldl var_e
	fimull var_f
	fldl var_g
	fdivl var_h # st(0) = st(0) / var_h
	fsubr %st(1) # st(0) = st(1) - st(0) 'r' is added to change the operand position without extra moving
	fdivr %st(2) # st(0) = st(2) / st(0)

	fdivl one # st(0) /= one, similar to 'div divisor'      ---> FOR MEMORY LOCATIONS

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
