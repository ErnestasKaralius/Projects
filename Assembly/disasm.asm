; ----------------------------------------------------------------------
; Disasm v. 1.0.0  Copyright (c) 1999 Marius Gedminas <mgedmin@delfi.lt>
; This program is Free Software.  See file COPYING for details.
; ----------------------------------------------------------------------

; $Id: disasm.asm,v 1.7 2002/10/20 17:50:29 mg Exp $

ideal
locals	@@
jumps

USE_BUFFERED_IO	equ	1

; ----------------------------------------------------------------------
; Define segments
; ----------------------------------------------------------------------

segment	cseg 'code'
ends

segment sseg stack 'stack'
		db	2048 dup (?)
ends

segment dseg 'data'
ends

segment bss uninit 'data'
ends

segment bss2 uninit 'data2'
ends

group dgroup dseg, bss

macro code_seg
	ends
	segment cseg
endm

macro data_seg
	ends
	segment dseg
endm

macro udata_seg
	ends
	segment bss
endm

macro udata2_seg
	ends
	segment bss2
endm

segment cseg
assume	cs: cseg, ds: nothing, es: nothing, ss: sseg

; ----------------------------------------------------------------------
; Utilities 
; ----------------------------------------------------------------------

; Hex conversion
; ----------------------------------------------------------------------

	data_seg

HexChars	db	'0123456789ABCDEF'

	udata_seg

HexValue	db	4 dup (?)

	code_seg

	assume	ds: dgroup

proc	hexbyte
; In:		al = value
; Out:		first two bytes of HexValue filled.
; Destroyed:	ax, bx

	mov	ah, al
	and	al, 0Fh
	lea	bx, [HexChars]
	xlatb
	mov	[HexValue+1], al
	shr	ax, 12
	xlatb
	mov	[HexValue], al
	ret
endp

proc	hexword
; In:		ax = value
; Out:		first two bytes of HexValue filled.
; Destroyed:	ax, bx, dx

	mov	dx, ax
	mov	ah, al
	and	al, 0Fh
	lea	bx, [HexChars]
	xlatb
	mov	[HexValue+3], al
	shr	ax, 12
	xlatb
	mov	[HexValue+2], al
	mov	al, dh
	mov	ah, dh
	and	al, 0Fh
	lea	bx, [HexChars]
	xlatb
	mov	[HexValue+1], al
	shr	ax, 12
	xlatb
	mov	[HexValue], al
	ret
endp

; Text I/O
; ----------------------------------------------------------------------

proc	strlen
; In:		ds:bx -> string (ASCIIZ)
; Out:		cx == length of string
; 		bx -> end of string	
		xor	cx, cx
		cmp	[byte bx], 0
		jz	short @@2
@@1:		inc	cx
		inc	bx
		cmp	[byte bx], 0
		jnz	@@1
@@2:
		ret
endp

proc	printz
; In:		ds:bx -> string (ASCIIZ)
; Out:		bx -> end of string (null byte)
; Destroyed:	al

		mov	al, [bx]
		or	al, al
		jz	@@2
@@1:		int	29h		; Print char in AL (undocummented)
		inc	bx
		mov	al, [bx]
		or	al, al
		jnz	@@1
@@2:
		ret
endp

macro	print	str
; Destroyed:	al, bx
		lea	bx, [str]
		call	printz
endm

macro	prints	str
; In:		ds => data segment
; Destroyed:	al, bx
; Warning: probably assumes dseg is first segment in dgroup
	data_seg
@msg_pos	=	$
		db	str, 0
	code_seg
		lea	bx, [@msg_pos]
		call	printz
endm

; File I/O
; ----------------------------------------------------------------------

assume	ds: nothing, es: nothing

macro	fopen	fname, mode
; destroys AX, DX
; returns handle in AX
; carry flag set on error
		mov	ah, 3Dh
                mov	dx, offset fname
                mov	al, mode
                int	21h
endm

macro	fcreate	fname, attr
; destroys AX, CX, DX
; returns handle in AX
; carry flag set on error
		mov	ah, 3Ch
                mov	dx, offset fname
                mov	cx, attr
                int	21h
endm

macro	fclose	handle
; destroys AX, BX
; carry flag set on error
		mov	ah, 3Eh
                mov	bx, handle
                int	21h
endm

macro	fread	handle, buf, bufsize
; destroys AX, BX, CX DX
; returns number of bytes read in AX
; carry flag set on error
		mov	ah, 3Fh
                mov	bx, handle
ifdifi <dx>,<buf>		
                lea	dx, buf
endif		
ifdifi <cx>,<bufsize>		
                mov	cx, bufsize
endif		
                int	21h
endm

macro	fwrite	handle, buf, bufsize
; destroys AX, BX, CX, DX
; returns number of bytes written in AX
; carry flag set on error
		mov	ah, 40h
                mov	bx, handle
ifdifi <dx>,<buf>		
                lea	dx, buf
endif		
ifdifi <cx>,<bufsize>		
                mov	cx, bufsize
endif		
                int	21h
endm

macro	fprint	handle, str
; In:		ds => data segment
; Destroyed:	ax, bx, cx, dx
ifdifi <bx>,<str>
		mov	bx, str
endif		
ifdifi <dx>,<str>
		mov	dx, bx
endif		
		call	strlen
		fwrite	handle, dx, cx
endm

macro	fprints	handle, str
; In:		ds => data segment
; Destroyed:	ax, bx, cx, dx
; Warning: probably assumes dseg is first segment in dgroup
	data_seg
@msg_pos	=	$
		db	str
@msg_size	=	($ - @msg_pos)
	code_seg
		fwrite	handle, [@msg_pos], @msg_size
endm

macro	fhexb	handle, num
; In:		ds => data segment
; Destroyed:	ax, bx, cx, dx
ifdifi	<num>,<al>
		mov	al, num
endif
		call	hexbyte
		fwrite	handle, [HexValue], 2
endm

macro	fhexw	handle, num
; In:		ds => data segment
; Destroyed:	ax, bx, cx, dx
ifdifi	<num>,<ax>
		mov	ax, num
endif
		call	hexword
		fwrite	handle, [HexValue], 4
endm

; Process control
; ----------------------------------------------------------------------
macro	quit	exitcode
		mov	ax, 4C00h + exitcode
		int	21h
endm

; ----------------------------------------------------------------------
; Instruction table
; ----------------------------------------------------------------------

	data_seg

