# Bit test example, CPUID instruction support test
# To compile: gcc ./FILENAME.s -m32 -o ./OUT_FILENAME

.section .data
support_cpuid:
	.asciz "This cpu supports CPUID instruction!\n"
not_support_cpuid:
	.asciz "This cpu does not support CPUID instruction.\n"

.section .text
.globl main
main:
	pushfl # push the EFLAGS register value onto the stack
	popl %eax
	xorl $0x00200000, %eax # alter the 21st bit of the EFLAGS value
	pushl %eax
	popfl # pop up the stack value to EFLAGS register

	pushfl
	popl %ebx
	xorl %ebx, %eax # check if the value in EFLAGS has been altered, zero result means changed 
	testl $0x00200000, %eax # test is AND without modifying the destination
	jnz cpuid_not_support 
	// if eax AND 0x00200000 is non-zero, which means the value in EFLAGS has not been changed
	// and the cpu does not support CPUID instruction, the ZF bit will be set.

	pushal
	movl %esp, %ebp
	subl $4, %esp
	movl $support_cpuid, -4(%ebp)
	call printf
	addl $4, %esp
	popal

exit:
	movl $1, %eax
	movl $0, %ebx
	int $0x80

cpuid_not_support:
	pushal
	movl %esp, %ebp
	subl $4, %esp
	movl $not_support_cpuid, -4(%ebp)
	call printf
	addl $4, %esp
	popal

	jmp exit
