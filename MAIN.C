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

#include "MAIN.H"
#include "DeviceController.h"

#include <stdio.h>
#include <string.h>

bool shouldMonitorHVStatus = 0;

void MAIN_vInit(void)
{
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


    //// Interrupt structure 2 mode 0 is selected.
    //// Interrupt service routine choice 2 is selected.
    //   globally enable interrupts
    EA            =  1;           

} 
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
    MAIN_vInit();

    while(1) {

        if (shouldMonitorHVStatus && !isAllHVRelayOK()) {
            sendUART("HV_NG\r\n");
        }

        delay(1);
    }
}