; Argument types
argNone		equ	0
; Fixed arguments
argConst1	equ	1	; constant `1' as in `shl  ax,1'
argConst3	equ	2	; constant `3' as in `int  3'
argRegAL	equ	3	; 8-bit registers
argRegCL	equ	4
argRegDL	equ	5
argRegBL	equ	6
argRegAH	equ	7
argRegCH	equ	8
argRegDH	equ	9
argRegBH	equ	10
argRegAX	equ	11	; 16-bit registers
argRegCX	equ	12
argRegDX	equ	13
argRegBX	equ	14
argRegSP	equ	15
argRegBP	equ	16
argRegSI	equ	17
argRegDI	equ	18
argRegES	equ	19	; segment registers
argRegCS	equ	20
argRegSS	equ	21
argRegDS	equ	22
arg_FixedEnd	equ	22
; Immediate/displacement arguments (w/o addr-mode byte)
argImm8		equ	34	; 8-bit immediate
argSImm8	equ	35	; signed 8-bit immediate (extended to 16-bit)
argImm16	equ	36	; 16-bit immediate
argMemOffs8	equ	37	; 16-bit memory offset to 8-bit data
argMemOffs16	equ	38	; 16-bit memory offset to 16-bit data
argShort	equ	39	; 8-bit relative address
argNear		equ	40	; 16-bit relative address
argFar		equ	41	; 32-bit absolute address
; Arguments, requiring addr-mode byte
arg_AddrMode_Start	equ	42
argRegMem8	equ	42	; 8-bit register/memory
argRegMem16	equ	43	; 16-bit register/memory 
argMem8		equ	44	; 8-bit memory reference
argMem16	equ	45	; 16-bit memory reference
argMem32	equ	46	; 32-bit memory reference
argReg8		equ	47	; 8-bit secondary register
argReg16	equ	48	; 16-bit secondary register
argSegReg	equ	49	; secondary segment register

; Kinds
kNormal		equ	0
kPrefix		equ	1	; lock/repX/segXX
; others are automatically generated
kGroupStart	equ	2

; Arguments as strings
s_Const1	db	'1', 0
s_Const3	db	'3', 0
s_RegAL		db	'al', 0	; 8-bit registers
s_RegCL		db	'cl', 0
s_RegDL		db	'dl', 0
s_RegBL		db	'bl', 0
s_RegAH		db	'ah', 0
s_RegCH		db	'ch', 0
s_RegDH		db	'dh', 0
s_RegBH		db	'bh', 0
s_RegAX		db	'ax', 0	; 16-bit registers
s_RegCX		db	'cx', 0
s_RegDX		db	'dx', 0
s_RegBX		db	'bx', 0
s_RegSP		db	'sp', 0
s_RegBP		db	'bp', 0
s_RegSI		db	'si', 0
s_RegDI		db	'di', 0
s_RegES		db	'es', 0	; segment registers
s_RegCS		db	'cs', 0
s_RegSS		db	'ss', 0
s_RegDS		db	'ds', 0
; Addressing modes
s_ModeBX_SI	db	'bx+si', 0
s_ModeBX_DI	db	'bx+di', 0
s_ModeBP_SI	db	'bp+si', 0
s_ModeBP_DI	db	'bp+di', 0
s_ModeSI	equ	s_RegSI
s_ModeDI	equ	s_RegDI
s_ModeBP	equ	s_RegBP
s_ModeBX	equ	s_RegBX

; Arrays
label	sa_FixedArgs	word
		dw	s_Const1, s_Const3
label	sa_8bitRegs	word
		dw	s_RegAL, s_RegCL, s_RegDL, s_RegBL
		dw	s_RegAH, s_RegCH, s_RegDH, s_RegBH
label	sa_16bitRegs	word
		dw	s_RegAX, s_RegCX, s_RegDX, s_RegBX
		dw	s_RegSP, s_RegBP, s_RegSI, s_RegDI
label	sa_SegRegs	word
		dw	s_RegES, s_RegCS, s_RegSS, s_RegDS
		
label	sa_Addrs	word
		dw	s_ModeBX_SI, s_ModeBX_DI, s_ModeBP_SI, s_ModeBP_DI
		dw	s_ModeSI, s_ModeDI, s_ModeBP, s_ModeBX

struc		TOpcodeData
Mnemonic	dw	0
Kind		db	kNormal
Arg1		db	argNone
Arg2		db	argNone
ends

LabelPrefix	equ	'l'

include	"opcodes.asm"

; Flags
flCodeLabel	=	01h	; Someone references this location
flCode		=	02h	; Instruction starts here
flCodeCont	=	04h	; Instruction continues here
flBadCode	=	08h	; Don't disassemble this (e.g. label inside).
flGap		=	10h	; Unreachable sequentially (e.g. after RET).
flDataLabel	=	20h	; Someone references this location

flPartOfCode	=	(flCode + flCodeCont + flBadCode)
flLabel		=	(flCodeLabel + flDataLabel)

; ----------------------------------------------------------------------
; Disassembling core
; ----------------------------------------------------------------------

	udata_seg

; Pointers
ofPrefix	dw	?	; start of instruction
ofOpcode	dw	?	; opcode
ofMode		dw	?	; addressing mode byte
ofOffset	dw	?	; displacement
ofData		dw	?	; immediate data

ofSegPrefix	dw	?	; segment prefix (if any)

; Sizes
szPrefix	dw	?	
;szOpcode	equ	1	; always
szMode		dw	?	; 0 or 1
szOffset	dw	?	; 0, 1 or 2
szData		dw	?	; 0, 1 or 2
;szInsn		dw	?	; = szPrefix + 1 + szMode + szOffset + szData

; Decoded data
Mnemonic	dw	?
SegPrefix	db	?
Arg1		db	?
Arg2		db	?

; Source buffer
MaxBufSize	equ	0F000h	; = 60 kb
Buffer		db	MaxBufSize dup (?)
BufSize		dw	?

	udata2_seg

Flags		db	MaxBufSize dup (?)
		db	?	; and one more
	
; ----------------------------------------------------------------------

	code_seg
	assume	cs: cseg, ds: dgroup

; ----------------------------------------------------------------------

macro	LocateOpcode
; In:		ds => data segment
;		al == opcode
; Out:		bx -> Opcodes[al] (== offset Opcodes + al * SIZE TOpcodeData)
; Destroyed:	ax

		mov	ah, SIZE TOpcodeData
		lea	bx, [Opcodes]
		mul	ah
		add	bx, ax
endm

; ----------------------------------------------------------------------

