	.file	"ex.c"
	.text
	.globl	s
	.data
	.type	s, @object
	.size	s, 1
s:
	.byte	115
	.comm	ss,2,1
	.globl	sss
	.type	sss, @object
	.size	sss, 2
sss:
	.byte	99
	.byte	103
	.globl	x
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	2
	.comm	xx,8,8
	.globl	xxx
	.align 8
	.type	xxx, @object
	.size	xxx, 8
xxx:
	.long	2
	.long	3
	.globl	g
	.align 4
	.type	g, @object
	.size	g, 4
g:
	.long	3
	.globl	gg
	.type	gg, @object
	.size	gg, 1
gg:
	.byte	99
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movb	$99, s(%rip)
	movb	$104, 1+ss(%rip)
	movb	$107, 2+ss(%rip)
	movzbl	gg(%rip), %eax
	movb	%al, s(%rip)
	movzbl	gg(%rip), %eax
	movb	%al, 1+ss(%rip)
	movzbl	gg(%rip), %eax
	movb	%al, 2+ss(%rip)
	movl	$3, x(%rip)
	movl	$5, 4+xx(%rip)
	movl	$7, 20+xxx(%rip)
	movl	g(%rip), %eax
	movl	%eax, x(%rip)
	movl	g(%rip), %eax
	movl	%eax, 4+xx(%rip)
	movl	g(%rip), %eax
	movl	%eax, 20+xxx(%rip)
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.3.0-16ubuntu3) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
