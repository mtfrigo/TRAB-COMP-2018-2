	.globl	GerofrigoliciousTemp2
	.data
	.align	4
	.size	GerofrigoliciousTemp2, 4
GerofrigoliciousTemp2:
	.zero	4
	.globl	GerofrigoliciousTemp1
	.data
	.align	4
	.size	GerofrigoliciousTemp1, 4
GerofrigoliciousTemp1:
	.zero	4
	.globl	GerofrigoliciousTemp4
	.data
	.align	4
	.size	GerofrigoliciousTemp4, 4
GerofrigoliciousTemp4:
	.zero	4
	.globl	GerofrigoliciousTemp0
	.data
	.align	4
	.size	GerofrigoliciousTemp0, 4
GerofrigoliciousTemp0:
	.zero	4
	.globl	GerofrigoliciousTemp3
	.data
	.align	4
	.size	GerofrigoliciousTemp3, 4
GerofrigoliciousTemp3:
	.zero	4
	popq	%rbp
	ret
	movl	$2, %eax
	popq	%rbp
	ret
.PINT:
	.string	"%d\n"
.RINT:
	.string	"%d"
.PCHAR:
	.string	"%c\n"
	popq	%rbp
	ret