proc	DecodeInsn
; In:		ds => data segment	
;		si -> index in buffer
; Out:		si -> next opcode
;               szPrefix, szMode, szOffset, szData
;		ofPrefix, ofOpcode, ofMode, ofOffset, ofData
;		SegPrefix, Mnemonic, Arg1, Arg2
; Destroyed:	ax bx di

		xor	ax, ax		; ax == 0
		mov	[szPrefix], ax
		mov	[szMode], ax
		mov	[szOffset], ax
		mov	[szData], ax

		mov	[SegPrefix], -1

		mov	[ofPrefix], si	; si -> current location in buffer
@@PrefixLoop:	mov	al, [Buffer + si]	; al == opcode
		LocateOpcode		; bx -> Opcodes[al]; ax destroyed
		cmp	[(TOpcodeData bx).Kind], kPrefix
		jne	@@NotPrefix
		; prefix
		mov	al, [Buffer + si]	; al == opcode
		and	al, 0E7h
		cmp	al, 026h
		jne	@@NotSegPrefix
		; segment prefix
		mov	al, [Buffer + si]	; al == opcode
		shr	al, 3
		and	al, 3
		mov	[SegPrefix], al
		mov	[ofSegPrefix], si
@@NotSegPrefix:	inc	[szPrefix]
		inc	si
		jmp	short @@PrefixLoop
		; Risky -- what if segment is full of prefix bytes only?
		; could deadlock; should add some limits
		
		; ------------------------------------------------------

@@DoF6:		
		mov	al, [Buffer + si]	; al == addr mode byte
		shr	al, 3
		and	al, 7
		jnz	@@HaveAddrMode
		; TEST	r/m8, imm8
		mov	[Arg2], argImm8
		jmp	@@HaveAddrMode
		
@@DoF7:		
		mov	al, [Buffer + si]	; al == addr mode byte
		shr	al, 3
		and	al, 7
		jnz	@@HaveAddrMode
		; TEST	r/m16, imm16
		mov	[Arg2], argImm16
		jmp	@@HaveAddrMode
		
@@DoFF:		; si -> addressing mode byte in buffer
		mov	al, [Buffer + si]	; al == addr mode byte
		shr	al, 3
		and	al, 7
		cmp	al, 3		; CALL	DWORD PTR mem32 
		je	@@ReallyDoFF
		cmp	al, 5		; JMP	DWORD PTR mem32
		jne	@@HaveAddrMode
@@ReallyDoFF:	mov	[Arg1], argMem32
		jmp	@@HaveAddrMode
		
		; ------------------------------------------------------
		
@@NotPrefix:	; al destroyed
		; bx -> Opcodes[<opcode>]
		; si -> opcode in buffer
		; filled in: SegPrefix, ofPrefix, szPrefix

		mov	al, [(TOpcodeData bx).Arg1]
		mov	ah, [(TOpcodeData bx).Arg2]
		mov	[Arg1], al
		mov	[Arg2], ah

		mov	[ofOpcode], si
		inc	si
		mov	[ofMode], si
		
		; filled in: ofOpcode, ofMode
		
		mov	al, [(TOpcodeData bx).Kind]
					; al == Kind
		cmp	al, kNormal
		je	@@Normal
		; Special
		xor	ah, ah		; ah == 0
		sub	al, kGroupStart	; al == Kind - kGroupStart
		lea	di, [Groups]
		add	di, ax
		add	di, ax		; di -> Groups[Kind-kGroupStart]
		mov	di, [di]	; di -> sa_<Group>
		mov	al, [Buffer + si]	; al == addr mode byte
		shr	al, 3
		and	al, 7		; al == secondary opcode
		add	di, ax
		add	di, ax		; di -> sa_<Group>[al]
		mov	ax, [di]	; ax == Groups[Kind][AddrMode >> 3 & 7]
		
		mov	[Mnemonic], ax
		mov	al, [(TOpcodeData bx).Arg1]
		mov	ah, [(TOpcodeData bx).Arg2]
		mov	[Arg1], al
		mov	[Arg2], ah
		
		mov	al, [Buffer + si-1]
		cmp	al, 0F6h
		je	@@DoF6
		cmp	al, 0F7h
		je	@@DoF7
		cmp	al, 0FFh
		je	@@DoFF
	
		jmp	short @@HaveAddrMode

@@Normal:	; al == kNormal
		; bx -> Opcodes[<opcode>]
		; si -> addr-mode in buffer
		
		mov	ax, [(TOpcodeData bx).Mnemonic]
		mov	[Mnemonic], ax

		mov	al, [(TOpcodeData bx).Arg1]
		mov	ah, [(TOpcodeData bx).Arg2]
		mov	[Arg1], al
		mov	[Arg2], ah
		cmp     al, arg_AddrMode_Start	
		jae	@@HaveAddrMode
		cmp     ah, arg_AddrMode_Start	
		jnae	@@CheckAddr

@@HaveAddrMode:	; ax destroyed
		; bx -> Opcodes[<opcode>]
		; si -> addr-mode in buffer
		; di destroyed
		; filled in: Mnemonic, Arg1, Arg2
		
		mov	[szMode], 1
		mov	al, [Buffer + si]	; al == addr mode byte
		inc	si		; si -> offset
		mov	[ofOffset], si
		shr	al, 6		; al == addressing mode
		cmp	al, 1
		je	@@8bitOffs
		cmp	al, 2
		je	@@16bitOffs
		cmp	al, 0
		jne	@@CheckAddr
		; al == 0
		mov	al, [Buffer + si-1]	; al == addr mode byte
		and	al, 7
		cmp	al, 6
		jne	@@CheckAddr
		; fall through
@@16bitOffs:
		mov	[szOffset], 2
		add	si, 2
		jmp	short @@CheckData

@@8bitOffs:
		mov	[szOffset], 1
		inc	si
		jmp	short @@CheckData

@@CheckAddr:	; ax destroyed
		; bx -> Opcodes[<opcode>]
		; si -> offset in buffer
		; di destroyed
		; filled in: Mnemonic, Arg1, Arg2, szMode

		mov	[ofOffset], si
		cmp	[Arg1], argShort
		je	@@8bitOffs
		cmp	[Arg2], argShort
		je	@@8bitOffs
		
		cmp	[Arg1], argNear
		je	@@16bitOffs
		cmp	[Arg2], argNear
		je	@@16bitOffs
		cmp	[Arg1], argMemOffs8
		je	@@16bitOffs
		cmp	[Arg2], argMemOffs8
		je	@@16bitOffs
		cmp	[Arg1], argMemOffs16
		je	@@16bitOffs
		cmp	[Arg2], argMemOffs16
		je	@@16bitOffs
		
		cmp	[Arg1], argFar
		je	@@32bitOffs
		cmp	[Arg2], argFar
		jne	@@CheckData
