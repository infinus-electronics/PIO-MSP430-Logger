#include <msp430g2452.h>

#include <stdint.h>
#include <spi.h>
#include <uart.h>

// #include <pff.h>

/**
 * main.c
 */



int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    // BCSCTL1 |= 0b1111; // select 16MHz mode
    BCSCTL1 = CALBC1_16MHZ;			// Set range
	DCOCTL = CALDCO_16MHZ;			// SMCLK = DCO = 1MHz  

    P1DIR |= (1 | 1 << 6); //set LED at P1.0 to output and MOSI to output
    P2DIR |= 1 << 3; //set CS to output
    P1OUT |= 0x01; //turn on LED to signal life
    SPIInit();
    uart_init();

    while (1)
    { //test transmit
        uint8_t res = SPITransfer(0x41);
        SPITransfer(res);
        uart_puts("A");
    }

    return 0;
}
