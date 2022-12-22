.model small
.stack 100h
.386

BUFFER_SIZE EQU 512
FILENAME_SIZE EQU 30

.data  
    include opcodes.asm
    help_message db "Programa disasemblina NEG, RCL, ADC, AAM, AAD, HLT, WAIT, LOCK, CBW, CWD, ESC, ADC instrukcijas.$"
    no_instruction_found db " NEATPAZINTA", 13, 10, 0

    buffer db BUFFER_SIZE dup(?)
    filename_buffer db FILENAME_SIZE dup(?)
    output_buffer db FILENAME_SIZE dup(?)

    output_prefix db "res_"
    prefix_length dw 0

    input_fh dw 0h
    output_fh dw 0h


    hex_characters db "0123456789ABCDEF"
    converted_hex db 04h dup(?)

    read_amount dw 100h

    write_instruction_info macro count
        local @@instruction_hex
        fputs tabs
        fputs colon

        mov cx, count
        push cx

        cmp cx, 2 
        jle @@instruction_hex

        mov bl, [di + 1]
        and bl, 11000000b 
        cmp bl, 11000000b
        je @@instruction_hex

        add cx, 1
        dec di

        @@instruction_hex:
            push cx

            mov al, [di]
            call byte_to_hex
            fputs converted_hex, 02h
            fputs space

            pop cx
            inc di
            loop @@instruction_hex

        call output_line_offset
        pop cx
        dec di
        add [read_amount], cx
        sub [read_amount], 1
    endm

    fputs macro string, count
        push ax
        push bx
        push dx
        push cx

        ifdifi <dx>, <string>
            lea	dx, string
        endif

        ifdifi <count>, <>
            xor cx, cx
            mov cx, count
        else
            call strlen
        endif

        mov ax, 4000h
        mov bx, output_fh
        int 21h
        jc exit

        pop cx
        pop dx
        pop bx
        pop ax
    endm
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

        lea dx, output_prefix
        call strlen
        mov [prefix_length], cx
        lea di, output_prefix
        lea si, output_buffer
        ; movsb doesn't work :(
        copy_str:
            mov bl, [di]
            mov [si], bl
            inc di 
            inc si 

            loop copy_str

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
                
                jmp read_file

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

    lea dx, s_PUSHF
    cmp bl, 09Ch
    je eight_bit_no_offset

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
        fputs dx

        mov ax, [read_amount]

        mov bl, [di + 1]
        and bl, 10000000b 
        cmp bl, 10000000b 
        jne not_signed_disp

        signed_disp:
            movzx bx, [di + 1]
            not bx
            add bx, 1 
            sub ax, bx
            jmp disp_done 

        not_signed_disp:
            movzx bx, [di + 1]
            add ax, bx

        disp_done:
            add ax, 2

        call word_to_hex
        fputs converted_hex, 04h

        write_instruction_info 02h

        pop bx
        ret

    eight_bit_no_offset:
        fputs dx
        write_instruction_info 01h

        pop bx
    ret
check_8_bit_opcodes endp

