#ifndef SPI
#define SPI

#include <stdint.h>

int SPIInit();
uint8_t SPITransfer(uint8_t data);

#endif