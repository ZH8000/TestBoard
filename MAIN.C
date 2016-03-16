//****************************************************************************
// @Module        Project Settings
// @Filename      MAIN.C
// @Project       TestBoard.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC888CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 1.7
//
// @Description   This file contains the Project initialization function.
//
//----------------------------------------------------------------------------
// @Date          2016/3/15 16:17:36
//
//****************************************************************************

// USER CODE BEGIN (MAIN_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"
#include <stdio.h>
#include <string.h>
extern void sendUART(char * message);

// USER CODE BEGIN (MAIN_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (MAIN_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (MAIN_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (MAIN_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************


// USER CODE BEGIN (MAIN_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (MAIN_General,9)

// USER CODE END


//****************************************************************************
// @Function      void MAIN_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This function initializes the microcontroller. It is 
//                assumed that the SFRs are in their reset state.
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

// USER CODE BEGIN (MAIN_Init,1)

// USER CODE END

void MAIN_vInit(void)
{
  // USER CODE BEGIN (MAIN_Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of the System Clock:
  ///  -----------------------------------------------------------------------
  ///  - On Chip Osc is Selected
  ///  - PLL Mode, NDIV =  20
  ///  - input frequency is 9.6 MHz



  //   FCLK runs at 2 times the frequency of PCLK.
  SFR_PAGE(_su1, noSST);         // switch to page1

  CMCON         =  0x10;         // load Clock Control Register

  SFR_PAGE(_su0, noSST);         // switch to page0


  ///  *********************************************************************************
  ///  Note : All peripheral related IO configurations are done in the 
  ///  respective peripheral modules (alternate functions selection)
  ///  *********************************************************************************

  ///  Initialization of module 'GPIO'
  IO_vInit();

  ///  Initialization of module 'UART (Serial Interface)'
  UART_vInit();


  //   Interrupt Priority

  IP            =  0x00;         // load Interrupt Priority Register
  IPH           =  0x00;         // load Interrupt Priority High Register
  IP1           =  0x00;         // load Interrupt Priority 1 Register
  IPH1          =  0x00;         // load Interrupt Priority 1 High Register


  // USER CODE BEGIN (MAIN_Init,3)

  // USER CODE END

  //// Interrupt structure 2 mode 0 is selected.

  //// Interrupt service routine choice 2 is selected.

  //   globally enable interrupts
  EA            =  1;           

} //  End of function MAIN_vInit


//****************************************************************************
// @Function      void main(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the main function.
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

// USER CODE BEGIN (MAIN_Main,1)

// USER CODE END
void delay(int second) {
	int i, j, k;
	for (i = 0; i < second; i++) {
		for (j = 0; j < 25; j++) {
			for (k = 0; k < 30000; k++) {
			}
		}
	}
	
}
void main(void)
{
  // USER CODE BEGIN (MAIN_Main,2)

  // USER CODE END
	int i = 0;
	int j = 0;
	//char message[100];

  MAIN_vInit();

  // USER CODE BEGIN (MAIN_Main,3)

  // USER CODE END
  while(1)
  {
		/*
		IO_vTogglePin(P3_7);
		i++;
		delay(1);
		*/
		if (IO_ubReadPin(P4_4)) {
			IO_vSetPin(P3_7);
		} else {
			IO_vResetPin(P3_7);
			
		}
  // USER CODE BEGIN (MAIN_Main,4)

  // USER CODE END

  }

} //  End of function main


// USER CODE BEGIN (MAIN_General,10)

// USER CODE END

