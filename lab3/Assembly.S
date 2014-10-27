
.text
	_KBD_HANDLER_ASS:

	movl %0,%ebx
	movl %0, %eax

	IN OUT_BUF,%ebx
	RET





