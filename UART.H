//****************************************************************************
// @Module        UART (Serial Interface)
// @Filename      UART.H
// @Project       TestBoard.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC888CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 1.7
//
// @Description:  This file contains all function prototypes and macros for 
//                the UART module.
//
//----------------------------------------------------------------------------
// @Date          2016/3/15 16:17:36
//
//****************************************************************************


#ifndef _UART_H_
#define _UART_H_

//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void UART_vInit(void);
void sendUART(char * message);

//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

#define UARTINT  4

#endif  // ifndef _UART_H_
