.model small
.stack 100h

.data
    message db "Hello, World!$"

.code
    begin: 
        mov ax, @data
        mov ds, ax

        mov ah, 09h
        mov dx, offset message
        int 21h

        mov ah, 4Ch
        int 21h
    end begin
