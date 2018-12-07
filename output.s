	.text
	.globl	x
	.data
	.align	4
	.type	x, @object
	.size	x, 4
x:
	.long	3

	.globl	xx
	.data
	.align	4
	.type	xx, @object
	.size	xx, 4
xx:
	.long	2

GerofrigoliciousTemp0:
	.long	0

	.section	.rodata
	.text
	.globl	main
	.type	main, @function
main:
	.cfi_startproc
	pushq	%rbp 

	movl	$0, x(%rip) 

	movl	$0, %eax 
	popq	%rbp 
	ret
	.cfi_endproc

