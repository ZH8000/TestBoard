$NOMOD51
;------------------------------------------------------------------------------
;  This file is part of the C51 Compiler package
;  Startup Code for the Infineon XC8xx devices 
;  Copyright (c) 1988-2005 Keil Elektronik GmbH and Keil Software, Inc.
;  Version 20100601
;  -------- Revision ---------
;  - Previous version 20100405
;  - Added XC864 with option for LIN_BSL parameters
;  - Renamed NDIV_XC866 to NDIV_XC86x
;
;  *** <<< Use Configuration Wizard in Context Menu >>> ***
;------------------------------------------------------------------------------
;  STARTUP.A51:  This code is executed after processor reset.
;
;  To translate this file use A51 with the following invocation:
;
;     A51 STARTUP.A51
;
;  To link the modified STARTUP.OBJ file to your application use the following
;  Lx51 invocation:
;
;     Lx51 your object file list, STARTUP.OBJ  controls
;
;------------------------------------------------------------------------------
;
;<e> Use off-chip XTAL
;<i> XC8xx series runs by default from on-chip osciallator.
;<i> optionally you may use a off-chip XTAL
;
XTAL          EQU     0   ; set to 0 On-chip oscillator/ not used for XC82x devices
;
;<e> Device = " XC82x "
XC82x_CHIP    EQU   0     ;applicable to XC83x
;---------------------------------------------------------------------
;resulting in fsys = 80MHz for XC866/XC864 and fsys = 96MHz for XC88x unless otherwise mentioned
;
;<e> Device = " XC866 "
XC866_CHIP    EQU   0
;<e> Device = " XC864 "
XC864_CHIP    EQU   0
;
; <o> PLL N-Divider
; <i> PLL N-Divider must result in fsys = 80MHz
; <0=>  N=14
; <1=>  N=15
; <2=>  N=16 (10 MHz XTAL)
; <3=>  N=17
; <4=>  N=18
; <5=>  N=19
; <6=>  N=20 (8 MHz XTAL)
; <7=>  N=21
; <8=>  N=24
; <9=>  N=28
; <10=> N=30
; <11=> N=32 (5 MHz XTAL)
; <12=> N=40
; <13=> N=42
; <14=> N=45
; <15=> N=50
;
NDIV_XC86x    EQU      2   ; default 2
;</e>    

;---------------------------------------------------------------------
;<e> Device = " XC88x "
XC88x_CHIP    EQU   1
;
; <o> PLL N-Divider for *NON-SAL* device fsys = 96 MHz
; <0=>  N=10
; <1=>  N=12 
; <2=>  N=13
; <3=>  N=14
; <4=>  N=15
; <5=>  N=16 (12 MHz XTAL)
; <6=>  N=17
; <7=>  N=18
; <8=>  N=19
; <9=>  N=20 (9.6 MHz On-Chip XTAL)
; <10=> N=24 (8 MHz XTAL)
; <11=> N=30
; <12=> N=32 (6 MHz XTAL)
; <13=> N=36
; <14=> N=40
; <15=> N=48 (4 MHz XTAL)
;
; <o> PLL N-Divider for *SAL* device -> fsys = 80 MHz
; <0=>  N=10 
; <1=>  N=12
; <2=>  N=13
; <3=>  N=14
; <4=>  N=15
; <5=>  N=16 (10 MHz On-Chip XTAL)
; <6=>  N=17
; <7=>  N=18
; <8=>  N=19
; <9=>  N=20 (8 MHz XTAL)
; <10=> N=24 
; <11=> N=30
; <12=> N=32 (5 MHz XTAL)
; <13=> N=36
; <14=> N=40 (4 MHz XTAL)
; <15=> N=48
;

NDIV_XC88x    EQU       9   ; default 9
;</e>

;---------------------------------------------------------------------
;<e> Device = " XC87x "
XC878_CHIP_16FF    EQU       0
XC878_CHIP_13FF    EQU       0
XC874_CHIP_16FF    EQU       0
XC874_CHIP_13FF    EQU       0

;4 MHz 
NDIV_XC87x_PLL_CON    EQU       0x18
NDIV_XC87x_PLL_CON1   EQU       0x20
NR_XC87x              EQU       0x00
OD_XC87x              EQU       0x00

