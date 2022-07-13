# Using functions: command-line parameters


# to compile this code, run
#	as ./main.s --32 -o ./main.o
#	ld ./main.o -dynamic-linker /lib/ld-linux.so.2 -lc -m elf_i386 -o ./main
# or simply use make with Makefile that can be found in the directory

# compiling this code with gcc has been tested to work improperly

.section .data
str_argv:
	.asciz "The number of command-line arguments is %u \nIndex   Value\n================\n"
str_args:
	.asciz "%+5u   %s\n"

.section .text
.globl _start
_start:
	# print the number of arguments
	movl (%esp), %ecx

	pushal
	movl %esp, %ebp
	subl $8, %esp
	movl $str_argv, -8(%ebp)
	movl %ecx, -4(%ebp)
	call printf
	addl $8, %esp
	popal

	# print all arguments
	movl %esp, %ebp     # ebp will be used to access the args pointers
	addl $4, %ebp
	movl $0, %ebx       # index

print_args:
	movl (%ebp), %eax   # eax is used to temporarily store the args pointer

	pushal
	movl %esp, %ebp
	subl $12, %esp
	movl $str_args, -12(%ebp)
	movl %ebx, -8(%ebp)
	movl %eax, -4(%ebp)
	call printf
	addl $12, %esp
	popal

	inc %ebx            # ++index
	addl $4, %ebp       # next pointer
	loop print_args

exit:
	movl $1, %eax
	movl $0, %ebx
	int $0x80