@@32bitOffs:
		mov	[szOffset], 4
		add	si, 4

@@CheckData:	; ax destroyed
		; bx -> Opcodes[<opcode>]
		; si -> data in buffer
		; filled in: ofOffset, szOffset

		mov	[ofData], si
		; filled in: ofData

		cmp	[Arg1], argImm8
		je	@@8bitData
		cmp	[Arg2], argImm8
		je	@@8bitData
		cmp	[Arg1], argSImm8
		je	@@8bitData
		cmp	[Arg2], argSImm8
		je	@@8bitData
		cmp	[Arg1], argImm16
		je	@@16bitData
		cmp	[Arg2], argImm16
		jne	@@Done

@@16bitData:	mov	[szData], 2
		add	si, 2
		jmp	short @@Done

@@8bitData:	mov	[szData], 1
		inc	si
		jmp	short @@Done

@@Done:		; filled in: szData
		ret
endp	DecodeInsn

proc	BreakInsn
; In:		es => bss2 segment
;		di -> index in buffer
; Out:		Flags modified

		push	di
@@Loop:
		dec	di
		test	[byte es:Flags + di], (flCode + flBadCode)
		jz	@@Loop
		and	[byte es:Flags + di], not flCode
		or	[byte es:Flags + di], flBadCode
		
		pop	di
		ret
endp

proc	Trace
; In:		ds => data segment
;		es => bss2 segment
;		si -> index in buffer
; Out:		si -> next opcode
;		Flags modified
; Destroyed:    szPrefix, szMode, szOffset, szData
;		ofPrefix, ofOpcode, ofMode, ofOffset, ofData
;		SegPrefix, Mnemonic, Arg1, Arg2
; 		ax bx di
		
@@Loop:
		cmp	si, [BufSize]
		jae	@@DoneHere
		test	[byte es:Flags + si], flPartOfCode
		jnz	@@DoneHere
		call	DecodeInsn
		cmp	si, [BufSize]
		ja	@@DoneHere	; not full opcode
		cmp	[Mnemonic], 0
		jnz	@@OpcodeOk
@@InvalidOpcode:
		; invalid opcode
		mov	si, [ofOpcode]
		inc	si
		jmp	short @@Loop
@@OpcodeOk:
		cmp	[Arg1], argMem8
		jb	@@CheckArg2
		cmp	[Arg1], argMem32
		jbe	@@RequireMemArg
@@CheckArg2:
		cmp	[Arg2], argMem8
		jb	@@NoMemArg
		cmp	[Arg2], argMem32
		ja	@@NoMemArg
@@RequireMemArg:
		mov	bx, [ofMode]
		mov	al, [Buffer + bx]
		shr	al, 6
		cmp	al, 3
		je	@@InvalidOpcode

@@NoMemArg:
		mov	bx, [ofPrefix]
		or	[byte es:Flags + bx], flCode
		inc	bx
		cmp	bx, si
		jae	@@FinishedMarking
@@DoMarking:	
		test	[byte es:Flags + bx], (flCodeLabel + flCode)
		jz	@@NothingInside
		push	bx
		mov	bx, [ofPrefix]
		and	[byte es:Flags + bx], not flCode
		or	[byte es:Flags + bx], flBadCode
		pop	bx
@@NothingInside:
		and	[byte es:Flags + bx], not flDataLabel
		or	[byte es:Flags + bx], flCodeCont
		inc	bx
		cmp	bx, si
		jb	@@DoMarking
@@FinishedMarking:
		; verify individual opcodes
		
		cmp	[SegPrefix], 0
		jge	@@NoDataLabels
		cmp	[Arg1], argMemOffs8 
		je	@@DataLabel
		cmp	[Arg2], argMemOffs8
		je	@@DataLabel
		cmp	[Arg1], argMemOffs16 
		je	@@DataLabel
		cmp	[Arg2], argMemOffs16
		je	@@DataLabel
		cmp	[szMode], 0
		jz	@@NoDataLabels
		mov	bx, [ofMode]
		mov	al, [Buffer + bx]
		mov	ah, al
		shr	al, 6
		cmp	al, 0
		jne	@@NoDataLabels
		mov	al, ah
		and	al, 7
		cmp	al, 6
		jne	@@NoDataLabels
@@DataLabel:
		mov	bx, [ofOffset]
		mov	bx, [word Buffer + bx]
		sub	bx, 100h
		cmp	bx, [BufSize]
		ja	@@NoDataLabels
		test	[byte es:Flags + bx], flPartOfCode
		jnz	@@NoDataLabels	; Assume no self-modifying code
		or	[byte es:Flags + bx], flDataLabel
		
@@NoDataLabels:
		; jXX, jmp short, loop 
		mov	bx, [ofOpcode]
		cmp	[byte Buffer + bx], 70h
		jb	@@NotJmpShort
		cmp	[byte Buffer + bx], 7Fh
		jbe	@@JmpShort
		cmp	[byte Buffer + bx], 0E0h
		jb	@@NotJmpShort
		cmp	[byte Buffer + bx], 0E3h
		jbe	@@JmpShort
		cmp	[byte Buffer + bx], 0EBh
		je	@@JmpShortWithGap
@@NotJmpShort:
		; jmp near, call near
		cmp	[byte Buffer + bx], 0E8h
		je	@@JmpNear
		cmp	[byte Buffer + bx], 0E9h
		je	@@JmpNearWithGap
		; call far
		cmp	[byte Buffer + bx], 09Ah
		je	@@JmpFar
		; jmp far
		cmp	[byte Buffer + bx], 0EAh
		je	@@JmpFarWithGap
		; ret, iret
		cmp	[byte Buffer + bx], 0C2h
		je	@@JustGap
		cmp	[byte Buffer + bx], 0C3h
		je	@@JustGap
		cmp	[byte Buffer + bx], 0CAh
		je	@@JustGap
		cmp	[byte Buffer + bx], 0CBh
		je	@@JustGap
		cmp	[byte Buffer + bx], 0CFh
		je	@@JustGap
		; jmp [...]
		cmp	[byte Buffer + bx], 0FFh
		jne	@@Loop
		mov	bx, [ofMode]
		mov	al, [Buffer + bx]
		shr	al, 3
		and	al, 7
		cmp	al, 4
		jb	@@Loop
		cmp	al, 5
		ja	@@Loop
@@JustGap:
		or	[es:Flags + si], flGap
		jmp	@@DoneHere

		; ------------------------------------------------------

@@JmpShortWithGap:
		or	[es:Flags + si], flGap