;6 MHz 
;NDIV_XC87x_PLL_CON    EQU       0x18
;NDIV_XC87x_PLL_CON1   EQU       0x20
;NR_XC87x              EQU       0x01
;OD_XC87x              EQU       0x00

;8 MHz default
;NDIV_XC87x_PLL_CON    EQU       0x18
;NDIV_XC87x_PLL_CON1   EQU       0x20
;NR_XC87x              EQU       0x02
;OD_XC87x              EQU       0x00

;</e>

;</e>
;------------------------------------------------------------------------------
;
;  User-defined <h> Power-On Initialization of Memory
;
;  With the following EQU statements the initialization of memory
;  at processor reset can be defined:
;
;<o> IDATA memory length <0x0-0x100>
;<i> Note: The absolute start-address of IDATA memory is always 0
;<i>       The IDATA space overlaps physically the DATA and BIT areas.
IDATALEN        EQU     0x100
;
; <o> XDATA memory start address <0x0-0xFFFF> 
; <i> absolute start-address of XDATA memory
XDATASTART      EQU     0xF000     
;
; <o> XDATA memory length <0x0-0xFFFF> 
; <i> length of XDATA memory in bytes.
IF (XC82x_CHIP)
  XDATALEN      EQU     0x100 
ELSEIF (XC866_CHIP || XC864_CHIP)
  XDATALEN      EQU     0x200
ELSEIF (XC88x_CHIP)
  XDATALEN      EQU     0x600 
ELSEIF (XC878_CHIP_16FF || XC878_CHIP_13FF)
  XDATALEN      EQU     0xC00
ELSEIF (XC874_CHIP_16FF || XC874_CHIP_13FF)
  XDATALEN      EQU     0xC00

ENDIF
  
;
; <o> PDATA memory start address <0x0-0xFFFF> 
; <i> absolute start-address of PDATA memory
PDATASTART      EQU     0xF000
;
; <o> PDATA memory length <0x0-0xFF> 
; <i> length of PDATA memory in bytes.
PDATALEN        EQU     0
;
; </h>
;------------------------------------------------------------------------------
;
; <h> Reentrant Stack Initilization
;
;  The following EQU statements define the stack pointer for reentrant
;  functions and initialized it:
;
; Stack Space for reentrant functions in the SMALL model.
; <e> Activate reentrant Stack (SMALL model)
IBPSTACK        EQU     0       ; set to 1 if small reentrant is used.
; <o> top of stack <0x0-0xFF> 
; <i> set top of stack to highest location+1 
IBPSTACKTOP     EQU     0xFF +1     ; default 0FFH+1  
; </e>
;
;  Stack Space for reentrant functions in the LARGE model.      
; <e> Activate reentrant Stack (LARGE model)
XBPSTACK        EQU     0       ; set to 1 if large reentrant is used.
; <o> top of stack <0x0-0xFFFF> 
; <i> set top of stack to highest location+1.
XBPSTACKTOP     EQU     0xFFFF +1   ; default 0FFFFH+1 
; </e>
;
;  Stack Space for reentrant functions in the COMPACT model.    
; <e> Activate reentrant Stack (COMPACT model)
PBPSTACK        EQU     0       ; set to 1 if compact reentrant is used.
;
; <o> top of stack <0x0-0xFF> 
; <i> set top of stack to highest location+1.
PBPSTACKTOP     EQU     0xFF +1     ; default 0FFH+1  
; </e>
; </h>
;------------------------------------------------------------------------------
;
;  <e>Set Memory Page for Using the Compact Model with 64 KByte xdata RAM
;
;  <i>Define the xdata page used for pdata variables. 
;  <i>PPAGE must conform with the PPAGE set in the linker invocation.
;
; Enable pdata memory page initalization
PPAGEENABLE     EQU     0       ; set to 1 if pdata object are used.
;
; <o> PPAGE number <0x0-0xFF> 
; <i> uppermost 256-byte address of the page used for pdata variables.
PPAGE           EQU     0xF0
;
; </e>
;------------------------------------------------------------------------------
;
;  <e>Parameters for LIN Boostrap Loader (XC864 only)
;  <i>When these values are not defined, an XC864 device stays in 
;  <i>LIN-BSL mode and does not start the user application 
;
; Enable LIN BSL parameter initialization
LIN_BSL         EQU     1           ; set to 1 if LIN BSL parameters should be generated in flash table
;
; <o> NAC: No. Activity Count <0x00-0xFF> 
; <i> specifies the delay (n * 5ms) before jumping to user mode.
; <i> 0x01:  0 ms delay. Jump to User Mode immediately
; <i> 0x02:  5 ms delay before jumping to User Mode
; <i> 0x03: 10 ms delay before jumping to User Mode
; <i> 0x04 - 0x0C: 15 - 55 ms delay before jumping to User Mode
; <i> 0x0D - 0xFF, 0x00: Enter LIN BSL Mode (Invalid NAC)
LIN_NAC         EQU     0x01
;
; <o> NAD: Node Address for Diagnostic <0x00-0xFF> 
; <i> specifies the address of the active slave node.
LIN_NAD         EQU     0x01
;
; </e>
;------------------------------------------------------------------------------

