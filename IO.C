//****************************************************************************
// @Module        GPIO
// @Filename      IO.C
// @Project       TestBoard.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC888CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 1.7
//
// @Description:  This file contains functions that use the IO module.
//
//----------------------------------------------------------------------------
// @Date          2016/3/15 16:17:36
//
//****************************************************************************

//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"
#include "PinDefine.h"

//****************************************************************************
// @Function      void IO_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the IO function 
//                library. It is assumed that the SFRs used by this library 
//                are in their reset state. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2016/3/15
//
//****************************************************************************

// USER CODE BEGIN (IO_Init,1)

// USER CODE END

void IO_vInit(void)
{
	#ifdef STARTER_KIT_EMU
		P1_DIR        		= 0x04; 
		P1_DATA       		= 0x00;
		P3_DIR			  		= 0xFF;
		P3_DATA						= 0x00;
	#else

		///  -----------------------------------------------------------------------
		///  Configuration of Port P0:
		///  -----------------------------------------------------------------------
		///  - no pin of port P0 is used


		///  -----------------------------------------------------------------------
		///  Configuration of Port P1:
		///  -----------------------------------------------------------------------
		///  P1.0:
		///  - is used as general purpose output
		///  - push/pull output is selected
		///  - the pin status is low level
		///  - pull-up device is assigned
		///  P1.1:
		///  - is used as general purpose output
		///  - push/pull output is selected
		///  - the pin status is low level
		///  - pull-up device is assigned
		///  P1.2:
		///  - is used as general purpose output
		///  - push/pull output is selected
		///  - the pin status is low level
		///  - pull-up device is assigned
		///  P1.3:
		///  - is used as general purpose output
		///  - push/pull output is selected
		///  - the pin status is low level
		///  - pull-up device is assigned
		///  P1.4:
		///  - is used as general purpose output
		///  - push/pull output is selected
		///  - the pin status is low level
		///  - pull-up device is assigned
		///  P1.5:
		///  - is used as general purpose output
		///  - push/pull output is selected
		///  - the pin status is low level
		///  - pull-up device is assigned


		P1_DIR        =  0x3F;         // load direction register

		///  -----------------------------------------------------------------------
		///  Configuration of Port P2:
		///  -----------------------------------------------------------------------
		///  - no pin of port P2 is used


		///  -----------------------------------------------------------------------
		///  Configuration of Port P3:
		///  -----------------------------------------------------------------------
		///  P3.4:
		///  - is used as general purpose output
		///  - push/pull output is selected
		///  - the pin status is low level
		///  - pull device is disabled (tristate) 
		///  P3.5:
		///  - is used as general purpose output
		///  - push/pull output is selected
		///  - the pin status is low level
		///  - pull device is disabled (tristate) 
		///  P3.6:
		///  - is used as general purpose output
		///  - push/pull output is selected
		///  - the pin status is low level
		///  - pull device is disabled (tristate) 
		///  P3.7:
		///  - is used as general purpose output
		///  - push/pull output is selected
		///  - the pin status is low level
		///  - pull device is disabled (tristate) 


		P3_DIR        =  0xF0;         // load direction register

		///  -----------------------------------------------------------------------
		///  Configuration of Port P4:
		///  -----------------------------------------------------------------------
		///  P4.0:
		///  - is used as general input
		///  - pull device is disabled (tristate) 
		///  P4.1:
		///  - is used as general input
		///  - pull device is disabled (tristate) 
		///  P4.2:
		///  - is used as general input
		///  - pull-up device is assigned
		///  P4.3:
		///  - is used as general input
		///  - pull device is disabled (tristate) 
		///  P4.4:
		///  - is used as general input
		///  - pull device is disabled (tristate) 
		///  P4.5:
		///  - is used as general input
		///  - pull device is disabled (tristate) 


		///  -----------------------------------------------------------------------
		///  Configuration of Port P5:
		///  -----------------------------------------------------------------------
		///  - no pin of port P5 is used
	#endif

} //  End of function IO_vInit
