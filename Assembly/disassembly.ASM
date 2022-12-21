.model small
.stack 100h
.386

BUFFER_SIZE EQU 512
FILENAME_SIZE EQU 30

.data  
    help_message db "Programa disasemblina NEG, RCL, ADC, AAM, AAD, HALT, WAIT, LOCK, CBW, CWD, ESC, ADC instrukcijas.$"
    open_fail_message db "Nepavyko atidaryti failo!$"
    no_instruction_found db " NEATPAZINTA", 13, 10, 0
    
    include opcodes.asm

    fwrite macro file_handle, buff, buff_size
        push ax
        push bx
        push cx
        push dx

        mov	ax, 4000h
        mov bx, file_handle
        lea	dx, buff
        mov	cx, buff_size
        int	21h
        jc exit
        

        pop dx
        pop cx
        pop bx
        pop ax
    endm

    write_instruction_info macro count
        local @@output_opcodes
        fwrite output_fh, colon, 02h

        mov cx, count
        push cx

        @@output_opcodes:
            push cx

            mov al, [di]
            call byte_to_hex
            fwrite output_fh, [converted_hex], 02h
            fwrite output_fh, space, 01h

            pop cx
            inc di
            loop @@output_opcodes

        call print_line_offset
        pop cx
        dec di
        add [read_amount], cx
        sub [read_amount], 1
    endm
    
    buffer db BUFFER_SIZE dup(?)
    filename_buffer db FILENAME_SIZE dup(?)
    output_buffer db FILENAME_SIZE dup(?)
    input_fh dw 0h
    output_fh dw 0h

    hex_characters db "0123456789ABCDEF"
    converted_hex db 4 dup (?)
    read_amount dw 100h

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

		mov si, 82h
		disassemble_files:
			call get_file_name
			push si

            ;Open input file
            mov ah, 3Dh
            mov al, 00
            lea dx, filename_buffer
            int 21h
            jc exit
            mov input_fh, ax

            ;Create output file
            mov ah, 3Ch
            lea dx, output_buffer
            xor cx, cx
            int 21h
            jc exit
            mov output_fh, ax

            read_file:
                ; Read
                mov ax, 3f00h
                mov bx, input_fh
                mov cx, BUFFER_SIZE
                lea dx, buffer
                int 21h
                jc exit

                lea di, buffer

                ; Check read character amount
                cmp ax, 0
                je stop_read
                mov cx, ax

                read_buffer:
                    mov bl, [di]

                    push cx
                    call check_8_bit_opcodes
                    pop cx
                    
                continue_buffer:
                    inc di
                    add [read_amount], 1
                    loop read_buffer

            stop_read:
                ; Close current input file
                mov ax, 3e00h
                mov bx, input_fh
                int 21h
                jc exit

                ; Close current input file
                mov ax, 3e00h
                mov bx, output_fh
                int 21h
                jc exit

                pop si
                mov dl, es:[si]

                ; If end of string is reached, stop searching for filenames
                cmp dl, 13
                je exit
                cmp dl, 0
                je exit

                jmp disassemble_files

        help:
            mov ah, 09h
            lea dx, help_message
            int 21h

        exit:
            mov ah, 4Ch
            xor al, al
            int 21h