@@JmpShort:
		mov	bx, [ofOffset]
		mov	al, [Buffer + bx]
		cbw
		mov	di, si
		add	di, ax
		jmp	@@SetCodeLabel		

		; ------------------------------------------------------

@@JmpNearWithGap:
		or	[es:Flags + si], flGap
@@JmpNear:
		mov	bx, [ofOffset]
		mov	ax, [word Buffer + bx]
		mov	di, si
		add	di, ax
		jmp	@@SetCodeLabel		
		
		; ------------------------------------------------------

@@SetCodeLabel:
		; di -> destination
		cmp	di, [BufSize]
		ja	@@BreakCur
		test	[byte es:Flags + di], flCodeCont
		jz	@@NoBreaking
		call	BreakInsn
@@NoBreaking:
		or	[byte es:Flags + di], flCodeLabel
		push	si
		mov	si, di
		call	Trace
		pop	si
		test	[byte es:Flags + si], flGap
		jnz	@@DoneHere
		jmp	@@Loop

		; ------------------------------------------------------

@@JmpFarWithGap:
		or	[es:Flags + si], flGap
@@JmpFar:
@@BreakCur:
		mov	bx, [ofPrefix]
		and	[byte es:Flags + bx], not flCode
		or	[byte es:Flags + bx], flBadCode
		test	[byte es:Flags + si], flGap
		jz	@@Loop

@@DoneHere:
		ret
endp

; ----------------------------------------------------------------------
; Main
; ----------------------------------------------------------------------

	udata_seg

InFName		db	127 dup (?)
OutFName	db	127 dup (?)

InFile		dw	?
OutFile		dw	?

Scratch		db	?

PrevWasData	db	?

; PSP:
CmdLineLen	equ	80h
CmdLine		equ	81h

; Output buffer
MaxOutBufSize	equ	1024
OutBufThreshold	equ	MaxOutBufSize - 100
			; Assume no line will be longer than 100 characters
OutBuf		db	MaxOutBufSize dup (?)
	
	data_seg

OutBufSize	dw	0
Column		db	0

	code_seg

; ----------------------------------------------------------------------
; Output routines
; ----------------------------------------------------------------------

if USE_BUFFERED_IO

; --- Buffered I/O ---

macro	do_write
local @@Loop, @@Tab, @@NoTab
; In:		ds:bx	-> str
;		cx	== length of str
; Destroyed:	ax bx cx
		push	di
		mov	di, [OutBufSize]
		add	[OutBufSize], cx
@@Loop:
		mov	al, [bx]
	    	inc	bx
		mov	[OutBuf + di], al
		inc	di
		cmp	al, 9
		je	@@Tab
		inc	[Column]
		loop	@@Loop
		jmp	@@NoTab

@@Tab:
		add	[Column], 8
		and	[Column], not 7
		loop	@@Loop
	
@@NoTab:
		pop	di
endm

macro	write	str
ifdifi <bx>,<str>
		mov	bx, str
endif	
		push	bx
		call	strlen
		pop	bx
		do_write
endm

macro	writes	str
local @@Loop, @@Tab, @@NoTab
	data_seg
@msg_pos	=	$
		db	str
@msg_size	=	($ - @msg_pos)
	code_seg
		lea	bx, [@msg_pos]
		mov	cx, @msg_size
		do_write
endm

macro	whexb	num
ifdifi	<num>,<al>
		mov	al, num
endif
		call	hexbyte
		mov	bx, [OutBufSize]
		mov	ax, [word HexValue]
		mov	[word OutBuf + bx], ax
		add	[OutBufSize], 2
		add	[Column], 2
endm

macro	whexw	num
ifdifi	<num>,<ax>
		mov	ax, num
endif
		call	hexword
		mov	bx, [OutBufSize]
		mov	ax, [word HexValue]
		mov	[word OutBuf + bx], ax
		mov	ax, [word HexValue + 2]
		mov	[word OutBuf + bx + 2], ax
		add	[OutBufSize], 4
		add	[Column], 4
endm

macro	writec	chr
local @@Tab, @@NoTab
ifdifi <dx>,<chr>		
		lea	bx, chr
endif
		push	di
		mov	di, [OutBufSize]
		mov	al, [bx]
		mov	[OutBuf + di], al
		inc	[OutBufSize]
		cmp	al, 9
		je	@@Tab
		inc	[Column]
		jmp	@@NoTab
@@Tab:
		add	[Column], 8
		and	[Column], not 7
@@NoTab:
		pop	di
endm

macro	flush
		fwrite	[OutFile], [OutBuf], [OutBufSize]
		mov	[OutBufSize], 0
endm

macro	eoln
local @@Skip
		mov	[Column], 0
		cmp	[OutBufSize], OutBufThreshold
		jb	@@Skip
		flush
@@Skip:
endm

else	; if USE_BUFFERED_IO

; --- Unbuffered I/O ---

proc	CalcColumn
; In:		ds:bx	-> string
;		ax	== length
; Destroyed:	ax, cx, bx
	mov	cx, ax
@@Loop:
	mov	al, [bx]
	inc	bx
	cmp	al, 9
	je	@@Tab
	inc	[Column]
	loop	@@Loop
	ret

@@Tab:	
	add	[Column], 8
	and	[Column], not 7
	loop	@@Loop
	ret
endp

macro	write	str
ifdifi <bx>,<str>
	mov	bx, str
endif		
	push	bx
	fprint	[OutFile], bx
	pop	bx
	call	CalcColumn
endm

macro	writes	str
	fprints	[OutFile], <str>
	lea	bx, [@msg_pos]
	call	CalcColumn
endm

macro	whexb	hex
	fhexb	[OutFile], <hex>
	add	[Column], 2
endm

macro	whexw	hex
	fhexw	[OutFile], <hex>
	add	[Column], 4
endm

macro	writec	chr
ifdifi <dx>,<chr>		
	lea	dx, chr
endif	
	push	dx
	fwrite	[OutFile], dx, 1
	pop	bx
	call	CalcColumn
endm

macro	eoln
	mov	[Column], 0
endm

macro	flush
endm

endif	; if USE_BUFFERED_IO

macro	aligntocol	col
local @@1
; Assumes col is divisible by eight
; Destroys:	ax, bx, cx, dx
	mov	cx, 1
	mov	al, col
	sub	al, [Column]
	js	@@1
	add	al, 7
	shr	al, 3
	mov	cl, al
@@1:
	push	cx
	writes	<9>
	pop	cx
	loop	@@1
endm

; ----------------------------------------------------------------------
; Output formatting
; ----------------------------------------------------------------------

