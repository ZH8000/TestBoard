/**********************************************************************************************************
**	 FlashHandlerConfig.h   XC866-2FR/4FR Step BB and higher 
**                          XC88x-6FF/8FF Step AB and higher
**                          XC878-13FF/17FF
**---------------------------------------------------------------
**   Note: If a newer step should be used, 
**         contact Infineon to ensure that the right addresses 
**         for the Boot ROM subroutines are in use !
**--------------------------------------------------------------- 
**   Infineon Technologies 2008
**********************************************************************************************************/
#ifndef __FLASHHANDLERCONFIG_H__
#define __FLASHHANDLERCONFIG_H__

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// User Configuration Section Begin //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Select general device type       //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//#define								XC866
#define								XC88x
//#define								XC878_13FF	// 52K device
//#define								XC878_16FF	// 64K device				

/*=============================================================================================
  NOTE: This section is only valid for XC88x devices !!
===============================================================================================*/
#define USE_BANK					3		// Register Bank ( 0 - 3 ) used during Program / Erase
											// Default = 3

/*==========================================
   Set start address of Wordline buffer
==========================================*/
#define WORDLINE_BUFFER_ADDRESS		0xE0	// start address of wordline buffer XC866/88x in IRAM 
	                                        // start address of wordline buffer XC878     in XRAM,
											// where Highbyte is fixed to 0xFB --> results in 0xFBE0 for XC878 64k
											//                            0xEB -->            0xEBE0 for XC878 52k
// ***------------------------------------------------***
// *** Boot ROM - entry points for the flash routines ***
// ***------------------------------------------------***
#define FLASH_ERASE					0xDFF9  // Erase Flash Bank						XC866 / XC88x / XC878
#define FLASH_PROG					0xDFF6  // Program Flash Bank.					XC866 / XC88x / XC878
#ifndef	XC878
#define FLASH_ERASE_ABORT			0xDFF3  // Abort the on going erase process		XC866 / XC88x  
#define FLASH_READ_STATUS			0xDFF0  // Read Flash Status					XC866 / XC88x
#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// User Configuration Section End   //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#endif	// __FLASHHANDLERCONFIG_H__
