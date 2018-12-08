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
GerofrigoliciousTemp3:
	.long	0

l:
	.long	0
a:
	.long	0
	.section	.rodata
.LC0:
	.string	"%d\n"

	.text
	.globl	ff
	.type	ff, @function
ff:
	.cfi_startproc
	pushq	%rbp 
	movq	%rsp, %rbp

	movl	%edi, a(%rip)
	movl	%esi, l(%rip)
	movl	a(%rip), %eax
	movl	l(%rip), %ebx
	addl	%ebx, %eax
	movl	%eax, GerofrigoliciousTemp0(%rip)

	movl	GerofrigoliciousTemp0(%rip), %eax 
	movl	%eax, x(%rip) 

	movl	x(%rip), %eax 

	popq	%rbp 
	ret
	.cfi_endproc

	.globl	main
	.type	main, @function
main:
	.cfi_startproc
	pushq	%rbp 
	movq	%rsp, %rbp

	movl	$55, %esi
	movl	$1, %edi
	call	ff
	movl	%eax, GerofrigoliciousTemp2(%rip)

	movl	GerofrigoliciousTemp2(%rip), %eax 
	movl	%eax, x(%rip) 

	movl	x(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

	movl	$1, %eax 

	popq	%rbp 
	ret
	.cfi_endproc

