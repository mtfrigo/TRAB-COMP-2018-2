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
	.long	7

	.globl	c
	.data
	.align	4
	.type	c, @object
	.size	c, 4
c:
	.long	2

GerofrigoliciousTemp6:
	.long	0
GerofrigoliciousTemp2:
	.long	0
GerofrigoliciousTemp9:
	.long	0
GerofrigoliciousTemp5:
	.long	0
GerofrigoliciousTemp1:
	.long	0
GerofrigoliciousTemp8:
	.long	0
GerofrigoliciousTemp4:
	.long	0
GerofrigoliciousTemp0:
	.long	0
GerofrigoliciousTemp7:
	.long	0
GerofrigoliciousTemp3:
	.long	0
GerofrigoliciousTemp10:
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
	.string	"Xis maior que 5"

.LC1:
	.string	"Xis menor que 5"

.LC2:

.LC3:

.LC4:
	.string	"Valor de c:"

.LC5:

.LC6:

.LC7:

.LC8:

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

	movl	x(%rip), %edx
	movl	$5, %eax
	cmpl	%eax, %edx
	jle	.Label0
	leaq	.LC0(%rip), %rdi
	call	puts@PLT

	jmp	.Label1
.Label0:
	leaq	.LC1(%rip), %rdi
	call	puts@PLT

.Label1:
.Label2:
	movl	x(%rip), %edx
	movl	$0, %eax
	cmpl	%eax, %edx
	jle	.Label3
	movl	x(%rip), %eax
	movl	$1, %ebx
	subl	%ebx, %eax
	movl	%eax, GerofrigoliciousTemp4(%rip)

	movl	GerofrigoliciousTemp4(%rip), %eax 
	movl	%eax, x(%rip) 

	movl	x(%rip), %eax
	movl	%eax, %esi
	leaq	.printInt(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

	jmp	.Label2
.Label3:
	movl	$5, %esi
	movl	$10, %edi
	call	ff
	movl	%eax, GerofrigoliciousTemp5(%rip)

	movl	GerofrigoliciousTemp5(%rip), %eax 
	movl	%eax, c(%rip) 

	leaq	.LC4(%rip), %rdi
	call	puts@PLT

	movl	c(%rip), %eax
	movl	%eax, %esi
	leaq	.printInt(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

	movb	$121, 3+xx(%rip) 

	movl	0+xx(%rip), %eax
	movl	%eax	, GerofrigoliciousTemp9(%rip)

	movzbl	GerofrigoliciousTemp9(%rip), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.printChar(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

	movl	1+xx(%rip), %eax
	movl	%eax	, GerofrigoliciousTemp8(%rip)

	movzbl	GerofrigoliciousTemp8(%rip), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.printChar(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

	movl	2+xx(%rip), %eax
	movl	%eax	, GerofrigoliciousTemp7(%rip)

	movzbl	GerofrigoliciousTemp7(%rip), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.printChar(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

	movl	3+xx(%rip), %eax
	movl	%eax	, GerofrigoliciousTemp6(%rip)

	movzbl	GerofrigoliciousTemp6(%rip), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.printChar(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

	movl	$1, %eax 

	popq	%rbp 
	ret
	.cfi_endproc

