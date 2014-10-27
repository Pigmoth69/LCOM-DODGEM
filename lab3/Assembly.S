#define OUT_BUFF 0X60
.global _ass_handler

.text
	_ass_handler:

	xor %al, %al
	in $OUT_BUFF, %al
	RET





