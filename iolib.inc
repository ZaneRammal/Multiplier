section .data
	
	not_an_int_message: db 'Could not convert string to int, character is not an ASCII integer.', NULL

	NEWLINE EQU 10
	NULL EQU 0
	STDIN EQU 0
	STDOUT EQU 1
	SYS_READ EQU 0
	SYS_WRITE EQU 1
	SYS_EXIT EQU 60

exit:
	mov rax, SYS_EXIT
	xor rdi, rdi
	syscall

print_string:
	push rbx
	mov rbx, rdi
	xor rdx, rdx

	; Iterates through the string
	; rdx will hold the number of chars when the loop ends
	.count:
		cmp byte [rbx], NULL
		je end_count
		inc rdx
		inc rbx
		jmp .count

	end_count:
		cmp rdx, 0
		je end

	mov rax, SYS_WRITE
	mov rsi, rdi
	mov rdi, STDOUT
	syscall

	end:
		pop rbx
		ret

; prints the contents of the rax register as an integer
print_int:
	mov rcx, digitMem
	mov rbx, NEWLINE

	mov [rcx], rbx
	inc rcx
	push rcx

	; Extracts each digit by repeatedly
	; dividing by 10 and saving
	; the remainder in memory
	.division_routine:
		xor rdx, rdx
		mov rbx, 10
		div rbx

		lea rdx, [rdx + 48]
		pop rcx
		push rax

		mov [rcx], dl
		inc rcx

		pop rax
		cmp rax, 0
		push rcx
		jne .division_routine

	.print:
		pop rcx
		mov rax, SYS_WRITE
		mov rdi, STDOUT
		mov rsi, rcx
		mov rdx, 1
		push rcx
		syscall

		pop rcx
		dec rcx
		push rcx
		cmp rcx, digitMem
		jge .print
		pop rcx
		ret

; Iterates through the string and converts it to an integer
convert_to_int:
	xor rax, rax

	.convert:
		movzx rbx, byte [rdi]

		; Stop when we reach the null terminator
		test rbx, rbx
		je end_2

		; Stop and display message if not an ASCII integer
		cmp rbx, 48
		jl not_int
		cmp rbx, 57
		jg not_int

		; Convert the string to an integer
		lea rbx, [rbx - 48]
		lea rax, [rax + 8 * rax]
		lea rax, [rax + rbx]

		inc rdi
		jmp .convert
	end_2:
		ret
	not_int:
		mov rax, SYS_WRITE
		mov rsi, not_an_int_message
		mov rdi, STDOUT
		syscall
		ret