proc	PrintSegPrefix
; In:		SegPrefix filled in
; Destroyed:	ax, bx
		mov	al, [SegPrefix]
		cbw
		add	ax, ax
		js	@@NoPrefix
		lea	bx, [sa_SegRegs]
		add	bx, ax
		mov	bx, [bx]
		write	bx
		writes	<':'>
@@NoPrefix:
		ret
endp

proc	PrintAddrBase
; In:		
; Destroyed:	ax, bx
		mov	bx, [ofMode]
		mov	al, [Buffer + bx]
		and	ax, 7
		lea	bx, [sa_Addrs]
		add	bx, ax
		add	bx, ax
		mov	bx, [bx]
		write	bx
		ret
endp

proc	PrintArg
; In:		al == argument type
;		si -> next opcode
;		ofXXX and szXXX filled in
;		SegPrefix filled in
; Destroyed:	ax, bx, cx, dx

		cmp	al, arg_FixedEnd
		jbe	@@FixedArg
		cmp	al, argImm8
		je	@@Imm8
		cmp	al, argSImm8
		je	@@SImm8
		cmp	al, argImm16
		je	@@Imm16
		cmp	al, argMemOffs8
		je	@@MemOffs8
		cmp	al, argMemOffs16
		je	@@MemOffs16
		cmp	al, argShort
		je	@@Short
		cmp	al, argNear
		je	@@Near
		cmp	al, argFar
		je	@@Far
		cmp	al, argReg8
		je	@@Reg8
		cmp	al, argReg16
		je	@@Reg16
		cmp	al, argSegReg
		je	@@SegReg

		; Determine from addressing mode byte

		xor	dx, dx
		cmp	al, argMem16
		je	@@16bit
		cmp	al, argRegMem16
		je	@@16bit
		cmp	al, argMem32
		jne	@@DoneBitChecking
@@32bit:	inc	dx
@@16bit:	inc	dx
@@DoneBitChecking:
		; dx = 0 for 8 bit, 1 for 16 bit, 2 for 32 bit
		mov	bx, [ofMode]
		mov	al, [Buffer + bx]
		mov	ah, al
		shr	al, 6
		cmp	al, 3
		je	@@Reg

		cmp	dx, 0
		jz	@@PrintByte
		cmp	dx, 1
		je	@@PrintWord
		writes	<'dword'>
		jmp	short @@StartIt
@@PrintByte:
		writes	<'byte'>
		jmp	short @@StartIt
@@PrintWord:
		writes	<'word'>
@@StartIt:
		writes	<' ptr '>
		mov	bx, [ofMode]
		mov	al, [Buffer + bx]
		mov	ah, al
		shr	al, 6
		jz	@@Mode0
		cmp	al, 1
		jz	@@Mode1
@@Mode2:
		call	PrintSegPrefix
		writes	<'['>
		call	PrintAddrBase
		writes	<'+0'>
		mov	bx, [ofOffset]
		mov	ax, [word Buffer + bx]
		whexw	ax
		writes	<'h]'>
		ret
		
@@Mode1:
		call	PrintSegPrefix
		writes	<'['>
		call	PrintAddrBase
		mov	bx, [ofOffset]
		test	[byte Buffer + bx], 0
		jns	@@NoSign1
		writes	<'-0'>
		mov	bx, [ofOffset]
		mov	al, [Buffer + bx]
		neg	al
		jmp	short @@DoOutput1
@@NoSign1:
		writes	<'+0'>
		mov	bx, [ofOffset]
		mov	al, [Buffer + bx]
@@DoOutput1:
		whexb	al
		writes	<'h]'>
		ret

@@Mode0:
		and	ah, 7
		cmp	ah, 6
		je	@@PrintOffs16
		call	PrintSegPrefix
		writes	<'['>
		call	PrintAddrBase
		writes	<']'>
		ret
		
@@FixedArg:
		xor	ah, ah
		dec	al
		lea	bx, [sa_FixedArgs] 
		add	bx, ax
		add	bx, ax
		mov	bx, [bx]		; bx = sa_FixedArgs[ax*2]
		write	bx
		ret
@@Imm8:
		writes	<'0'>
		mov	bx, [ofData]
		mov	al, [Buffer + bx]
		whexb	al
		writes	<'h'>
		ret

@@SImm8:
		mov	bx, [ofData]
		test	[Buffer + bx], 0
		jns	@@NoSign2
		writes	<'-0'>
		mov	bx, [ofData]
		mov	al, [Buffer + bx]
		neg	al
		jmp	short @@DoOutput2
@@NoSign2:
		writes	<'0'>
		mov	bx, [ofData]
		mov	al, [Buffer + bx]
@@DoOutput2:
		whexb	al
		writes	<'h'>
		ret

@@Imm16:
		writes	<'0'>
		mov	bx, [ofData]
		mov	ax, [word Buffer + bx]
		whexw	ax
		writes	<'h'>
		ret

@@MemOffs8:	; 16-bit offset to 8-bit memory location
		writes	<'byte ptr '>
		jmp	short @@PrintOffs16

@@MemOffs16:	; 16-bit offset to 16-bit memory location
		writes	<'word ptr '>
@@PrintOffs16:
		cmp	[SegPrefix], 0
		jge	@@NoLabel
		mov	bx, [ofOffset]
		mov	bx, [word Buffer + bx]
		sub	bx, 100h
		cmp	bx, [BufSize]
		ja	@@NoLabelNoSegment
		mov	al, [byte es:Flags + bx]
		and	al, flPartOfCode + flLabel
		cmp	al, flDataLabel
		jne	@@NoLabelNoSegment
		; Label exists
		call	PrintSegPrefix
		writes	<'[', LabelPrefix>
		mov	bx, [ofOffset]
		mov	ax, [word Buffer + bx]
		whexw	ax
		writes	<']'>
		ret

@@NoLabelNoSegment:
		; Add default segment so that TASM doesn't interpet offset 
		; as constant data
		mov	[SegPrefix], 3		; DS: 
@@NoLabel:
		call	PrintSegPrefix
		writes	<'[0'>
		mov	bx, [ofOffset]
		mov	ax, [word Buffer + bx]
		whexw	ax
		writes	<'h]'>
		ret
		
@@Short:
		writes	<'short ', LabelPrefix>
		mov	bx, [ofOffset]
		mov	al, [Buffer + bx]
		cbw
		add	ax, 100h
		add	ax, si
		whexw	ax
		ret

@@Near:
		writes	<'near ptr ', LabelPrefix>
		mov	bx, [ofOffset]
		mov	ax, [word Buffer + bx]
		add	ax, 100h
		add	ax, si
		whexw	ax
		ret

