;; @module multiplier
;; Takes two integers as command line arguments.
;; The integers are multiplied together and printed
;; to the screen.

%include "iolib.inc"

extern atoi

section .data
	WRONG_ARGS_TEXT: db 'Wrong number of arguments. The program requires exactly two integers.' , NULL

section .bss
	digitMem: resb 100
	rcxMem: resb 8

section .text
	global _start

_start:
	; End with message if there are not two arguments
	pop rcx
	cmp rcx, 3
	jne enderr

	lea rsp, [rsp + 8]

	; get first argument
	pop rsi
	mov rdi, rsi
	call convert_to_int
	mov r8, rax
	call print_int

	; get second argument
	pop rdx
	mov rdi, rdx
	call convert_to_int
	mov rbx, rax
	mov r9, rax
	call print_int

	; multiply them together
	mov rax, r8
	mul r9

	call print_int
	call exit

	enderr:
		mov rdi, WRONG_ARGS_TEXT
		call print_string
		call exit
