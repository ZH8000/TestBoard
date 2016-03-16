#include "DeviceController.h"
#include "PinDefine.h"
#include "UART.h"

void enableLCChannel(char channelCode) {
	// Switch off all LCR channel first.
	IO_vResetPin(LC_CHANNEL_1);
	IO_vResetPin(LC_CHANNEL_2);
	IO_vResetPin(LC_CHANNEL_3);
	
	// Enable coressponding LCR channel GPIO
	switch(channelCode) {
		case '0':
			sendUART("#b#0#\r\n");
			break;
		case '1':
			IO_vSetPin(LC_CHANNEL_1);
			sendUART("#b#1#\r\n");
			break;
		case '2':
			IO_vSetPin(LC_CHANNEL_2);
			sendUART("#b#2#\r\n");		
			break;
		case '3':
			IO_vSetPin(LC_CHANNEL_3);
			sendUART("#b#3#\r\n");
			break;
		default:
			sendUART("Unknown LC Channel.\r\n");			
			break;
	}
}

void enableLCRChannel(char channelCode) {
	// Switch off all LCR channel first.
	IO_vResetPin(LCR_CHANNEL_1);
	IO_vResetPin(LCR_CHANNEL_2);
	IO_vResetPin(LCR_CHANNEL_3);
	
	// Enable coressponding LCR channel GPIO
	switch(channelCode) {
		case '0':
			sendUART("#a#0#\r\n");
			break;
		case '1':
			IO_vSetPin(LCR_CHANNEL_1);
			sendUART("#a#1#\r\n");
			break;
		case '2':
			IO_vSetPin(LCR_CHANNEL_2);
			sendUART("#a#2#\r\n");		
			break;
		case '3':
			IO_vSetPin(LCR_CHANNEL_3);
			sendUART("#a#3#\r\n");
			break;
		default:
			sendUART("Unknown LCR Channel.\r\n");			
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
	if (isAllHVRelayOK()) {
		sendUART("HV_OK\r\n");
	} else {
		sendUART("HV_NG\r\n");		
	}
}

void setChargeMode(char modeCode) {
	if (modeCode == '1') {
		if (!isAllHVRelayOK()) {
			IO_vResetPin(HV_CHANNEL);			
			IO_vResetPin(CHARGE_CHANNEL);
			IO_vResetPin(DISCHARGE_CHANNEL);
			sendUART("HV_NG\r\n");
			return;
		}
		IO_vResetPin(DISCHARGE_CHANNEL);
		IO_vSetPin(HV_CHANNEL);
		IO_vSetPin(CHARGE_CHANNEL);
		sendUART("#c#1#\r\n");
	} else if (modeCode == '0') {
		IO_vResetPin(CHARGE_CHANNEL);
		IO_vResetPin(HV_CHANNEL);
		IO_vSetPin(DISCHARGE_CHANNEL);
		sendUART("#c#0#\r\n");
	} else {
		sendUART("Unknown Charge Mode\r\n");		
	}
}