	.text
	.globl	x
	.data
	.align	4
	.type	x, @object
	.size	x, 4
x:
	.long	5

	.globl	xx
	.data
	.align	8
	.type	xx, @object
	.size	xx, 8
xx:
	.long	1
	.long	5
GerofrigoliciousTemp2:
	.long	0
GerofrigoliciousTemp1:
	.long	0
GerofrigoliciousTemp0:
	.long	0

	.section	.rodata
.LC0:
	.string	"%d\n"

	.text
	.globl	main
	.type	main, @function
main:
	.cfi_startproc
	pushq	%rbp 

	movl	4+xx(%rip), %eax
	movl	%eax	, GerofrigoliciousTemp0(%rip)

	movl	GerofrigoliciousTemp0(%rip), %eax 
	movl	%eax, x(%rip) 

.Label0:
	movl	x(%rip), %edx
	movl	$2, %eax
	cmpl	%eax, %edx
	jle	.Label1
	movl	x(%rip), %eax
	movl	$1, %ebx
	subl	%ebx, %eax
	movl	%eax, GerofrigoliciousTemp2(%rip)

	movl	GerofrigoliciousTemp2(%rip), %eax 
	movl	%eax, x(%rip) 

	jmp	.Label0
.Label1:
	movq	%rsp, %rbp
	movl	x(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

	movl	$0, %eax 
	popq	%rbp 
	ret
	.cfi_endproc

