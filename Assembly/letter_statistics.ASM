.model small
.386
.stack 100h

buff_size EQU 512
letter_amount EQU 26

.data
	help_message db "Iveskite failu pavadinimus, rezultatu faile output.txt bus atspausdinta raidziu statistika.$"
	new_line db 13, 10
	space db 20h
	statistics_symbol db 23h
	input db "input2.txt", 0h
	output db "output.txt", 0h
	input_fh dw 0h
	output_fh dw 0h
	buffer db buff_size dup(?)
	filename_buffer db buff_size dup(?)
	letters db letter_amount dup(0)

.code
	begin:
		mov ax, @data
		mov ds, ax

		; Check if any arguments were entered
		xor cx, cx
		mov cl, es:[80h]
		cmp cl, 0
		je help

		call search_for_help

		;Create output file
		mov ah, 3Ch
		mov dx, offset output
		xor cx, cx
		int 21h
		jc exit
		mov output_fh, ax
		
		mov si, 82h
		get_file_statistics:
			call get_file_name
			push si

			;Open input file
			mov ah, 3Dh
			mov al, 00
			mov dx, offset filename_buffer
			int 21h
			jc exit
			mov input_fh, ax

			read_file:
				; Read
				mov ax, 3f00h
				mov bx, input_fh
				mov cx, 30
				lea dx, buffer
				int 21h
				jc exit

				lea di, buffer

				; Check read character amount
				cmp ax, 0
				je next_file
				mov cx, ax

				; Get statistics of current file
				call increment_counters
				jmp read_file

		next_file:
			; Close current input file
			push ax
			mov ax, 3e00h
			mov bx, input_fh
			int 21h

			pop ax

			pop si
			mov dl, es:[si]

			; If end of string is reached, stop searching for filenames
			cmp dl, 13
			je end_read
			cmp dl, 0
			je end_read
			
			jmp get_file_statistics

		end_read: 
			call find_largest_number

			xor cx, cx
			mov cl, dl
			cmp cl, 0
			je exit

			top_to_bottom: ; Loop through largest number to get top-down statistics
				lea di, letters
				je top_to_bottom
				push cx

				call output_statistics

				push dx

				mov ax, 4000h
				mov cx, 01h
				mov bx, output_fh
				lea dx, new_line
				int 21h
				jc exit

				pop dx
				pop cx
				dec dl ; Decrement largest number!!!
				loop top_to_bottom


			; Close output file
			mov ax, 3e00h
			mov bx, output_fh
			int 21h

			jmp exit

			help:
				mov ah, 09h
				lea dx, help_message
				int 21h

			exit:
				mov ah, 4Ch
				xor al, al
				int 21h
				
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;; Procedures ;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

search_for_help proc
	mov bx, 82h
	search_help:
		cmp es:[bx], '?/'
		je help

		inc bx
		loop search_help
	ret
search_for_help endp

get_file_name proc
    mov di, 0 

	clear_spaces:
		mov dl, es:[si]
		cmp dl, 32
		jne get_letters

		inc si
		jmp clear_spaces

    get_letters:
		mov dl, es:[si]
		
		cmp dl, 32 ; Space
		je word_found
		cmp dl, 13 ; Carriage Return
		je word_found
		cmp dl, 0 ; End of String
		je word_found
		mov filename_buffer[di], dl

		inc si
		inc di
		jmp get_letters

	word_found:
    	ret
		
	get_file_name endp

increment_counters proc
	read_buffer:
		mov dl, [di]
		cmp dl, 'A'
		jb next_char
		cmp dl, 'Z'
		ja is_lowercase

		jmp convert

		is_lowercase:
			cmp dl, 'a'
			jb next_char
			cmp dl, 'z'
			ja next_char
			sub dl, 20h

		convert:
			sub dl, 65
			mov si, dx
			mov dl, [letters + si]
			inc dl
			mov [letters + si], dl

		next_char:
			inc di
			loop read_buffer
	ret
increment_counters endp

find_largest_number proc
	lea di, letters
	mov dl, [di]
	inc di

	xor cx, cx
	mov cl, 25
	find_max:
		cmp [di], dl
		jb continue_max_search
		mov dl, [di]

		continue_max_search:
			inc di
			loop find_max
	ret
find_largest_number endp

output_statistics proc
	xor cx, cx
	mov cl, letter_amount
	check_counters: ; Print statistics left-right
		push cx
		cmp [di], dl
		jne write_space

		push dx
		mov dl, [di]
		dec dl
		mov [di], dl

		mov ax, 4000h
		mov cx, 01h
		mov bx, output_fh
		lea dx, statistics_symbol
		int 21h
		jc exit

		jmp check_next_counter

		write_space:
			push dx

			mov ax, 4000h
			mov cx, 01h
			mov bx, output_fh
			lea dx, space
			int 21h
			jc exit
		
		check_next_counter:
			pop dx
			pop cx
			inc di
			loop check_counters
	ret
output_statistics endp
end begin