# selection sort in IA-32 assembly language

# compile command: gcc ./FILENAME.s -m32 -o ./OUT_FILENAME

.section .data
ar_size:
	.int 100
ar:
	.int -40049,10059,48014,-7533,38778,38751,-19353,-20411,-28071,-33771
	.int -16275,-43399,-25428,-47735,44031,-39762,5667,-6037,-26460,8996
	.int -41508,-23131,-1824,-15506,18304,-30363,208,-28220,20180,2251
	.int 42668,30131,-21338,-42965,-27402,-16208,-37862,19598,13381,-15933
	.int 35827,-36542,-9332,-39600,-17925,1051,-29362,37743,45014,10530
	.int 13091,-30142,-46249,-38733,20704,22056,-19096,-12736,-39812,-48916
	.int 39515,-47143,47567,-15471,-40108,-13482,18321,-27970,-43884,-1946
	.int 22449,41943,27864,-36883,-31305,-40060,30520,-10667,47683,41886
	.int -33784,10774,-38256,-30033,22042,32448,42023,-30702,-30288,-47788
	.int -13265,-24421,-28579,-15698,10108,-2335,20820,-5219,36047,26936
print_single_num:
	.asciz "%d%s"
blank_string:
	.asciz " "
newline_string:
	.asciz "\n"

.section .text
.globl main
main:
	movl $0, %esi # i = 0

	movl ar_size, %ebx # ebx = 100
	movl %ebx, %ecx
	dec %ecx # ecx = 99
	outer_loop:
		movl ar(, %esi, 4), %eax # eax = ar[i]
		
		movl %esi, %edi
		inc %edi # j = i + 1
		inner_loop:
			cmp ar(, %edi, 4), %eax
			jle pass
			xchg %eax, ar(, %edi, 4) # if(a[j] < eax) then swap
		pass:
			inc %edi
			cmp %ebx, %edi
			jne inner_loop # if new j == 100 then stop inner loop

		movl %eax, ar(, %esi, 4) # make ar[i] = eax
		inc %esi
		
		cmp %ecx, %esi
		jne outer_loop # if new i == 99 accessing ar[j] must be illegal, stop outer loop

	movl $0, %esi # indicating number index
	movl $blank_string, %edx
	print_loop:
		cmp %ecx, %esi
		jne print_loop_pass
		movl $newline_string, %edx # change the delimiter for the last number
	print_loop_pass:

		# keep key register values
		pushl %ebx
		pushl %ecx
		pushl %edx
		pushl %esi
		
		pushl %edx
		pushl ar(, %esi, 4)
		pushl $print_single_num
		call printf
		addl $12, %esp

		# restore key register values
		popl %esi
		popl %edx
		popl %ecx
		popl %ebx

		inc %esi
		cmp %ebx, %esi
		jne print_loop # exit print loop when reaching the end of ar

	movl $1, %eax
	movl $0, %ebx
	int $0x80
