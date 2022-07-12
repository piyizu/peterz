# Using functions: leap year test
# to compile the code, run 
# 'gcc ./CODE_FILE_NAME.S -m32 -o ./OUTPUT_FILENAME'

.section .data
str_prompt:
	.asciz "Enter the year:\n"
str_format:
	.asciz "%u"
str_leap_year:
	.asciz "The year %u is a leap year.\n"
str_not_leap_year:
	.asciz "The year %u is not a leap year.\n"

.section .bss
	.lcomm input_year, 4
	.lcomm result, 4

.section .text

.type is_leap_year, @function
.globl is_leap_year       # if you don't want the function globly visible, comment it
is_leap_year:
	pushl %ebp
	movl %esp, %ebp
	subl $12, %esp
	
	# Now the stack is like:
	# dword year_to_test
	# dword return_address
	# dword old_ebp  (%ebp)
	# dword can_be_evenly_divided_by_4
	# dword can_be_evenly_divided_by_100
	# dword can_be_evenly_divided_by_400 (%esp)

	# get year mod 4
	movl 8(%ebp), %eax
	xor %edx, %edx
	movl $4, %ebx   # ebx contains a temporary value
	divl %ebx
	movl %edx, -4(%ebp)

	# get year mod 100
	movl 8(%ebp), %eax
	xor %edx, %edx
	movl $100, %ebx
	divl %ebx
	movl %edx, -8(%ebp)

	# get year mod 400
	movl 8(%ebp), %eax
	xor %edx, %edx
	movl $400, %ebx
	divl %ebx
	movl %edx, -12(%ebp)

	xor %eax, %eax   # eax contains the return value
	movl $1, %ebx    

	cmpl $0, -8(%ebp)
	je even100
		# the year mod 100 is not zero, then test if it is evenly divided by 4
		cmpl $0, -4(%ebp)
		cmove %ebx, %eax

leave_is_leap_year:
	addl $12, %esp
	popl %ebp
	ret

	even100:
		# the year mod 100 is zero, then test if it is evenly divided by 400
		cmpl $0, -12(%ebp)
		cmove %ebx, %eax
		jmp leave_is_leap_year

.globl main
main:
	# print: Enter the year
	pushal
	movl %esp, %ebp
	subl $4, %esp
	movl $str_prompt, -4(%ebp)
	call printf
	addl $4, %esp
	popal

	# get: input_year
	pushal
	movl %esp, %ebp
	subl $8, %esp
	movl $str_format, -8(%ebp)
	movl $input_year, -4(%ebp)
	call scanf
	addl $8, %esp
	popal

	pushal
	movl %esp, %ebp
	subl $4, %esp
	movl input_year, %eax
	movl %eax, -4(%ebp)
	call is_leap_year
	movl %eax, result   # keep the return value
	addl $4, %esp
	popal

	movl result, %eax
	and %eax, %eax
	jnz print_is_leap_year

	# the year is not a leap year, which is more possible
	pushal
	movl %esp, %ebp
	subl $8, %esp
	movl input_year, %eax
	movl %eax, -4(%ebp)
	movl $str_not_leap_year, -8(%ebp)
	call printf
	addl $8, %esp
	popal

exit:
	movl $1, %eax
	movl $0, %ebx
	int $0x80

print_is_leap_year:
	pushal
	movl %esp, %ebp
	subl $8, %esp
	movl input_year, %eax
	movl %eax, -4(%ebp)
	movl $str_leap_year, -8(%ebp)
	call printf
	addl $8, %esp
	popal
	jmp exit