check_7_bit_opcodes proc
    push bx

    ;;;;;;;;;;;;;;;
    ;;;;; NEG ;;;;;
    ;;;;;;;;;;;;;;;

    mov bl, [di]
    and bl, 11111110b 
    cmp bl, 11110110b 
    jne is_not_neg

    mov bl, [di + 1]
    and bl, 00111000b
    cmp bl, 00011000b 
    jne is_not_neg

    fputs s_NEG

    call output_r_m
    call get_instruction_size
    write_instruction_info cx

    pop bx 
    ret
    is_not_neg:

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;;;;; ADC AX/AL + Operand ;;;;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    mov bl, [di]
    and bl, 11111110b 
    cmp bl, 00010100b 
    jne not_7_bit 

    fputs s_ADC

    mov bl, [di]
    and bl, 00000001b 
    cmp bl, 00000001b 
    je two_byte_adc_accu

    fputs r_AL
    fputs comma

    mov al, [di + 1]
    call byte_to_hex
    fputs converted_hex, 02h

    write_instruction_info 02h

    pop bx 
    ret

    two_byte_adc_accu:

    fputs r_AX
    fputs comma

    mov al, [di + 2]
    call byte_to_hex
    fputs converted_hex, 02h 

    mov al, [di + 1]
    call byte_to_hex
    fputs converted_hex, 02h

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

    fputs s_ADC

    pop bx
    push bx
    and bl, 00000010b 
    cmp bl, 00000000b
    je first_r_m

    pop bx
    push bx
    call output_reg
    fputs comma
    pop bx
    push bx

    call output_r_m

    jmp print_adc_6_bit

    first_r_m:
            pop bx
            push bx
            call output_r_m
            fputs comma
            pop bx
            push bx

        call output_reg
    
    print_adc_6_bit:
        call get_instruction_size
        write_instruction_info cx

        pop bx
        ret

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;;;;; ADC R/M + OPERAND ;;;;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    maybe_adc_reg_mem_op:
        mov bl, [di]
        and bl, 11111100b 
        cmp bl, 10000000b 
        jne maybe_rcl

        mov bl, [di + 1]
        and bl, 00111000b
        cmp bl, 00010000b
        jne maybe_rcl

        fputs s_ADC
        call output_r_m
        fputs comma

        mov bl, [di]
        and bl, 00000011b
        cmp bl, 00000001b 
        je adc_op_16_bit

        movzx ax, [di + 2]
        call word_to_hex
        fputs converted_hex, 04h
        
        write_instruction_info 03h

        pop bx
        ret 

        adc_op_16_bit:
            mov al, [di + 3]
            call byte_to_hex
            fputs converted_hex, 02h 

            mov al, [di + 2]
            call byte_to_hex
            fputs converted_hex, 02h

            write_instruction_info 04h

            pop bx
            ret

    ;;;;;;;;;;;;;;;
    ;;;;; RCL ;;;;;
    ;;;;;;;;;;;;;;;   

    maybe_rcl:
        mov bl, [di]
        and bl, 11111100b
        cmp bl, 11010000b 
        jne not_rcl

        mov bl, [di + 1]
        and bl, 00111000b 
        cmp bl, 00010000b
        jne not_rcl

        fputs s_RCL
        call output_r_m
        fputs comma

        mov bl, [di]
        and bl, 00000010b
        cmp bl, 00000010b 
        je rcl_print_cl_reg
            
        fputs number_1
        write_instruction_info 02h
        pop bx
        ret

        rcl_print_cl_reg:
            fputs r_CL
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

    ;;;;;;;;;;;;;;;
    ;;;;; ESC ;;;;;
    ;;;;;;;;;;;;;;;

    mov bl, [di]
    and bl, 11111000b 
    cmp bl, 11011000b
    jne not_found

    fputs s_ESC

    mov al, [di]
    and al, 00000111b
    shl al, 3
    mov bl, al

    mov al, [di + 1]
    and al, 00111000b
    shr al, 3

    add al, bl
    call byte_to_hex
    fputs converted_hex, 02h
    fputs comma

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

        call output_8_bit_hex
        fputs no_instruction_found

    check_stop:
    pop bx 
ret 
check_5_bit_opcodes endp

output_reg proc

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
        fputs dx
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
        fputs bracket_left
        mov al, [di + 3]
        call byte_to_hex
        fputs converted_hex, 02h
        
        mov al, [di + 2]
        call byte_to_hex
        fputs converted_hex, 02h
        fputs bracket_right
        ret
    
    mod_01_or_10:
        pop bx
        and bl, 00000111b

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
        fputs bracket_left
        fputs dx
        fputs bracket_right

        jmp end_check
    print_out_r_m:
        fputs dx
        jmp end_check

    print_out_r_m_with_offset:
        call output_segment_register

        fputs bracket_left
        fputs dx
        fputs plus
        mov bl, [di + 1]
        and bl, 11000000b
        cmp bl, 10000000b
        je two_byte_offset

        mov al, [di + 2]
        call byte_to_hex
        fputs converted_hex, 02h
        fputs bracket_right

        ret

        two_byte_offset:
            mov al, [di + 3]
            call byte_to_hex
            fputs converted_hex, 02h

            mov al, [di + 2]
            call byte_to_hex
            fputs converted_hex, 02h
            fputs bracket_right

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
        fputs dx
        pop dx
        pop cx 
ret
output_segment_register endp

output_8_bit_hex proc
    mov al, [di]
    call byte_to_hex

    fputs converted_hex, 02h
ret
output_8_bit_hex endp

output_line_offset proc
    mov ax, [read_amount]

    mov bl, [di + 1]
    and bl, 11000000b 
    cmp bl, 11000000b
    jne no_seg_reg

    dec ax

    no_seg_reg:
    call word_to_hex

    fputs colon
    fputs converted_hex, 04h
    fputs new_line
ret
output_line_offset endp

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

strlen proc 
    push si 
    xor cx, cx
    mov si, dx 

    lodsb
    cmp al, 0
    je strlen_found

    find_length:
        inc cx
        lodsb 
        cmp al, 0
        je strlen_found

        jmp find_length 

    strlen_found:
    pop si 
ret 
strlen endp 

search_for_help proc
	mov si, 83h
    dec cx
	search_help:
        mov bl, es:[si]
		cmp bl, '?'
        jne continue_help_search
		
        mov bl, es:[si - 1]
        cmp bl, '/'
        je help

        continue_help_search:
            inc si
            loop search_help
	ret
search_for_help endp

get_file_name proc
    push ax
    push di

    xor di, di
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
        pop ax
        pop di
    	ret
	get_file_name endp
end begin