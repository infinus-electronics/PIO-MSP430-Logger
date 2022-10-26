#include "spi.h"
#include <msp430g2452.h>

int SPIInit()
{
    //SPI Config
    USICTL0 = 0b11101010;
    USICTL1 = 0b10000000; //disabled counter interrupt
    USICKCTL = 0b10001000; // choose full speed smclk
    P1DIR |= (1 << 5 | 1 << 6); //set mosi to output
    // USICKCTL = 0b10001000; // choose div16 for debug
    return 0;
}
char SPITransfer(uint8_t data)
{
    USISR = data;
    USICNT |= 8;
    while ((USICTL1 & 1) == 0);
    char res = USISR;
    return res;
}