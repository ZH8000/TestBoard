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


//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"
#include "PinDefine.h"
#include "DeviceController.h"
#include <string.h>
#include <stdio.h>
#include "FlashUtils.h"

#define MAX_COMMAND_LENGTH		100
#define MAX_RESPONSE_LENGTH		200



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


void UART_vInit(void)
{
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

static char xdata receiveBuffer[MAX_COMMAND_LENGTH] = {0};
static int bufferCount = 0;

void sendUART(char * message) {
	char * current = message;
	while (*current != '\0') {
		SBUF = *current;
		while (TI == 0);
		TI = 0;		
		current++;
	}
}

void processCommand(char * command) {
	
	int commandSize = strlen(command);
	char xdata respondMessage[MAX_RESPONSE_LENGTH] = {0};
	bool isNormalCommand = commandSize == 5 && command[0] == '$' && command[2] == '$' && command[4] == '$';
	bool isSetUUIDCommand = commandSize == 40 && command[0] == '$' && command[1] == 'f' && command[2] == '$' && command[39] == '$';
	
	memset(respondMessage, 0, MAX_RESPONSE_LENGTH);	

	if (isNormalCommand) {
		switch(command[1]) {
			case 'a':
				enableLCRChannel(command[3]);
				break;
			case 'b':
				enableLCChannel(command[3]);
				break;
			case 'c':
				setChargeMode(command[3]);
				break;
			case 'd':
				sendHVRelayStatus();
				break;
			case 'e':
				setHVMonitorMode(command[3]);
				break;
			case 'f':
				sendUUID();
				break;
			default:
				sendUART("Unknown Command\r\n");
		}		
	} else if (isSetUUIDCommand) {
		setUUID(command);
		sendUART("DONE\r\n");
	} else {
		sendUART("Unknown Command\r\n");
	}
}

void UART_viIsr(void) interrupt UARTINT
{
	// switch to page 0
  SFR_PAGE(_su0, SST0);
  if (TI)
  {
		TI = 0;
  }
  if (RI)
  {
		char receiveByte = SBUF;
		if (receiveByte == '\r' || receiveByte == '\n' || bufferCount >= MAX_COMMAND_LENGTH-1) {
			processCommand(receiveBuffer);
			memset(receiveBuffer, 0, MAX_COMMAND_LENGTH);			
			bufferCount = 0;
		} else {
			receiveBuffer[bufferCount] = receiveByte;
			bufferCount++;
		}
    RI = 0;
  }

	// restore the old page
  SFR_PAGE(_su0, RST0);
}
