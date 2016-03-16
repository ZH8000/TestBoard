//****************************************************************************
// @Module        UART (Serial Interface)
// @Filename      UART.C
// @Project       TestBoard.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC888CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 1.7
//
// @Description:  This file contains functions that use the UART module.
//
//----------------------------------------------------------------------------
// @Date          2016/3/15 16:17:36
//
//****************************************************************************

// USER CODE BEGIN (UART_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (UART_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (UART_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (UART_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (UART_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (UART_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (UART_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (UART_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (UART_General,9)

// USER CODE END


//****************************************************************************
// @Function      void UART_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the UART function 
//                library. It is assumed that the SFRs used by this library 
//                are in their reset state. 
//                
//                The following SFR fields will be initialized:
//                - register SCON
//                - bits SMOD and ES
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

// USER CODE BEGIN (UART_Init,1)

// USER CODE END

void UART_vInit(void)
{
  // USER CODE BEGIN (UART_Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  UART settings
  ///  -----------------------------------------------------------------------
  ///  Pin TXD_1 (P0.2) is selected for transmission
  ///  Pin RXD_1 (P0.1) is selected for reception
  ///  Receiver enabled
  ///  Mode 1: 8-bit data, 1 start bit, 1 stop bit, variable baud rate
  ///  Receiver interrupt flag RI will only be activated if a valid stop bit 
  ///  was received
  ///  BRG is selected for baudrate generation

  SFR_PAGE(_pp2, noSST);         // switch to page 2 without saving
  P0_ALTSEL0   &= ~(ubyte)0x04;  // configure alternate function register 0
  P0_ALTSEL1   |=  (ubyte)0x04;  // configure alternate function register 1
  SFR_PAGE(_pp0, noSST);         // switch to page 0 without saving
  P0_DIR       |=  (ubyte)0x04;  // set output direction


  MODPISEL     |=  (ubyte)0x01;  // configure peripheral input select register
  BCON          =  0x00;         // reset baudrate timer/reload register
  SCON          =  0x70;         // load serial channel control register

  ///  -----------------------------------------------------------------------
  ///  Baudrate generator settings
  ///  -----------------------------------------------------------------------
  ///  input clock = fPCLK
  ///  Fractional divider is enabled
  ///  baudrate = 9.6004 kbaud

  FDSTEP        =  0xD5;         // load fractional divider reload register
  BG            =  0x81;         // load baudrate timer/reload register
  FDCON        |=  0x01;         // load Fractional Divider control register
  BCON         |=  0x01;         // load baud rate control register


  // USER CODE BEGIN (UART_Init,3)

  // USER CODE END

  ///  UART interrupt enabled
  ES = 1;

} //  End of function UART_vInit


//****************************************************************************
// @Function      void UART_viIsr(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the service routine for the UART interrupt. It is 
//                called after each transmission (flag TI set) or reception 
//                (flag RI set) of a data unit.
//                Please note that you have to add application specific code 
//                to this function.
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

//   You have two choices for interrupt type select in Project Settings Page 
//   under Global Settings Section.
//   If you select CHOICE 1 then ISR will be generated with push and pop.
//   If you select CHOICE 2 then ISR will be generated without push and pop.
//   Default choice is CHOICE 2.
//   Current selection is CHOICE 2 

// USER CODE BEGIN (UART_Isr,1)

// USER CODE END

void sendUART(char * message) {
	char * current = message;
	while (*current != '\0') {
		SBUF = *current;
		while (TI == 0);
		TI = 0;		
		current++;
	}
}
void UART_viIsr(void) interrupt UARTINT
{

    // USER CODE BEGIN (UART_Isr,2)

    // USER CODE END
  SFR_PAGE(_su0, SST0);          // switch to page 0
  if (TI)
  {
    // USER CODE BEGIN (UART_Isr,3)

       TI = 0;

    // USER CODE END
  }
  if (RI)
  {
    // USER CODE BEGIN (UART_Isr,4)
			 char receive = SBUF;
			 if (receive == '1') {
				 P1_DATA = 1;
			 } else {
				 P1_DATA = 0;
			 }
       RI = 0;
			 sendUART("ABC\r\n");
			 //SBUF = receive;

    // USER CODE END
  }

    // USER CODE BEGIN (UART_Isr,5)

    // USER CODE END
  SFR_PAGE(_su0, RST0);          // restore the old page
} //  End of function UART_viIsr


// USER CODE BEGIN (UART_General,10)

// USER CODE END

