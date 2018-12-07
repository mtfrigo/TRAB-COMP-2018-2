	.text
	.globl	x
	.data
	.align	4
	.type	x, @object
	.size	x, 4
x:
	.long	3

	.globl	c
	.data
	.type	c, @object
	.size	c, 1
c:
	.byte	99

	.section	.rodata
.LC0:
	.string	"asdasd"

.LC1:
	.string	"%c\n"

.LC2:
	.string	"%d\n"

	.text
	.globl	main
	.type	main, @function
main:
	.cfi_startproc
	pushq	%rbp 

	movq	%rsp, %rbp
	movl	x(%rip), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

	movq	%rsp, %rbp
	movzbl	c(%rip), %eax
	movsbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT

	movq	%rsp, %rbp
	leaq	.LC0(%rip), %rdi
	call	puts@PLT

	movl	$0, %eax 
	popq	%rbp 
	ret
	.cfi_endproc

