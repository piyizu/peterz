# Manipulating strings: upper to lower
# to compile the code, run 
# 'gcc ./CODE_FILE_NAME.S -m32 -o ./OUTPUT_FILENAME'

.section .data
str_test:
	.asciz "Oh! Hello and weLCOMe to SynBAy's Program!\n"
.section .bss
	.lcomm buffer, 256

.section .text
.globl main
main:
	leal str_test, %esi
	movl %esi, %edi
	movl $44, %ecx  # the total length (including 0 at the end) is 44 (bytes)

convert_chars:
	lodsb
	cmp $'A', %al
	jl skip
	cmp $'Z', %al
	jg skip
	addb $0x20, %al    # add 0x20 to the uppercase letter to convert it to the lowercase
skip:
	stosb
	loop convert_chars

print_str:
	pushal
	movl %esp, %ebp
	subl $4, %esp
	movl $str_test, -4(%ebp)
	call printf
	addl $4, %esp
	popal
exit:
	movl $1, %eax
	movl $0, %ebx
	int $0x80
