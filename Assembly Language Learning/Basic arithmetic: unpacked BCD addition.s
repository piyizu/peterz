# An example of unpacked BCD arithmetic
# To compile: gcc ./FILENAME.s -m32 -o ./OUT_FILENAME

.section .data
num_a:
	.byte 9, 4, 5, 6, 7, 3, 2, 6, 9 # 962376549
num_b:
	.byte 9, 9, 9, 5, 3, 4, 2, 9, 0 # 92435999
res_output:
	.asciz "%d"
new_line:
	.ascii "\n"

.section .bss
	.lcomm res, 10

.section .text
.globl main
main:
	movl $0, %edi
	movl $9, %ecx
	clc

	loop_add:
		movb num_a(, %edi, 1), %al
		adcb num_b(, %edi, 1), %al # remember to perform additions with carry
		aaa # adjust AL after addition
		movb %al, res(, %edi, 1)
		inc %edi
		loop loop_add

	movb $0, %al
	adcb $0, %al # The result may be one digit longer than the longest oprand
	aaa
	movb %al, res(, %edi, 1)

	loop_out: # print the result digit from the highest to the lowest
		pushal

		movl %esp, %ebp
		subl $8, %esp
		xorl %eax, %eax
		movb res(, %edi, 1), %al
		movl %eax, -4(%ebp)
		movl $res_output, -8(%ebp)
		call printf
		addl $8, %esp

		# We need fflush(FILE *stream) to help us correctly print those numbers
		movl %esp, %ebp
		subl $4, %esp
		movl $0, -4(%ebp) # NULL as the argument to flush all output streams
		call fflush
		addl $4, %esp

		popal

		subl $1, %edi
		jns loop_out
	
	# Here we call linux system interrupt to print a newline character
	movl $4, %eax # write
	movl $1, %ebx # standard output
	movl $new_line, %ecx # source location
	movl $1, %edx # how many bytes
	int $0x80

exit:
	movl $1, %eax
	movl $0, %ebx
	int $0x80
