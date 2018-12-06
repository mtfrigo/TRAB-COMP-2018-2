	.globl	s
	.data
	.type	s, @object
	.size	s, 1
s:
	.byte	115

	.comm	ss, 2, 1
	.globl	sss
	.data
	.align	8
	.type	sss, @object
	.size	sss, 2
sss:
	.byte	99
	.byte	103
	.globl	x
	.data
	.align	4
	.type	x, @object
	.size	x, 4
x:
	.long	2

	.comm	xx, 8, 8
	.globl	xxx
	.data
	.align	8
	.type	xxx, @object
	.size	xxx, 8
xxx:
	.long	2
	.long	3
	.globl	g
	.data
	.align	4
	.type	g, @object
	.size	g, 4
g:
	.long	3

	.globl	gg
	.data
	.type	gg, @object
	.size	gg, 1
gg:
	.byte	103

	.section	.rodata

	.globl	main
	.type	main, @function
main:
	.cfi_startproc
	pushq	%rbp 

	movb	$99, s(%rip) 

	movb	$104, 1+ss(%rip) 

	movb	$107, 2+ss(%rip) 

	movzbl	$gg(%rip), %eax 
	movl	%al, s(%rip) 

	movzbl	$gg(%rip), %eax 
	movl	%eax, 1+ss(%rip) 

	movzbl	$gg(%rip), %eax 
	movl	%eax, 2+ss(%rip) 

	movl	$3, x(%rip) 

	movl	$5, 4+xx(%rip) 

	movl	$7, 20+xxx(%rip) 

	movl	$g(%rip), %eax 
	movl	%eax, x(%rip) 

	movl	$g(%rip), %eax 
	movl	%eax, 4+xx(%rip) 

	movl	$g(%rip), %eax 
	movl	%eax, 20+xxx(%rip) 

	movl	$0, %eax 
	popq	%rbp 
	ret
	.cfi_endproc

