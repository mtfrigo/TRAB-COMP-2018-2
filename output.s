	.text
	.globl	xx
	.data
	.align	16
	.type	xx, @object
	.size	xx, 4
xx:
	.byte	97
	.byte	110
	.byte	99
	.byte	109
	.globl	x
	.data
	.align	4
	.type	x, @object
	.size	x, 4
x:
	.long	5

	.globl	c
	.data
	.align	4
	.type	c, @object
	.size	c, 4
c:
	.long	2

GerofrigoliciousTemp2:
	.long	0
GerofrigoliciousTemp1:
	.long	0
GerofrigoliciousTemp0:
	.long	0
GerofrigoliciousTemp3:
	.long	0

lal:
	.long	0
lol:
	.long	0
	.section	.rodata

.printChar:
	.string "%c\n"
.printInt:
	.string "%d\n"
.printFloat:
	.string "%f\n"
.LC0:

	.text
	.globl	ff
	.type	ff, @function
ff:
	.cfi_startproc
	pushq	%rbp 
	movq	%rsp, %rbp

	movl	%edi, lol(%rip)
	movl	%esi, lal(%rip)
	movl	lol(%rip), %eax
	movl	lal(%rip), %ebx
	cltd
	idivl	%ebx
	movl	%eax, GerofrigoliciousTemp0(%rip)

	movl	GerofrigoliciousTemp0(%rip), %eax 

	popq	%rbp 
	ret
	.cfi_endproc

	.globl	main
	.type	main, @function
main:
	.cfi_startproc
	pushq	%rbp 
	movq	%rsp, %rbp

	movl	c(%rip), %esi
	movl	x(%rip), %edi
	call	ff
	movl	%eax, GerofrigoliciousTemp2(%rip)

	movl	GerofrigoliciousTemp2(%rip), %eax 
	movl	%eax, x(%rip) 

	movl	x(%rip), %eax
	movl	%eax, %esi
	leaq	.printInt(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

	movl	$1, %eax 

	popq	%rbp 
	ret
	.cfi_endproc

