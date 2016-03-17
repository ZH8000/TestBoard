/**********************************************************************************************************
**  Flashhandler.c    XC866BB and higher, XC88x, XC878
**  2008  Infineon Technologies     
**********************************************************************************************************/
#include "FlashHandler.h"

//     MACRO Definitions for absolute register access
//----------------------------------------------------------------------
#define REG		((unsigned char volatile data *) 0)	// Allow absolute access to registers R0 ... R7 
													// in all banks. 

//     sfr16 operator declaration / definition
//----------------------------------------------------------------------
#ifdef	__C51__
sfr16 DPTR = 0x82;
#endif	// __C51__

#ifdef	SDCC
__sfr16	__at(((0x82+1U)<<8) | 0x82)  DPTR;			// just sfr16 check for SCC XC800
#endif	// SDCC


//     Intrinsic functions used in the handler for XC866 / XC88x
//----------------------------------------------------------------------
#ifndef XC878
#ifdef	__C51__
#define		PUSH(n)		_push_(n);
#define		POP(n)		_pop_(n);
#endif	// __C51__

#ifdef	SDCC
#define		PUSH(n)		{ _asm PUSH  n _endasm; }
#define		POP(n)		{ _asm POP   n _endasm; }
#endif	// SDCC
#endif	// ifndef XC878


//     GLOBAL Variable WLBuf and fix up for MagicMemory location
//----------------------------------------------------------------------
//       Fix MAGIC Memory and Wordlinebuffer addresses
// Note: This could also be done with the linker/locator, 
//       but is easier this way for unexperienced users
#ifndef XC878
#ifdef	SDCC						
unsigned char idata __at	(WORDLINE_BUFFER_ADDRESS)	WLBuf[BYTES_PER_WORDLINE];
unsigned char data  __at	(MAGIC_MEMORY)				MagicMemory[RESERVED_BYTES];
#endif	// SDCC

#ifdef	__C51__
unsigned char idata			WLBuf[BYTES_PER_WORDLINE]   _at_ WORDLINE_BUFFER_ADDRESS;
unsigned char data			MagicMemory[RESERVED_BYTES] _at_ MAGIC_MEMORY;
#endif	// __C51__ 
#endif	// ifndef XC878



#ifdef	XC878
#ifdef	SDCC						
unsigned char xdata __at	(XRAM_BUFFER_ADDR)			WLBuf[BYTES_PER_WORDLINE];
unsigned char data  __at	(MAGIC_MEMORY)				MagicMemory[RESERVED_BYTES];
#endif	// SDCC
#ifdef	__C51__
unsigned char xdata			WLBuf[BYTES_PER_WORDLINE]   _at_ XRAM_BUFFER_ADDR;
unsigned char data			MagicMemory[RESERVED_BYTES] _at_ MAGIC_MEMORY;
#endif	// __C51__ 
#endif	// XC878