;Check the chip selection
IF ((XC82x_CHIP + XC866_CHIP + XC864_CHIP + XC88x_CHIP + XC878_CHIP_16FF + XC878_CHIP_13FF + XC874_CHIP_16FF + XC874_CHIP_13FF) > 1)
      __ERROR__  "Please select only one chip!"
ELSEIF ((XC82x_CHIP + XC866_CHIP + XC864_CHIP + XC88x_CHIP + XC878_CHIP_16FF + XC878_CHIP_13FF + XC874_CHIP_16FF + XC874_CHIP_13FF) == 0)
      __ERROR__  "Please select a chip!"
ENDIF

IF (XTAL <> 0)
    IF (XC866_CHIP <> 0 || XC864_CHIP <> 0)
       NDIV EQU NDIV_XC86x
    ELSEIF (XC88x_CHIP <> 0)
       NDIV EQU NDIV_XC88x
    ELSEIF (XC878_CHIP_16FF <> 0 || XC878_CHIP_13FF <> 0)
       ;nothing   
    ELSEIF (XC874_CHIP_16FF <> 0 || XC874_CHIP_13FF <> 0)
       ;nothing
    ELSEIF (XC82x_CHIP <> 0)
       ;nothing
    ELSE
      __WARNING__  "Default NDIV selection is XC866"
      NDIV EQU NDIV_XC86x  ;Default
    ENDIF
 ENDIF                   ;End of XTAL selection

; Standard SFR Symbols 
ACC     DATA    0E0H
B       DATA    0F0H
SP      DATA    81H
DPL     DATA    82H
DPH     DATA    83H

; XC8xx specific SFR Symbols used in STARTUP code
IF (XC82x_CHIP == 0)
; Take note of different SFR addresses for XC82x. Currently not used.
        sfr  SCU_PAGE = 0xBF
        sfr  PLL_CON  = 0xB7
        sfr  PLL_CON1 = 0xEA;//SCU,RMAP=0,Page=1
        sfr  CMCON    = 0xBA
        sfr  OSC_CON  = 0xB6
        sfr  PASSWD   = 0xBB
        sfr  XADDRH   = 0xB3
        sfr  MEX3     = 0x96
ENDIF

IF(XC874_CHIP_13FF == 1 || XC874_CHIP_16FF == 1)
        sfr  PORT_PAGE = 0xB2
        sfr  P3_PUDEN  = 0xB1
        sfr  P4_PUDEN  = 0xC9
ENDIF

                NAME    ?C_STARTUP

?C_C51STARTUP   SEGMENT   CODE
?STACK          SEGMENT   IDATA

                RSEG    ?STACK
                DS      1

                EXTRN CODE (?C_START)
                PUBLIC  ?C_STARTUP

                CSEG    AT      0
?C_STARTUP:     LJMP    STARTUP1

                RSEG    ?C_C51STARTUP

STARTUP1:

