.model small
.stack 100h

.data
	message_enter db "Iveskite zodi: $"
	new_line db 13, 10, "$"
	buffer db 255

.code

begin:  
	mov ax, @data
	mov ds, ax

	mov ah, 09h
	mov dx, offset message_enter
	int 21h

	; Nuskaitome eilute i buffer
	mov ah, 0Ah
	mov dx, offset buffer
	int 21h

	; Kad isvestis neperrasytu ivesties
	mov ah, 09h
	mov dx, offset new_line
	int 21h

	xor cx, cx
	mov cl, [buffer + 1]
	cmp cx, 00h
	je exit ; Jei neivesta nieko, programa baigia darba

	mov bx, offset buffer + 2

	convert_letters:
		mov al, [bx]
		cmp al, 'a'
		jb not_lowercase
		cmp al, 'z'
		ja not_lowercase

		sub al, 20h
		mov [bx], al
		jmp continue_loop

		not_lowercase:
			cmp al, 'A'
			jb continue_loop
			cmp al, 'Z'
			ja continue_loop
			add al, 20h
			mov [bx], al
			
		continue_loop:
			inc bx
			loop convert_letters


	; Isvedimas
	 mov dx, offset buffer + 2 
	 mov bx, 01h 
	 xor cx, cx 
	 mov cl, [buffer + 1] 
	 mov ah, 40h 
	 int 21h 
			
exit:
	mov ah, 4Ch
	int 21h

end begin