check_8_bit_opcodes proc
    push bx

    mov cx, 06h 
    lea dx, s_PUSHF
    cmp bl, 09Ch
    je eight_bit_no_offset

    ;;;;;;;;;;;
    mov cx, 05h ; WAIT, LOCK, HALT, POPF, JCXZ, XLAT
    ;;;;;;;;;;;

    lea dx, s_POPF
    cmp bl, 09Dh 
    je eight_bit_no_offset

    lea dx, s_WAIT
    cmp bl, 09Bh
    je eight_bit_no_offset

    lea dx, s_LOCK
    cmp bl, 0F0h
    je eight_bit_no_offset

    lea dx, s_JCXZ
    cmp bl, 0E3h
    je output_jump

    lea dx, s_XLAT
    cmp bl, 0D7h
    je eight_bit_no_offset


    ;;;;;;;;;;;
    mov cx, 04h ; AAM AND AAD
    ;;;;;;;;;;;

    lea dx, s_HLT
    cmp bl, 0F4h
    je eight_bit_no_offset

    lea dx, s_AAM
    cmp bl, 0D4h
    jne not_aam

    inc di
    mov bl, [di]
    cmp bl, 0Ah
    je eight_bit_no_offset

    dec di
    mov bl, [di]
    not_aam:

    lea dx, s_AAD
    cmp bl, 0D5h
    jne not_aad

    inc di
    mov bl, [di]
    cmp bl, 0Ah
    je eight_bit_no_offset

    dec di
    mov bl, [di]

    not_aad:

    lea dx, s_JNO ; Jump not overflow
    cmp bl, 071h
    je output_jump

    lea dx, s_JNC
    cmp bl, 073h
    je output_jump

    lea dx, s_JNE
    cmp bl, 075h
    je output_jump

    lea dx, s_JNA
    cmp bl, 076h
    je output_jump

    lea dx, s_JNS ; Jump not sign
    cmp bl, 079h
    je output_jump

    lea dx, s_JNP ; Jump not parity
    cmp bl, 07Bh
    je output_jump

    lea dx, s_JNL
    cmp bl, 07Dh
    je output_jump

    lea dx, s_JLE ; Jump less or equal
    cmp bl, 07Eh
    je output_jump

    lea dx, s_CBW
    cmp bl, 098h
    je output_jump

    lea dx, s_CWD
    cmp bl, 099h
    je output_jump

    ;;;;;;;;;;;
    mov cx, 03h ; Will be 2 char long instructions
    ;;;;;;;;;;;

    lea dx, s_JO ; Jump overflow
    cmp bl, 070h
    je output_jump

    lea dx, s_JC
    cmp bl, 072h
    je output_jump

    lea dx, s_JE
    cmp bl, 074h
    je output_jump

    lea dx, s_JA
    cmp bl, 077h
    je output_jump

    lea dx, s_JS ; Jump sign
    cmp bl, 078h
    je output_jump

    lea dx, s_JP ; Jump parity
    cmp bl, 07Ah
    je output_jump

    lea dx, s_JL
    cmp bl, 07Ch
    je output_jump

    lea dx, s_JG ; Jump greater
    cmp bl, 07Fh
    je output_jump

    pop bx
    call check_7_bit_opcodes
    ret

    output_jump:
        call print_opcode

        mov ax, [read_amount]
        add al, [di + 1]
        add al, 2

        call word_to_hex
        fwrite output_fh, [converted_hex], 04h

        write_instruction_info 02h

        pop bx
        ret

    eight_bit_no_offset:
        call print_opcode
        write_instruction_info 01h

        pop bx
    ret
check_8_bit_opcodes endp

check_7_bit_opcodes proc
    push bx

    ;;;;;;;;;;;;;;;;;;;;;;;;;
    ;;;;; Check for NEG ;;;;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;

    mov bl, [di]
    and bl, 11111110b 
    cmp bl, 11110110b 
    jne is_not_neg

    mov bl, [di + 1]
    and bl, 00111000b
    cmp bl, 00011000b 
    jne is_not_neg

    fwrite output_fh, s_NEG, 04h

    call output_r_m
    call get_instruction_size
    write_instruction_info cx

    pop bx 
    ret
    is_not_neg:

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;;;;; ADC Accumulator + Operand ;;;;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    mov bl, [di]
    and bl, 11111110b 
    cmp bl, 00010100b 
    jne not_7_bit 

    fwrite output_fh, s_ADC, 04h

    mov bl, [di]
    and bl, 00000001b 
    cmp bl, 00000001b 
    je two_byte_adc_accu

    fwrite output_fh, r_AL, 02h
    fwrite output_fh, comma, 02h

    mov al, [di + 1]
    call byte_to_hex
    fwrite output_fh, [converted_hex], 02h 

    write_instruction_info 02h

    pop bx 
    ret

    two_byte_adc_accu:

    fwrite output_fh, r_AX, 02h
    fwrite output_fh, comma, 02h

    mov al, [di + 2]
    call byte_to_hex
    fwrite output_fh, [converted_hex], 02h 

    mov al, [di + 1]
    call byte_to_hex
    fwrite output_fh, [converted_hex], 02h 

    write_instruction_info 03h

    pop bx 
    ret

    not_7_bit:
    pop bx
    call check_6_bit_opcodes