//===============================================================================
//                               HANDLER ROUTINES
//===============================================================================
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//     FLASH ERASE ABORT		 XC866 / XC88x
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef	XC878
bit FLASH_Erase_Abort (void)
{
#ifdef __C51__		
	((void (code *) (void)) FLASH_ERASE_ABORT) ();
#endif	// __C51__
#ifdef	SDCC
_asm
	LCALL FLASH_ERASE_ABORT;
_endasm;
#endif	// SDCC
	return (!CY);  
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//     FLASH Ready               XC866 / XC88x
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bit FLASH_Ready						(unsigned char BankNum)
{
    ACC = BankNum;
#ifdef __C51__		
	((void (code *) (void)) FLASH_READ_STATUS) ();
#endif	// __C51__
#ifdef	SDCC
_asm
	LCALL FLASH_READ_STATUS;
_endasm;
#endif	// SDCC
	return(CY);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//     FLASH Prog                XC866 / XC88x
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  With modification of this routine, we can save the intermediate 
//  DPTR SAVING for the SDCC, due to the fact that WORDLINE Buffer Address 
//  is known at compile time. It coud be fixed up here


// FLAH_Prog ((unsigned char code*)WORDLINEADDR(117));			// How to call it ...
bit FLASH_Prog					(unsigned char code* WLAddress) 
{
#ifdef	XC88x
	volatile bit success;		    // needed for CY flag saving of the BROM routine's result
#endif	// XC88x
#ifdef	XC866
#define USE_BANK  3					// fix the used registerbank to 3 for XC866 devices
#endif	// XC866
									// For SDCC parameter is now already in DPTR
#ifdef SDCC
	*WLAddress;						// avoid warning of 'unreferenced function argument
#endif	// SDCC
#ifdef __C51__
   DPTR = (unsigned int)WLAddress;
#endif	// __C51__

   REG[(0+(USE_BANK*8))] = WORDLINE_BUFFER_ADDRESS;
#ifdef	XC88x
	PUSH(PSW);
	PSW = ((USE_BANK)<<3);
#endif	// XC88x

#ifdef	__C51__		
	((void (code *) (void)) FLASH_PROG) ();
#endif	// __C51__
#ifdef	SDCC
_asm
	LCALL FLASH_PROG;
_endasm;
#endif	// SDCC

#ifdef	XC88x
	success = CY;
	POP(PSW);
	return(!success);			  
#endif	// XC88x
#ifdef	XC866
	return (!CY);
#endif	// XC866
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//     FLASH Erase                XC866 / XC88x
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifdef	XC866
bit FLASH_Erase			(unsigned int DFlash0Sector)
#endif	// XC866
#ifdef	XC88x
bit FLASH_Erase			(unsigned int DFlash0Sector,unsigned int DFlash1Sector)
#endif	// XC88x
{
#ifdef	XC88x
    volatile bit success; 
#endif	// XC88x
	t_unFLPARAM P1;
#ifdef	XC88x
	t_unFLPARAM P2;
#endif	// XC88x

#ifdef	XC866
#define USE_BANK  3								// fix the used registerbank to 3 for XC866 devices
#endif	// XC866

	P1.UINT_Param = DFlash0Sector;
#ifdef	XC88x
	P2.UINT_Param = DFlash1Sector;
#endif	// XC88x
	
#ifdef	XC866
	REG[(4+(USE_BANK*8))] = P1.UBYTE_Param[0];	// DFLASH0 Sector - BANK3 - High Adr Byte
	REG[(3+(USE_BANK*8))] = P1.UBYTE_Param[1];	// DFLASH0 Sector - BANK3 - Low  Adr Byte
#endif	// XC866
#ifdef	XC88x
	REG[(1+(USE_BANK*8))] = P1.UBYTE_Param[0];	// DFLASH0 Sector -         High Adr Byte
	REG[(0+(USE_BANK*8))] = P1.UBYTE_Param[1];	// DFLASH0 Sector -         Low  Adr Byte
	REG[(4+(USE_BANK*8))] = P2.UBYTE_Param[0];	// DFLASH1 Sector  
	REG[(3+(USE_BANK*8))] = P2.UBYTE_Param[1];	// DFLASH1 Sector  
#endif	// XC88x
	REG[(5+(USE_BANK*8))] = 0;					// PFLASH  
	REG[(6+(USE_BANK*8))] = 0;					// PFLASH  
	REG[(7+(USE_BANK*8))] = 0;					// PFLASH  

#ifdef XC88x
	PUSH(PSW);
	PSW = ((USE_BANK)<<3);
#endif	// XC88x

#ifdef	__C51__
	((void (code *) (void)) FLASH_ERASE) ();
#endif	// __C51__
#ifdef	SDCC
_asm
	LCALL FLASH_ERASE;
_endasm;
#endif	// SDCC

#ifdef	XC866
	return(!CY);
#endif	// XC866
#ifdef	XC88x
	success = CY;
	POP(PSW);
	return (!success);
#endif	// XC88x
}
#endif // ifndef XC878


//---------------------------------------- XC878 ------------------------------------------------------------
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//     FLASH Erase                XC878
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifdef	XC878
void InitMemExtension (void)							// should be called once before using FLASH routines!
{
#ifdef	K64		
	    MEX1 = 0x00;									// NextBank 0 / Current Bank 0 
		MEX2 = 0x80;									// Ensure that all MOVC command are using Bank 0 
		MEX3 = 0x1F;									// Ensure all MOVX access XRAM Bank F 		
#endif
#ifdef	K52								
	    MEX1 = 0x00;									// NextBank 0 / Current Bank 0  
		MEX2 = 0x00;									// Ensure that all MOVC command are using Bank 0 
		MEX3 = 0x00;									// Ensure all MOVX access XRAM Bank 0 	
														// MEX1 seems to be overwritten, if debugger is active ( KEIL V8.12c ) 
#endif
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//     FLASH Erase                XC878
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bit FLASH_Erase (unsigned char code* FlashDstAddr,unsigned char KindOfErase)
{
	volatile bit tmpEA, success;						// bit tmpEA --> overwrites CY ( in KEIL )
														// that's why use second var

	(EA)?(tmpEA = 1,EA=0):(tmpEA = 0);					// save EA bit for restoring at end
														// required by UM
	 ACC = KindOfErase;									// desire MASS or PAGE erase 

	DPTR = (unsigned int) FlashDstAddr;

#ifdef	K64
	MEX1 = 0x02;
#endif  // K64
#ifdef	__C51__
	((void (code *) (void)) FLASH_ERASE) ();			// BROM call KEIL
#endif	// __C51__
#ifdef	SDCC
_asm
	LCALL FLASH_ERASE;									// BROM call SDCC
_endasm;
#endif	// SDCC
#ifdef	K64
	MEX1 = 0x00;
#endif  // K64
	success = CY;
	EA = tmpEA;											// restore old EA state either '0' or '1' 
	return(!success);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//     FLASH Prog                XC878
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bit FLASH_Prog (unsigned char code * DestWordLine, unsigned char NrOfBytes)	
{
	volatile bit tmpEA, success;						// bit tmpEA --> overwrites CY ( in KEIL )
														// that's why use second var

	(EA)?(tmpEA = 1,EA=0):(tmpEA = 0);					// save EA bit for restoring at end
														// required by UM

#ifdef	K64
	MEX1 = 0x02;
#endif  // K64

	REG[0x0001] = NrOfBytes;							// Number of bytes to be programmed - max. 32 DFLASH

	EO |= 0x01;											// select DPTR1 to hold Buffer Address
	DPTR = (unsigned int)XRAM_BUFFER_ADDR;
	EO &= ~(0x01);										// ensure DPTR0 is set as active before leave

	DPTR = (unsigned int)DestWordLine;

#ifdef	__C51__	
	((void (code *) (void)) FLASH_PROG) ();				// BROM call KEIL
#endif	// __C51__
#ifdef	SDCC
_asm
	LCALL FLASH_PROG;									// BROM call SDCC
_endasm;
#endif	// SDCC

#ifdef	K64
	MEX1 = 0x00;
#endif  // K64
	success = CY;
	EA = tmpEA;											// restore old EA state either '0' or '1' 
	return(!success);
}
#endif	// XC878








