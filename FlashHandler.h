/**********************************************************************************************************
**   FlashHandler.h
**   Infineon Technologies AG 2008
**********************************************************************************************************/
#ifndef	__FLASHHANDLER_H__
#define __FLASHHANDLER_H__

#include "FlashHandlerConfig.h"						// Wordline buffer address / Boot ROM entry addresses
#include "FLASH_Def.h"
#include "Main.h"									// Make the sfr definitions available
#ifdef 	__C51__
#include <intrins.h>								// ensure in every case that intrinsics are available
#endif	// __C51__

#ifndef	XC878
/*------------------------
     General - Section
-------------------------*/
typedef union unFLASH_ERASE_PARAM {					// simplify parameter passing to the different compilers
	unsigned char UBYTE_Param[2];
	unsigned int  UINT_Param;
} t_unFLPARAM;
#endif  // ifndef XC878

#ifndef	XC878
#ifdef	SDCC						
extern unsigned char idata __at (WORDLINE_BUFFER_ADDRESS) WLBuf[BYTES_PER_WORDLINE];
#endif // SDCC
#ifdef __C51__
extern unsigned char idata      WLBuf[BYTES_PER_WORDLINE]; 
#endif // __C51__
#endif	// ifndef XC878

#ifdef	XC878
#ifdef	SDCC						
extern unsigned char xdata __at	(XRAM_BUFFER_ADDR)			WLBuf[BYTES_PER_WORDLINE];
#endif	// SDCC
#ifdef	__C51__
extern unsigned char xdata		WLBuf[BYTES_PER_WORDLINE];   
#endif	// __C51__ 
#endif	// XC878

#ifndef	XC878
// Handler routines
extern bit FLASH_Prog					(unsigned char code* WLAddress);
extern bit FLASH_Ready					(unsigned char BankNum);
extern bit FLASH_Erase_Abort			(void);

/*------------------------
     Device - Section
-------------------------*/ 
#ifdef	XC866
extern  bit FLASH_Erase					(unsigned int DFlash0Sector);  // is same as bank 3
#endif	// XC866
#ifdef	XC88x
extern  bit FLASH_Erase					(unsigned int DFlash0Sector,unsigned int DFlash1Sector);
#endif  // XC88x
#endif	// ifndef XC878 

#ifdef	XC878
void InitMemExtension					(void);
extern	bit  FLASH_Erase				(unsigned char code* FlashDstAddr,unsigned char KindOfErase);
extern	bit  FLASH_Prog					(unsigned char code * DestWordLine, unsigned char NrOfBytes);
#endif	// XC878

#endif	//__FLASHHANDLER_H__






