ret
check_7_bit_opcodes endp

check_6_bit_opcodes proc
    push bx

    ;;;;;;;;;;;;;;;;;;;;;;;;;
    ;;;;; ADC REG + R/M ;;;;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;

    and bl, 11111100b 
    cmp bl, 00010000b
    jne maybe_adc_reg_mem_op

    fwrite output_fh, s_ADC, 04h

    pop bx
    push bx
    and bl, 00000010b 
    cmp bl, 00000000b
    je first_r_m

    pop bx
    push bx
    call output_reg
    fwrite output_fh, comma, 02h
    pop bx
    push bx

    call output_r_m

    jmp print_adc_6_bit

    first_r_m:
            pop bx
            push bx
            call output_r_m
            fwrite output_fh, comma, 02h
            pop bx
            push bx

        call output_reg
    
    print_adc_6_bit:
        call get_instruction_size
        write_instruction_info cx

        pop bx
        ret

    maybe_adc_reg_mem_op:
        mov bl, [di]
        and bl, 11111100b 
        cmp bl, 10000000b 
        jne maybe_rcl

        mov bl, [di + 1]
        and bl, 00111000b
        cmp bl, 00010000b
        jne maybe_rcl

        fwrite output_fh, s_ADC, 04h 
        call output_r_m
        fwrite output_fh, comma, 02h

        mov bl, [di]
        and bl, 00000011b
        cmp bl, 00000001b 
        je adc_op_16_bit

        mov al, [di + 2]
        call byte_to_hex
        fwrite output_fh, [converted_hex], 02h
        
        write_instruction_info 03h

        pop bx
        ret 

        adc_op_16_bit:
            mov al, [di + 3]
            call byte_to_hex
            fwrite output_fh, [converted_hex], 02h 

            mov al, [di + 2]
            call byte_to_hex
            fwrite output_fh, [converted_hex], 02h

            write_instruction_info 04h

            pop bx
            ret            
    maybe_rcl:
        mov bl, [di]
        and bl, 11111100b
        cmp bl, 11010000b 
        jne not_rcl

        mov bl, [di + 1]
        and bl, 00111000b 
        cmp bl, 00010000b
        jne not_rcl

        fwrite output_fh, s_RCL, 04h 
        call output_r_m
        fwrite output_fh, comma, 02h 

        mov bl, [di]
        and bl, 00000010b
        cmp bl, 00000010b 
        je rcl_print_cl_reg
            
        fwrite output_fh, number_1, 01h
        write_instruction_info 02h
        pop bx
        ret

        rcl_print_cl_reg:
            fwrite output_fh, r_CL, 02h 
            write_instruction_info 02h
            pop bx
            ret


        not_rcl:
        pop bx
        call check_5_bit_opcodes
ret
check_6_bit_opcodes endp

check_5_bit_opcodes proc
    push bx 

    mov bl, [di]
    and bl, 11111000b 
    cmp bl, 11011000b
    jne not_found

    fwrite output_fh, s_ESC, 04h

    mov al, [di]
    and al, 00000111b
    shl al, 3
    mov bl, al

    mov al, [di + 1]
    and al, 00111000b
    shr al, 3

    add al, bl
    call byte_to_hex
    fwrite output_fh, [converted_hex], 02h
    fwrite output_fh, comma, 02h

    call output_r_m

    write_instruction_info 02h

    pop bx
    ret

    not_found:
        mov bl, [di]
        cmp bl, 26h
        je check_stop
        cmp bl, 02Eh
        je check_stop
        cmp bl, 036h
        je check_stop

        call print_part_of_opcode
        fwrite output_fh, no_instruction_found, 0Eh

    check_stop:
    pop bx 
ret 
check_5_bit_opcodes endp

