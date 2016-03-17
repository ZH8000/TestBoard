/**********************************************************************************************************
**	FLASH_Definitions.h
**********************************************************************************************************/
#ifndef __FLASH_DEF_H__
#define __FLASH_DEF_H__

// Intermediate defines for XC878 device(s)
//===========================================
#ifdef		XC878_16FF						// 64K device
#define		XC878							// hold "design" easy
#define		K64
#endif
#ifdef		XC878_13FF						// 52K device
#define		XC878							// hold "design" easy	
#define		K52		
#endif

/*+------------------------------------+
  |   General Fix Section              |
  +------------------------------------+*/
#ifndef	XC878
#define		MAGIC_MEMORY		0x36		// reserve magic memory from D:0x36 .. D:0x3D
#endif		// ifndef XC878
#ifdef	XC878
#define		MAGIC_MEMORY		0x37		// reserve magic memory from D:0x37 .. D:0x3E
#define		PAGE_ERASE			0U
#define		MASS_ERASE			1U
#ifdef		K64
#define		XRAM_BUFFER_ADDR	((0xFB00+(WORDLINE_BUFFER_ADDRESS)))
#endif		// K64
#ifdef		K52
#define		XRAM_BUFFER_ADDR	((0xEB00+(WORDLINE_BUFFER_ADDRESS)))
#endif		// K52
#endif		// XC878

#define		RESERVED_BYTES		0x08		// FlashHandler.c module
#define		BYTES_PER_WORDLINE	32U			// fixed length for data transfer

#ifndef XC878	
#define		BASEADDR			0xA000		// Base address, where the data flash starts 
#endif

#ifdef	XC878
#ifdef	K52
#define		BASEADDR			0xE000		// Base address data flash 52k device
#endif	// K52
#ifdef	K64
#define		BASEADDR			0xF000		// Base address data flash 64k device
#endif	// K64
#endif

//=========================================================================================================
// Calculate the WORDLINE address depending on the passed Wordline Number e.g.
// WORDLINEADDR(117) is calculated as (117d * 0x20h) + 0xA000 = 0xAEA0 --> Sector 7
//=========================================================================================================
#define WORDLINEADDR(AsWLNumber)	(((AsWLNumber)*(BYTES_PER_WORDLINE) + BASEADDR)) 
#ifdef	XC878						// intended for page erase
#define PAGEADDR(AsPageNumber)		((((AsPageNumber)*2*(BYTES_PER_WORDLINE)) + BASEADDR))
#endif 

#ifndef XC878										// These sections are only for XC866/XC88x devices
// Bit Vector Definitions For Sector Erase
//---------------------------------------------
#define SEC0							0x0001
#define SEC1							0x0002
#define SEC2							0x0004
#define SEC3							0x0008
#define SEC4							0x0010
#define SEC5							0x0020
#define SEC6							0x0040
#define SEC7							0x0080
#define SEC8							0x0100
#define SEC9							0x0200
#define SECALL							0x03FF
//-------
// XC866
//-------
#ifdef  XC866
#define DFLASH0							3			// same as Bank 3    For FLASH_Ready()  
#endif  // XC866
//-------
// XC88x
//-------
#ifdef	XC88x 
#define DFLASH0							3			// DFlash 0	For FLASH_Ready()
#define DFLASH1							4			// DFlash 1	For FLASH_Ready()
#endif  // XC88x
#endif  // ifndef XC878

#endif	// __FLASH_DEF_H__
