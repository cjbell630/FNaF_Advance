.arm
.text

.global vbaprint
.type   vbaprint STT_FUNC
vbaprint:
	swi 0xFF0000
	bx lr