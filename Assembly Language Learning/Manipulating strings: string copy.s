# Manipulating strings: string copy
# to compile the code, run 
# 'gcc ./CODE_FILE_NAME.S -m32 -o ./OUTPUT_FILENAME'

.section .data
original:
	.asciz "Hello, my dear friend!\n"
str_counter:
	.asciz "Number of moved bytes: %d\n"

.section .bss
	.lcomm buffer, 256

.section .text
.globl main
main:
	leal original, %esi
	leal buffer, %edi
	xor %eax, %eax
	xor %ecx, %ecx

	cld  # clear DF so that esi and edi increase, to set DF use STD
string_copy:
	movb (%esi), %al
	
	# move one byte from (%esi) to (%edi) and then increase/decrease esi and edi
	movsb
	
	inc %ecx
	test %al, %al
	jnz string_copy # loop until (%esi) steps on '\0'
print_new_string:
	pushal
	movl %esp, %ebp
	subl $4, %esp
	movl $buffer, -4(%ebp)
	call printf
	addl $4, %esp
	popal
print_num_of_moved_bytes:
	pushal
	movl %esp, %ebp
	subl $8, %esp
	movl $str_counter, -8(%ebp)
	movl %ecx, -4(%ebp)
	call printf
	addl $8, %esp
	popal
exit:
	movl $1, %eax
	movl $0, %ebx
	int $0x80