output_reg proc
    mov cx, 02h 

    and bl, 00000001b
    cmp bl, 00000001b
    jne reg_w_0

    reg_w_1:
        mov bl, [di + 1]
        and bl, 00111000b

        lea dx, r_AX
        cmp bl, 00000000b
        je output_register

        lea dx, r_CX
        cmp bl, 00001000b
        je output_register

        lea dx, r_DX
        cmp bl, 00010000b
        je output_register

        lea dx, r_BX
        cmp bl, 00011000b 
        je output_register

        lea dx, r_SP
        cmp bl, 00100000b 
        je output_register

        lea dx, r_BP
        cmp bl, 00101000b 
        je output_register

        lea dx, r_SI
        cmp bl, 00110000b 
        je output_register

        lea dx, r_DI
        jmp output_register

    reg_w_0:
        mov bl, [di + 1]
        and bl, 00111000b

        lea dx, r_AL
        cmp bl, 00000000b
        je output_register

        lea dx, r_CL
        cmp bl, 00001000b
        je output_register

        lea dx, r_DL
        cmp bl, 00010000b
        je output_register

        lea dx, r_BL
        cmp bl, 00011000b 
        je output_register

        lea dx, r_AH
        cmp bl, 00100000b 
        je output_register

        lea dx, r_CH
        cmp bl, 00101000b 
        je output_register

        lea dx, r_DH
        cmp bl, 00110000b 
        je output_register

        lea dx, r_BH
        jmp output_register

    output_register:
        call print_opcode
ret
output_reg endp

output_r_m proc
    mov bl, [di + 1]
    push bx
    
    and bl, 11000000b
    cmp bl, 00000000b
    je mod_00

    cmp bl, 11000000b
    jne mod_01_or_10

    mov bl, [di]
    and bl, 00000001b
    cmp bl, 00000000b
    je mod_11_0

    jmp mod_11_1

    mod_11_0:
        pop bx
        and bl, 00000111b
        mov cx, 02h

        lea dx, r_AL
        cmp bl, 00000000b
        je print_out_r_m

        lea dx, r_CL
        cmp bl, 00000001b
        je print_out_r_m

        lea dx, r_DL
        cmp bl, 00000010b
        je print_out_r_m

        lea dx, r_BL
        cmp bl, 00000011b
        je print_out_r_m

        lea dx, r_AH
        cmp bl, 00000100b
        je print_out_r_m

        lea dx, r_CH
        cmp bl, 00000101b
        je print_out_r_m

        lea dx, r_DH
        cmp bl, 00000110b
        je print_out_r_m

        lea dx, r_BH
        jmp print_out_r_m

    mod_11_1:
        pop bx
        and bl, 00000111b
        mov cx, 02h

        lea dx, r_AX
        cmp bl, 00000000b
        je print_out_r_m

        lea dx, r_CX
        cmp bl, 00000001b
        je print_out_r_m

        lea dx, r_DX
        cmp bl, 00000010b
        je print_out_r_m

        lea dx, r_BX
        cmp bl, 00000011b
        je print_out_r_m

        lea dx, r_SP
        cmp bl, 00000100b
        je print_out_r_m

        lea dx, r_BP
        cmp bl, 00000101b
        je print_out_r_m

        lea dx, r_SI
        cmp bl, 00000110b
        je print_out_r_m

        lea dx, r_DI
        jmp print_out_r_m

    mod_00:
        pop bx
        and bl, 00000111b

        mov cx, 07h
        lea dx, r_BX_SI
        cmp bl, 00000000b
        je print_only_adress

        lea dx, r_BX_DI
        cmp bl, 00000001b
        je print_only_adress

        lea dx, r_BX_SI
        cmp bl, 00000010b
        je print_only_adress

        lea dx, r_BP_DI
        cmp bl, 00000011b
        je print_only_adress

        mov cx, 02h
        lea dx, r_SI
        cmp bl, 00000100b
        je print_only_adress

        lea dx, r_DI
        cmp bl, 00000101b
        je print_only_adress

        lea dx, r_BX
        cmp bl, 00000111b
        je print_only_adress

        ; SPECIAL CASE
        call output_segment_register
        add di, 2
        fwrite output_fh, bracket_left, 01h
        call print_part_of_opcode
        fwrite output_fh, bracket_right, 01h
        sub di, 2
        ret
    
    mod_01_or_10:
        pop bx
        and bl, 00000111b
        mov cx, 07h

        lea dx, r_BX_SI
        cmp bl, 00000000b
        je print_out_r_m_with_offset

        lea dx, r_BX_DI
        cmp bl, 00000001b
        je print_out_r_m_with_offset

        lea dx, r_BP_SI
        cmp bl, 00000010b
        je print_out_r_m_with_offset

        lea dx, r_BP_DI
        cmp bl, 00000011b
        je print_out_r_m_with_offset

        mov cx, 02h
        lea dx, r_SI
        cmp bl, 00000100b
        je print_out_r_m_with_offset

        lea dx, r_DI
        cmp bl, 00000101b
        je print_out_r_m_with_offset

        lea dx, r_BP
        cmp bl, 00000110b
        je print_out_r_m_with_offset

        lea dx, r_BX
        jmp print_out_r_m_with_offset

    print_only_adress:
        call output_segment_register
        fwrite output_fh, bracket_left, 01h
        call print_opcode
        fwrite output_fh, bracket_right, 01h

        jmp end_check
    print_out_r_m:
        call print_opcode
        jmp end_check

    print_out_r_m_with_offset:
        call output_segment_register

        fwrite output_fh, bracket_left, 01h
        call print_opcode
        fwrite output_fh, plus, 03h
        mov bl, [di + 1]
        and bl, 11000000b
        cmp bl, 10000000b
        je two_byte_offset

        mov al, [di + 2]
        call byte_to_hex
        fwrite output_fh, [converted_hex], 02h
        fwrite output_fh, bracket_right, 01h

        ret

        two_byte_offset:
            mov al, [di + 3]
            call byte_to_hex
            fwrite output_fh, [converted_hex], 02h

            mov al, [di + 2]
            call byte_to_hex
            fwrite output_fh, [converted_hex], 02h
            fwrite output_fh, bracket_right, 01h

         ret
    end_check:
