# Manipulating strings: string comparison
# to compile the code, run 
# 'gcc ./CODE_FILE_NAME.S -m32 -o ./OUTPUT_FILENAME'

.section .data
str1:
	.asciz "bbc"
str2:
	.asciz "abc"
less:
	.asciz "Src < Dest\n"
equal:
	.asciz "Src = Dest\n"
greater:
	.asciz "Src > Dest\n"

.section .bss
	.lcomm buffer, 256

.section .text
.globl main
main:
	movl $str1, %esi # source
	movl $str2, %edi # destination
	movl $3, %ecx

	# the CMPSB is like compare-byte (%edi), (%esi)
	repe cmpsb
	jl src_less_dest
	jg src_greater_dest

	pushal
	movl %esp, %ebp
	subl $4, %esp
	movl $equal, -4(%ebp)
	call printf
	addl $4, %esp
	popal
exit:
	movl $1, %eax
	movl $0, %ebx
	int $0x80

src_less_dest:
	pushal
	movl %esp, %ebp
	subl $4, %esp
	movl $less, -4(%ebp)
	call printf
	addl $4, %esp
	popal
	jmp exit

src_greater_dest:
	pushal
	movl %esp, %ebp
	subl $4, %esp
	movl $greater, -4(%ebp)
	call printf
	addl $4, %esp
	popal
	jmp exit
