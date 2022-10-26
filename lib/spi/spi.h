#ifndef SPI
#define SPI

#include <stdint.h>

int SPIInit();
char SPITransfer(uint8_t data);

#endif