IF (XTAL <> 0)       
                    ; switch to external XTAL
        IF(XC878_CHIP_16FF <> 0 || XC878_CHIP_13FF <> 0 || XC874_CHIP_16FF <> 0 || XC874_CHIP_13FF <> 0)
                MOV     SCU_PAGE,#1;
                MOV     PASSWD, #11000000B     ;Disable Bit-Protection
                ANL     OSC_CON, #~(0x01 << 2) ;OSCSS = 0
                ORL     OSC_CON, #(0x01 << 6)  ;Bypass PLL Output ( PLLBYP = 1 )
                ORL     OSC_CON, #(0x01 << 5)  ;Set PLL Power Down Mode ( PLLPD = 1)
                ANL     OSC_CON, #~(0x01 << 3) ;XPD = 0, XTAL not powered down
                          
                          
        WAIT_XTAL_STABLE:          ; delay necssary for external clock to stablise
                MOV     R2,#0x1E   ; wait about 1.5 ms ( varies with oscillator freq )
        LOOP:
                MOV     R3,#0x64   
                DJNZ    R3, $
                DJNZ    R2, LOOP
     OSC_WDT:
                ORL     OSC_CON, #(0x01 << 1)  ;Restart external oscillator watchdog
                MOV     R0,#0x41               ;Wait for 65 cycles
                DJNZ    R0, $
             ;user may want to add an error counter for oscillator detection
        CHECK_EXTOSCR:
                MOV     A, OSC_CON
                JNB     ACC.0, OSC_WDT        
                ORL     OSC_CON, #(0x01 << 2)  ;Select external oscillator 
                MOV     PLL_CON,  #NDIV_XC87x_PLL_CON      ; NDIV value 
                MOV     PLL_CON1, #NDIV_XC87x_PLL_CON1     ; NDIV Value 
                MOV     A, #NR_XC87x                       ; PDIV Value 
                ORL     PLL_CON1, A                                     
                MOV     A, #OD_XC87x                       ; KDIV Value 
                ORL     CMCON,    A                                     
                ANL     OSC_CON, #~(0x01 << 5)  ;Change to PLL Normal Mode ( PLLPD = 0) 
                ORL     OSC_CON, #(0x01 << 7)   ;Restart the PLL watchdog ( PLLRDRES = 1) 

             ;user may want to add an error counter for PLL lock detection
        PLLNOTRUN:
                MOV     A, PLL_CON
                JNB     ACC.1, PLLNOTRUN           ;PLL_Run Status

        PLLNOTLOCKED:
                MOV     A, PLL_CON
                JNB     ACC.0, PLLNOTLOCKED        ;PLL_Lock Status

                ANL     OSC_CON, #~(0x01 << 6)     ;Disable bypass PLL output 
                MOV     PASSWD, #11000011B         ;Enable Bit-Protection
                MOV     SCU_PAGE,#0

ELSEIF(XC866_CHIP <> 0 || XC864_CHIP <> 0 || XC88x_CHIP <> 0)
                MOV     SCU_PAGE,#1
                ORL     PLL_CON, #0x08  ; VCOBYP = 1
                ORL     PLL_CON, #0x04  ; OSCDISC = 1   _ _ _ NDIV, VCOBYP, OSCDISC, RESLD, LOCK
                ANL     OSC_CON, #0xF7  ; XPD = 0       power xtal
                ORL     OSC_CON, #0x04  ; OSCSS = 1     0, 0, 0, OSCPD, XPD, OSCSS, ORDRES, OSCR
                ;all calculations are based on no wait state
                MOV     R1,#0
DelayXTAL0:
                MOV     R0,#10         ; delay necssary for external clock to stablise (amplitude >= 0.4 * VDDC - refer to product data sheet)
DelayXTAL:            ; delay time should be adjusted according to different external osciallators
                DJNZ    R1,$
                DJNZ    R0,DelayXTAL
                
                ; redetection of osc
