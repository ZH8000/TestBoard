#include "DeviceController.h"
#include "PinDefine.h"
#include "UART.h"
#include "FlashUtils.h"
#include <string.h>

#define PREDEFINED_UUID		"bfcf9428-eef6-4261-ae2e-e9d66c7e3d31"
extern bool shouldMonitorHVStatus;


void sendUUID() {
    //char xdata uuidString[50];
    //unsigned char code * currentFlashDataEndAddress = getFlashDataEndAddress();
    //readFlashToBuffer(uuidString, 50, currentFlashDataEndAddress);
    sendUART("#f#");
    sendUART(PREDEFINED_UUID);
    sendUART("#\n");
}

void enableLCChannel(char channelCode) {
    // Switch off all LC / LCR channel first.
    IO_vResetPin(LCR_CHANNEL_1);
    IO_vResetPin(LCR_CHANNEL_2);
    IO_vResetPin(LCR_CHANNEL_3);    
    IO_vResetPin(LC_CHANNEL_1);
    IO_vResetPin(LC_CHANNEL_2);
    IO_vResetPin(LC_CHANNEL_3);

    // Enable coressponding LCR channel GPIO
    switch(channelCode) {
        case '0':
            sendUART("#b#0#\n");
            break;
        case '1':
            IO_vSetPin(LC_CHANNEL_1);
            sendUART("#b#1#\n");
            break;
        case '2':
            IO_vSetPin(LC_CHANNEL_2);
            sendUART("#b#2#\n");            
            break;
        case '3':
            IO_vSetPin(LC_CHANNEL_3);
            sendUART("#b#3#\n");
            break;
        default:
            sendUART("#Unknown LC Channel.#\n");                    
            break;
    }
}

void enableLCRChannel(char channelCode) {
    // Switch off all LC / LCR channel first.
    IO_vResetPin(LCR_CHANNEL_1);
    IO_vResetPin(LCR_CHANNEL_2);
    IO_vResetPin(LCR_CHANNEL_3);
    IO_vResetPin(LC_CHANNEL_1);
    IO_vResetPin(LC_CHANNEL_2);
    IO_vResetPin(LC_CHANNEL_3);

    // Enable coressponding LCR channel GPIO
    switch(channelCode) {
        case '0':
            sendUART("#a#0#\n");
            break;
        case '1':
            IO_vSetPin(LCR_CHANNEL_1);
            sendUART("#a#1#\n");
            break;
        case '2':
            IO_vSetPin(LCR_CHANNEL_2);
            sendUART("#a#2#\n");            
            break;
        case '3':
            IO_vSetPin(LCR_CHANNEL_3);
            sendUART("#a#3#\n");
            break;
        default:
            sendUART("#Unknown LCR Channel.#\n");                   
            break;
    }
}

bool isAllHVRelayOK() {
#ifdef STARTER_KIT_EMU
    return IO_ubReadPin(HV_READY_1);
#else
    return 
        IO_ubReadPin(HV_READY_1) &&
        IO_ubReadPin(HV_READY_2) &&
        IO_ubReadPin(HV_READY_3) &&
        IO_ubReadPin(HV_FAULT_1) &&
        IO_ubReadPin(HV_FAULT_2) &&
        IO_ubReadPin(HV_FAULT_3);
#endif
}

void sendHVRelayStatus() {
    if (IO_ubReadPin(HV_READY_1)) {
        sendUART("HV_READY_1: OK\n");
    } else {
        sendUART("HV_READY_1: NG\n");
    }

    if (IO_ubReadPin(HV_READY_2)) {
        sendUART("HV_READY_2: OK\n");
    } else {
        sendUART("HV_READY_2: NG\n");
    }

    if (IO_ubReadPin(HV_READY_3)) {
        sendUART("HV_READY_3: OK\n");
    } else {
        sendUART("HV_READY_3: NG\n");
    }

    if (IO_ubReadPin(HV_FAULT_1)) {
        sendUART("HV_FAULT_1: OK\n");
    } else {
        sendUART("HV_FAULT_1: NG\n");
    }

    if (IO_ubReadPin(HV_FAULT_2)) {
        sendUART("HV_FAULT_2: OK\n");
    } else {
        sendUART("HV_FAULT_2: NG\n");
    }

    if (IO_ubReadPin(HV_FAULT_3)) {
        sendUART("HV_FAULT_3: OK\n");
    } else {
        sendUART("HV_FAULT_3: NG\n");
    }


    if (isAllHVRelayOK()) {
        sendUART("#d#1#\n");
    } else {
        sendUART("#d#0#\n");            
    }
}

void setChargeMode(char modeCode) {
    if (modeCode == '0') {
        IO_vResetPin(HV_CHANNEL);               
        IO_vSetPin(DISCHARGE_CHANNEL);
        IO_vSetPin(CHARGE_CHANNEL);
        sendUART("#c#0#\n");            
    } else if (modeCode == '1') {
        if (!isAllHVRelayOK()) {
            IO_vResetPin(HV_CHANNEL);                       
            IO_vSetPin(CHARGE_CHANNEL);
            IO_vSetPin(DISCHARGE_CHANNEL);
            sendUART("#d#0#\n");
            return;
        }
        IO_vSetPin(DISCHARGE_CHANNEL);
        IO_vSetPin(HV_CHANNEL);
        IO_vResetPin(CHARGE_CHANNEL);
        sendUART("#c#1#\n");
    } else if (modeCode == '2') {
        IO_vSetPin(CHARGE_CHANNEL);
        IO_vResetPin(HV_CHANNEL);
        IO_vResetPin(DISCHARGE_CHANNEL);
        sendUART("#c#2#\n");
    } else {
        sendUART("#Unknown Charge Mode#\n");            
    }
}

void setHVMonitorMode(char modeCode) {
    if (modeCode == '1') {
        shouldMonitorHVStatus = 1;
        sendUART("#e#1#\n");
    } else if (modeCode == '0') {
        shouldMonitorHVStatus = 0;
        sendUART("#e#0#\n");
    } else {
        sendUART("#Unknown HV Monitor Code#\n");
    }

}

void setUUID(char * command) {
    unsigned char code * flashEndAddress = getFlashDataEndAddress();        
    char xdata uuidString[37] = {0};
    strncpy(uuidString, command+3, 36);
    sendUART("Setting UUID to ");
    sendUART(uuidString);
    sendUART("....\n");
    sendUART("Please wait...");
    writeBufferToFlash(uuidString, &flashEndAddress);
    sendUART("DONE\n");
}
