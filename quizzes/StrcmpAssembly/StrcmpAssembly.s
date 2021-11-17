Strcmp:
	mov 0 R6
loop:
	cmp byte[R1] 0x00
	jeq while
	MOV byte[R1] R0
	sub byre[R2] R0
	ret R0 
while:
	cmp byte[R1] 0x00
	jeq no
	cmp byte[R1] byte[R2]
	jne no
	add 8 R1
	add 8 R2
	goto while  
no:
	ret
