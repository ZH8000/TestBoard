#ifndef __DEVICE_CONTROLLER_H__
#define __DEVICE_CONTROLLER_H__

#include "MAIN.H"

void enableLCChannel(char channelCode);
void enableLCRChannel(char channelCode);
bool isAllHVRelayOK();
void sendHVRelayStatus();
void setChargeMode(char modeCode);
void setHVMonitorMode(char modeCode);
void sendUUID();
void setUUID(char * command);
#endif