@@Far:
		writes	<'far ptr '>
		mov	bx, [ofOffset]
		mov	ax, [word Buffer + bx + 2]
		whexw	ax
		writes	<':'>
		mov	bx, [ofOffset]
		mov	ax, [word Buffer + bx]
		whexw	ax
		ret

@@Reg8:
		mov	bx, [ofMode]
		mov	al, [Buffer + bx]
		shr	al, 3
		and	ax, 7
		lea	bx, [sa_8bitRegs]
		add	bx, ax
		add	bx, ax
		mov	bx, [bx]
		write	bx
		ret

@@Reg16:
		mov	bx, [ofMode]
		mov	al, [Buffer + bx]
		shr	al, 3
		and	ax, 7
		lea	bx, [sa_16bitRegs]
		add	bx, ax
		add	bx, ax
		mov	bx, [bx]
		write	bx
		ret

@@SegReg:
		mov	bx, [ofMode]
		mov	al, [Buffer + bx]
		shr	al, 3
		and	ax, 3
		lea	bx, [sa_SegRegs]
		add	bx, ax
		add	bx, ax
		mov	bx, [bx]
		write	bx
		ret

@@Reg:
		; dx = 0 for 8-bit, 1 for 16-bit regs
		mov	al, ah
		and	ax, 7
		lea	bx, [sa_8bitRegs]
		or	dx, dx
		jz	@@8bitReg
		lea	bx, [sa_16bitRegs]
@@8bitReg:
		add	bx, ax
		add	bx, ax
		mov	bx, [bx]
		write	bx
		ret
endp

; ----------------------------------------------------------------------

Help:
		assume	ds: nothing
		mov	ax, dgroup
		mov	ds, ax
		assume	ds: dgroup

	data_seg

MsgHelp		db	'Disasm v. 1.0.0  Copyright (c) 1999 Marius Gedminas'
		db		' <mgedmin@delfi.lt>', 13, 10
		db	'This program is Free Software.'
		db		'  See file COPYING for details.', 13, 10
		db	'Syntax: disasm in-file [out-file]', 13, 10
		db	'Only COM files for Intel 8086/8088 CPUs are supported'
		db	13, 10, 0

	code_seg

		print	MsgHelp
		quit	0
		
		; ------------------------------------------------------
		
Switch:
		assume	ds: nothing
		mov	al, [si]
		inc	si
		cmp	al, 'h'
		je	Help
		cmp	al, 'H'
		je	Help
		cmp	al, '?'
		je	Help
		; Invalid parameter

BadSwitch:
		assume	ds: nothing
		mov	ax, dgroup
		mov	ds, ax
		assume	ds: dgroup
		prints	<'disasm: invalid parameter', 13, 10>
		quit	1
		
		; ------------------------------------------------------

proc	Main
		; ds => PSP
		; es => PSP

		cld	; just in case
		
		assume	ds: nothing
		mov	ax, dgroup
		mov	es, ax
		assume	es:dgroup
		
		xor	ch, ch
		mov	cl, [CmdLineLen]	; cx == length of cmdline
		lea	si, [CmdLine]		; si -> cmdline
@@CmdLoop:	jcxz	Help
		dec	cx
		mov	al, [si]		; al == current char
		inc	si			; si -> next char
		cmp	al, ' '
		jbe	@@CmdLoop
		cmp	al, '-'
		je	Switch
		cmp	al, '/'
		je	Switch
		
		; file1
		lea	di, [InFName]
@@File1Loop:	mov	[es:di], al
		inc	di
		jcxz	@@File1Done
		dec	cx
		mov	al, [si]
		inc	si
		cmp	al, ' '
		ja	@@File1Loop

@@File1Done:	mov	[byte es:di], 0

		lea	di, [OutFName]
@@CmdLoop2:	jcxz	@@File2Done
		dec	cx
		mov	al, [si]
		inc	si
		cmp	al, ' '
		jbe	@@CmdLoop2
		cmp	al, '-'
		je	BadSwitch
		cmp	al, '/'
		je	BadSwitch

@@File2Loop:	mov	[es:di], al
		inc	di
		jcxz	@@File2Done
		dec	cx
		mov	al, [si]
		inc	si
		cmp	al, ' '
		ja	@@File2Loop

@@File2Done:	cmp	di, offset OutFName
		jne	@@File2Ok
		; No filename
		xor	bx, bx
		lea	si, [InFName]
		mov	al, [es:si]
		inc	si
		cmp	al, 0
		jz	@@DoneCopying
@@CopyFile:	cmp	al, '.'
		je	@@Dot
		cmp	al, '\'
		je	@@Slash
		cmp	al, '/'
		jne	@@StoreChar
@@Slash:	xor	bx, bx
		jmp	short @@StoreChar
@@Dot:		mov	bx, di
@@StoreChar:	mov	[es:di], al
		inc	di
		mov	al, [es:si]
		inc	si
		cmp	al, 0
		jnz	@@CopyFile
@@DoneCopying:
		or	bx, bx
		jz	@@NoExt
		mov	di, bx
@@NoExt:
		mov	[byte es:di], '.'
		inc	di
		mov	[byte es:di], 'a'
		inc	di
		mov	[byte es:di], 's'
		inc	di
		mov	[byte es:di], 'm'
		inc	di
@@File2Ok:
		mov	[byte es:di], 0

		mov	ax, dgroup
		mov	ds, ax
		mov	ax, bss2
		mov	es, ax
		assume	ds: dgroup, es: bss2

		; Open file
		fopen	InFName, 0
		jc	@@CantOpen
		mov	[InFile], ax	; save handle

		fread	[InFile], [Buffer], MaxBufSize
		jc	@@CantRead
		mov	[BufSize], ax

		fread	[InFile], [Scratch], 1
		jc	@@Ok
		or	ax, ax
		jz	@@Ok
		prints	<'disasm: file is too big', 13, 10>
		quit	3

@@Ok:
		fclose	[InFile]

		cmp	[BufSize], 2
		jb	@@NotEXE
		cmp	[byte Buffer+0], 'M'
		jne	@@MaybeNotEXE
		cmp	[byte Buffer+1], 'Z'
		jne	@@NotEXE
@@EXE:
		prints	<'disasm: EXE files are not supported', 13, 10>
		quit	3

@@MaybeNotEXE:
		cmp	[byte Buffer+0], 'Z'
		jne	@@NotEXE
		cmp	[byte Buffer+1], 'M'
		je	@@EXE