ret
output_r_m endp

get_instruction_size proc
    mov cx, 04h

    mov bl, [di + 1]
    and bl, 11000000b
    cmp bl, 10000000b
    je size_found

    
    mov cx, 03h
    cmp bl, 01000000b
    je size_found

    mov cx, 04h 

    mov bl, [di + 1]
    and bl, 00000111b
    cmp bl, 00000110b
    je size_found

    mov cx, 02h 

    size_found:
ret
get_instruction_size endp

output_segment_register proc
    push cx
    push dx

    mov cx, 03h
    mov bl, [di - 1]

    lea dx, r_ES
    cmp bl, 26h
    je print_seg_reg

    lea dx, r_CS
    cmp bl, 02Eh
    je print_seg_reg

    lea dx, r_SS
    cmp bl, 036h
    je print_seg_reg

    pop dx
    pop cx
    ret

    print_seg_reg:
        call print_opcode  
        pop dx
        pop cx 
ret
output_segment_register endp

print_part_of_opcode proc
    mov al, [di]
    call byte_to_hex

    fwrite output_fh, [converted_hex], 02h
ret
print_part_of_opcode endp

print_line_offset proc
    mov ax, [read_amount]
    call word_to_hex

    fwrite output_fh, colon, 02h
    fwrite output_fh, [converted_hex], 04h
    fwrite output_fh, new_line, 02h
ret
print_line_offset endp

print_opcode proc
    push ax
    push bx

    mov ax, 4000h
    mov bx, output_fh
    int 21h
    jc exit

    pop bx
    pop ax
ret
print_opcode endp

byte_to_hex proc
	mov	ah, al
	and	al, 0Fh
	lea	bx, [hex_characters]
	xlatb
	mov	[converted_hex + 1], al
	shr	ax, 12
	xlatb
	mov	[converted_hex], al
ret
byte_to_hex endp

word_to_hex proc
	mov	dx, ax
	mov	ah, al
	and	al, 0Fh
	lea	bx, [hex_characters]
	xlatb
	mov	[converted_hex + 3], al
	shr	ax, 12
	xlatb
	mov	[converted_hex + 2], al
	mov	al, dh
	mov	ah, dh
	and	al, 0Fh
	lea	bx, [hex_characters]
	xlatb
	mov	[converted_hex + 1], al
	shr	ax, 12
	xlatb
	mov	[converted_hex], al
	ret
word_to_hex endp

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
    push di
    mov di, 0 
    mov output_buffer[0], 'r'
    mov output_buffer[1], 'e'
    mov output_buffer[2], 's'
    mov output_buffer[3], '_'

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
        mov output_buffer[di + 4], dl

		inc si
		inc di
		jmp get_letters

	word_found:
        pop di
    	ret
	get_file_name endp
end begin