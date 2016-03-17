#include "FlashHandler.h"
#include "FlashUtils.h"

#include <string.h>

#define FLASH_FIRST_ADDR       BASEADDR	 	
#define FLASH_LAST_ADDR        WORDLINEADDR(96)
#define FLASH_BANK_TO_CHECK    DFLASH0
#define DFL0_SECTOR_ERASE      SECALL
extern void delay(int second);

unsigned char code * getFlashDataEndAddress() {
  // Initialize the pointer to the FLASH (Checking if there is a valid data)
  unsigned char code * EECurrentAddr = (unsigned char code*)FLASH_LAST_ADDR;
  unsigned char code * EETempAddr;
          
  for (EETempAddr = (unsigned char code*)FLASH_FIRST_ADDR; EETempAddr <= (unsigned char code*)FLASH_LAST_ADDR; EETempAddr += BYTES_PER_WORDLINE)
	{
		if (*EETempAddr == 0)
		{
			EECurrentAddr = EETempAddr;
			break;
		}
	}
	return EECurrentAddr;
}


void writeToFlashPage(char xdata * buffer, unsigned char code ** EECurrentAddr) {
	int i = 0;

	for (i=0; i < BYTES_PER_WORDLINE; i++) {
		WLBuf[i] = *buffer;
		buffer++;
	}

	// Start the Flash Programming
	if (FLASH_Prog(*EECurrentAddr)) 
	{
		*EECurrentAddr = *EECurrentAddr + BYTES_PER_WORDLINE;
	} 
	
}

void readFlashToBuffer(char xdata * buffer, int n, unsigned char code * EECurrentAddr) 
{
	unsigned char code * EETempAddr = (unsigned char code*)FLASH_FIRST_ADDR;
	int i = 0;
	int j = 0;
	int k = 0;
	memset(buffer, 0, n);
	
	while (FLASH_Ready(FLASH_BANK_TO_CHECK) == 0) {;}
	
	while (EETempAddr < EECurrentAddr && j < n) 
	{	
		i = 0;
		while (*(EETempAddr+i) != 0) {
			buffer[j] = *(EETempAddr+i);
			i++;
			j++;
		}
		EETempAddr = EETempAddr + BYTES_PER_WORDLINE;		
	}	
}

void writeBufferToFlash(char * buffer, unsigned char code ** EECurrentAddr) {
	char xdata pageBuffer[BYTES_PER_WORDLINE] = {0};
	char * currentCharacter = buffer;
	int i = 0;
	
	FLASH_Erase(SECALL,0);
	*EECurrentAddr = (unsigned char code*)FLASH_FIRST_ADDR;			// if erase than 1. WL is current
  delay(2);
	
	memset(pageBuffer, 0, BYTES_PER_WORDLINE);
	while (*currentCharacter != 0) {
		
		pageBuffer[i] = *currentCharacter;
		if (i == 25) {
			writeToFlashPage(pageBuffer, EECurrentAddr);
			memset(pageBuffer, 0, BYTES_PER_WORDLINE);
			i = 0;
		} else {
			i++;
		}
		currentCharacter++;
	}
	writeToFlashPage(pageBuffer, EECurrentAddr);	
}
