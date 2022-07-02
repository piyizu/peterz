# Using numbers: floating point values
# To compile: gcc ./FILENAME.s -m32 -o ./OUT_FILENAME
.section .data
floating_point:
	.float 3.14
output:
	.asciz "%%f:%f, %%lf:%f\n"

.section .text
.globl main
main:
	pushal

	movl %esp, %ebp
	subl $20, %esp
	
	flds floating_point
	fstl -8(%ebp)
	
	movl -8(%ebp), %eax
	movl %eax, -16(%ebp)
	movl -4(%ebp), %eax
	movl %eax, -12(%ebp)
	
	movl $output, -20(%ebp)
	call printf
	addl $20, %esp
	
	popal
exit:
	movl $1, %eax
	movl $0, %ebx
	int $0x80

/* Why do we need FLD and FST ?

According to Intel's IA-32 manuals for programmers, the x87 processor first converts a single- or 
double-precision floating-point value to an 80-bit double extended-precision one before other operations. 
And the processor will automatically converts what in an 80-bit floating-point register to a single- 
or double-precision floating-point value before it has been put into other places. 
Converting to 80-bit format may help improve precision in calculation.

And another intresting thing is that 'printf' seems to only use double-precision floating-point value. 
When I tried to print a single-precision floating-point value, it did not display the right 
value. But the double-precision values were rightly printed.

One more thing, in the x86 architecture, little-endian mode is adopted, 
so higher address stores a more significant byte.
*/
