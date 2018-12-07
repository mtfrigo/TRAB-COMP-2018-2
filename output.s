	.text
	.globl	x
	.data
	.align	4
	.type	x, @object
	.size	x, 4
x:
	.long	3

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

	movl	$50, %eax
	movl	$5, %ebx
	addl	%ebx, %eax
	movl	%eax, GerofrigoliciousTemp0(%rip)

	movl	GerofrigoliciousTemp0(%rip), %eax 
	movl	%eax, x(%rip) 

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