@@NotEXE:

		lea	di, [Flags]
		xor	ax, ax
		mov	cx, [BufSize]
		inc	cx
		shr	cx, 1
		rep stosw

		xor	si, si
		call	Trace

		fcreate	OutFName, 0
		jc	@@CantCreate
		mov	[OutFile], ax

	data_seg
Header		db	9, '.model', 9, 'tiny', 13, 10
		db	9, '.code', 13, 10
		db	9, 'org', 9, '100h', 13, 10
		db	'start:', 13, 10
HeaderSize	=	($ - Header)
	code_seg
		
		fwrite	[OutFile], [Header], HeaderSize
		jc	@@CantWrite
	
		xor	si, si
		mov	[PrevWasData], 0
@@MainLoop:
		test	[byte es:Flags + si], flCode
		jnz	@@CodeHere
		; Data
		cmp	[PrevWasData], 0
		jnz	@@TestGap
		mov	[PrevWasData], 1
		jmp	short @@PrintGap
		; ------------------------------------------------------
@@CodeHere:
		; Code
		cmp	[PrevWasData], 0
		jz	@@TestGap
		mov	[PrevWasData], 0
		jmp	short @@PrintGap
@@TestGap:
		test	[byte es:Flags + si], flGap
		jz	@@NoGap
@@PrintGap:
		writes	<13, 10>
		eoln
@@NoGap:
		test	[byte es:Flags + si], flLabel
		jz	@@NoLabel
		writes	<LabelPrefix>
		lea	ax, [si+0100h]
		whexw	ax
		writes	<':'>
@@NoLabel:
		test	[byte es:Flags + si], flCode
		jnz	@@Code
		test	[byte es:Flags + si], flBadCode
		jz	@@Data
		writes	<';*'>
@@Code:
		writes	<9>
		call	DecodeInsn
		mov	di, [ofPrefix]
		mov	cx, [szPrefix]
		jcxz	@@NoPrefix

		; Check if we will actually call PrintSegPrefix
		cmp	[Arg1], argMemOffs8
		je	@@Prefix
		cmp	[Arg2], argMemOffs8
		je	@@Prefix
		cmp	[Arg1], argMemOffs16
		je	@@Prefix
		cmp	[Arg2], argMemOffs16
		je	@@Prefix
		cmp	[szMode], 0
		je	@@WontPrintSegPrefix
		mov	bx, [ofMode]
		mov	al, [Buffer + bx]
		shr	al, 6
		cmp	al, 3
		jne	@@Prefix		; not reg -- will print
@@WontPrintSegPrefix:
		mov	[ofSegPrefix], -1
@@Prefix:
		cmp	di, [ofSegPrefix]	; don't show segXX prefixes!
		je	@@Skip
		mov	al, [Buffer + di]
		LocateOpcode			; bx -> Opcodes[al]
		mov	bx, [(TOpcodeData bx).Mnemonic]
		push	cx
		write	bx
		writes	<' '>
		pop	cx
@@Skip:		
		inc	di
		dec	cx
		jnz	@@Prefix
@@NoPrefix:
		write	[Mnemonic]
		cmp	[Arg1], argNone
		je	@@FinishCode
		writes	<9>
		mov	al, [Arg1]
		call	PrintArg
		cmp	[Arg2], argNone
		je	@@FinishCode
		writes	<', '>
		mov	al, [Arg2]
		call	PrintArg
@@FinishCode:
		mov	bx, [ofPrefix]
		test	[byte es:Flags + bx], flBadCode
		jz	@@FinishLine
		mov	si, bx
		writes	<13, 10>
	 	eoln

@@Data:
		mov	[ofPrefix], si
		test	[byte es:Flags + si], flBadCode
		jnz	@@NoString
		cmp	[byte Buffer + si], 32
		jb	@@NoString
		cmp	[byte Buffer + si], 126
		jbe	@@String
@@NoString:
		writes	<9, 'db', 9, '0'>
		whexb	<[Buffer + si]>
		writes	<'h'>
		inc	si
		jmp	@@FinishLine

		; ------------------------------------------------------

@@String:
		writes	<9, 'db', 9, ''''>
		lea	di, [si + 16]			; di == limit
		cmp	di, [BufSize]
		jbe	@@StringLoop
		mov	di, [BufSize]
@@StringLoop:	
		writec	<[Buffer + si]>
		cmp	[byte Buffer + si], ''''
		jne	@@NotQuote
		writec	<[Buffer + si]>			; Duplicate ''
@@NotQuote:		
		inc	si
		cmp	si, di
		jae	@@DoneString
		test	[byte es:Flags + si], flLabel or flPartOfCode
		jnz	@@DoneString
		cmp	[byte Buffer + si], 32
		jb	@@DoneString
		cmp	[byte Buffer + si], 126
		jbe	@@StringLoop
@@DoneString:
		writes	<''''>
; no need to:	jmp	@@FinishLine

@@FinishLine:
		aligntocol	48
		writes	<'; '>
		mov	ax, [ofPrefix]
		add	ax, 100h
		whexw	ax
		
		mov	di, [ofPrefix]
		writes	<' '>
@@PrintBytes:
		writes	<' '>
		mov	al, [Buffer + di]
		whexb	al
		inc	di
		cmp	di, si
		jb	@@PrintBytes

		writes	<13, 10>
		eoln
		cmp	si, [BufSize]
		jb	@@MainLoop

		; Final label
		test	[byte es:Flags + si], flLabel
		jz	@@NoFinalLabel
		writes	<LabelPrefix>
		lea	ax, [si+0100h]
		whexw	ax
		writes	<':', 13, 10>
		eoln
@@NoFinalLabel:

	data_seg
Footer		db	'end', 9, 'start', 13, 10
FooterSize	=	($ - Footer)
	code_seg
	
		flush
		fwrite	[OutFile], [Footer], FooterSize
		jc	@@CantWrite
		fclose	[OutFile]
		jc	@@CantWrite

		quit	0

@@CantOpen:
		prints	<'disasm: cannot open '>
		print	InFName
		prints	<13, 10>
		quit	2

@@CantRead:
		prints	<'disasm: error reading '>
		print	InFName
		prints	<13, 10>
		quit	2

@@CantCreate:
		prints	<'disasm: cannot create '>
		print	OutFName
		prints	<13, 10>
		quit	4

@@CantWrite:
		prints	<'disasm: error writing '>
		print	OutFName
		prints	<13, 10>
		quit	4

		; ------------------------------------------------------
	
endp	Main

; ----------------------------------------------------------------------

ends
end	Main

; ----------------------------------------------------------------------

