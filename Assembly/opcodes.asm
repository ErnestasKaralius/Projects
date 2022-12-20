    
	
	; 8bits
    s_JCXZ db "JCXZ ", 0
    s_XLAT db "XLAT ", 0
    s_JO db "JO ", 0
    s_JNO db "JNO ", 0
    s_JC db "JC ", 0
    s_JNC db "JNC ", 0
    s_JE db "JE ", 0
    s_JNE db "JNE ", 0
    s_JNA db "JNA ", 0
    s_JA db "JA ", 0
    s_JS db "JS ", 0
    s_JNS db "JNS ", 0
    s_JP db "JP ", 0
    s_JNP db "JNP ", 0
    s_JL db "JL ", 0
    s_JNL db "JNL ", 0
    s_JLE db "JLE ", 0
    s_JG db "JG ", 0

    s_CBW db "CBW ", 0
    s_CWD db "CWD ", 0
    s_HLT db "HLT ", 0
    s_WAIT db "WAIT ", 0
    s_LOCK db "LOCK ", 0
    s_PUSHF db "PUSHF ", 0
    s_POPF db "POPF ", 0

    s_AAM db "AAM ", 0
    s_AAD db "AAD ", 0

    s_NEG db "NEG ", 0 ; 7bits
    s_RCL db "RCL ", 0 ; 6bits
    s_ADC db "ADC ", 0 ; 6bits
    s_ESC db "ESC ", 0 ; 5bits

    r_AX db "AX", 0
    r_CX db "CX", 0
    r_DX db "DX", 0
    r_BX db "BX", 0
    r_BL db "BL", 0
    r_CL db "CL", 0
    r_AL db "AL", 0
    r_DL db "DL", 0
    r_DH db "DH", 0
    r_BH db "BH", 0
    r_CH db "CH", 0
    r_AH db "AH", 0

    r_SP db "SP", 0
    r_BP db "BP", 0
    r_SI db "SI", 0
    r_DI db "DI", 0
    r_ES db "es:", 0
    r_DS db "ds:", 0
    r_SS db "ss:", 0
    r_CS db "cs:", 0

    r_BX_SI db "BX + SI", 0
    r_BX_DI db "BX + DI", 0
    r_BP_SI db "BP + SI", 0
    r_BP_DI db "BP + DI", 0

    colon db ": ", 0
    new_line db 13, 10
    space db 20h, 20h
    plus db " + ", 0
    comma db ", ", 0
    bracket_left db "[", 0
    bracket_right db "]", 0
    number_1 db "1", 0