OSCR_NOTSET:
                MOV     R0, #86
                ORL     OSC_CON, #0x02  ; ORDRES = 1    ;restart oscillator run detection
                ;assume no wait state, K = 2, 
                ;Apollo requires to wait for 256 clock cycles -> 2048 vco cycles
                ;Elektra requires to wait for 342 clock cycles -> 2048 vco cycles
                ;djnz = 4 cc
                DJNZ    R0, $
                MOV     A,OSC_CON
                JNB     ACC.0, OSCR_NOTSET
                
                ;reprogram the NDIV factor to required value
                ;ORL     PLL_CON, #0x08      ; VCOBYP = 1 to change N-Divider
                MOV     PASSWD,  #0x98      ; open access to writing protected bit
                ANL     PLL_CON, #0x0F
                ORL     PLL_CON, #NDIV*16
                ANL     PLL_CON, #0xFB      ; OSCDISC = 0, reconnect oscillator to the PLL
                
                ;PLL lock detection
                ORL     PLL_CON, #0x02     ; detect PLL lock
                MOV     R0, #100           ; LOCK flag should be set within 200us, user need to adapt accordingly
                                           ; assume a 10MHz XTAL for XC866/XC864 device
                                           ; device is in prescaler mode, k = 2 therefore fsys = 5MHz
                                           ; ## 1cclk = 1/(5MHz/3) = 600 ns
                                           ; DJNZ requires 4 x 600ns = 2.4 us therefore 100 DJNZ -> 240us
                                           ; for XC88x, the factor 3 (##) is changed to 4 then the calculated value is 
                                           ; 320 us based on a 10MHz XTAL
WAIT_LOCK:
                DJNZ    R0, $
                MOV     A, PLL_CON
                JNB     ACC.0, OSCR_NOTSET
                ; reconnect to PLL
                ANL     PLL_CON, #0xF7   ; VCOBYP = 0
                MOV     SCU_PAGE,#0     
        ENDIF
ENDIF

IF IDATALEN <> 0
                MOV     R0,#IDATALEN - 1
                CLR     A
IDATALOOP:      MOV     @R0,A
                DJNZ    R0,IDATALOOP
ENDIF

IF (XC878_CHIP_16FF <> 0 || XC874_CHIP_16FF <> 0)
                MOV     MEX3, #0x1F
ENDIF

IF (XC874_CHIP_13FF <> 0 || XC874_CHIP_16FF <> 0)
                MOV     PORT_PAGE, #0x01
                ORL     P3_PUDEN, #0x80
                ORL     P4_PUDEN, #0xF0
                MOV     PORT_PAGE, #0x00
ENDIF



IF XDATALEN <> 0
                MOV     DPTR,#XDATASTART
                MOV     R7,#LOW (XDATALEN)
  IF (LOW (XDATALEN)) <> 0
                MOV     R6,#(HIGH (XDATALEN)) +1
  ELSE
                MOV     R6,#HIGH (XDATALEN)
  ENDIF
                CLR     A
XDATALOOP:      MOVX    @DPTR,A
                INC     DPTR
                DJNZ    R7,XDATALOOP
                DJNZ    R6,XDATALOOP
ENDIF

IF PPAGEENABLE <> 0
                MOV     SCU_PAGE,#3 
                MOV     XADDRH,#PPAGE
                MOV     SCU_PAGE,#0 
ENDIF

IF PDATALEN <> 0
                MOV     R0,#LOW (PDATASTART)
                MOV     R7,#LOW (PDATALEN)
                CLR     A
PDATALOOP:      MOVX    @R0,A
                INC     R0
                DJNZ    R7,PDATALOOP
ENDIF

IF IBPSTACK <> 0
EXTRN DATA (?C_IBP)

                MOV     ?C_IBP,#LOW IBPSTACKTOP
ENDIF

IF XBPSTACK <> 0
EXTRN DATA (?C_XBP)

                MOV     ?C_XBP,#HIGH XBPSTACKTOP
                MOV     ?C_XBP+1,#LOW XBPSTACKTOP
ENDIF

IF PBPSTACK <> 0
EXTRN DATA (?C_PBP)
                MOV     ?C_PBP,#LOW PBPSTACKTOP
ENDIF

                MOV     SP,#?STACK-1

                LJMP    ?C_START

; Overwrite ?C?DPSEL address for XC866 Device
PUBLIC ?C?DPSEL
?C?DPSEL DATA 0A2H   ; DPSEL address for Mentor M8051EW

IF XC864_CHIP <> 0
  ; Optional ROM-table for XC864 LIN-BSL
  IF LIN_BSL <> 0
                  CSEG    AT      0FFCH
                  DB      LIN_NAC
                  DB      NOT(LIN_NAC)
                  DB      LIN_NAD
                  DB      NOT(LIN_NAD)
  ENDIF
ENDIF

                END
