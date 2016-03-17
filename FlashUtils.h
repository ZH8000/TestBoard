#ifndef __FLASH_UTILS_H__
#define __FLASH_UTILS_H__

unsigned char code * getFlashDataEndAddress();
void writeToFlashPage(char xdata * buffer, unsigned char code ** EECurrentAddr);
void readFlashToBuffer(char xdata * buffer, int n, unsigned char code * EECurrentAddr);
void writeBufferToFlash(char * buffer, unsigned char code ** EECurrentAddr);

#endif