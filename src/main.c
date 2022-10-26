#include <msp430g2452.h>

#include <stdint.h>
#include <stdio.h>
#include <spi.h>
#include <uart.h>

#include <pff.h>

/**
 * main.c
 */

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

    // BCSCTL1 |= 0b1111; // select 16MHz mode
    BCSCTL1 = CALBC1_16MHZ; // Set range
    DCOCTL = CALDCO_16MHZ;  // SMCLK = DCO = 16MHz

    P1DIR |= (1 | 1 << 6); // set LED at P1.0 to output and MOSI to output

    P1OUT |= 0x01; // turn on LED to signal life

    char *ptr;
    char outstr[128]; //line buffer
	long p1, p2;
	BYTE res;
	UINT s1, s2, s3, ofs, cnt, w;
	FATFS fs;			/* File system object */
	DIR dir;			/* Directory object */
	FILINFO fno;		/* File information */

    uart_puts("\nPFF test monitor\n");
    res = disk_initialize();
    sprintf(outstr, "rc=%d\n", res);
    uart_puts(outstr);



    while (1)
    { // test transmit
        
    }

    return 0;
}
