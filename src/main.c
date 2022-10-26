#include <msp430g2452.h>

#include <stdint.h>
#include <stdio.h>
#include <spi.h>
#include <uart.h>

#include <pff.h>

/**
 * main.c
 */

// static void put_rc (FRESULT rc)
// {
// 	const char *p;
// 	static const char str[] =
// 		"OK\0" "DISK_ERR\0" "NOT_READY\0" "NO_FILE\0" "NO_PATH\0"
// 		"NOT_OPENED\0" "NOT_ENABLED\0" "NO_FILE_SYSTEM\0";
// 	FRESULT i;

// 	for (p = str, i = 0; i != rc && pgm_read_byte_near(p); i++) {
// 		while (pgm_read_byte_near(p++)) ;
// 	}
// 	xprintf(PSTR("rc=%u FR_%S\n"), (WORD)rc, p);
// }

void debugLED(int8_t code)
{
    int i = 0;
    for (i = 0; i < code; i++)
    {
        P1OUT |= 0x01;
        __delay_cycles(8000000);
        P1OUT &= ~0x01;
        __delay_cycles(8000000);
    }
    P1OUT |= 0x01;
    __delay_cycles(2000000);
    P1OUT &= ~0x01;
    __delay_cycles(2000000);
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

    // BCSCTL1 |= 0b1111; // select 16MHz mode
    BCSCTL1 = CALBC1_16MHZ; // Set range
    DCOCTL = CALDCO_16MHZ;  // SMCLK = DCO = 16MHz

    P1DIR |= (1 | 1 << 6); // set LED at P1.0 to output and MOSI to output

    char *ptr;
    char outstr[64] = ""; // line buffer
    long p1, p2;
    BYTE res = 0;
    UINT s1, s2, s3, ofs, cnt, w;
    FATFS fs;    /* File system object */
    DIR dir;     /* Directory object */
    FILINFO fno; /* File information */

    uart_init();

    uart_puts("\nPFF test monitor\n");
    res = disk_initialize();
    debugLED((int8_t)res);
    uart_putc(res+48);
    uart_puts("\n");
    

    uart_puts("\nMounting Test\n");

    res = (char)pf_mount(&fs);
    uart_putc(res+48);
    uart_puts("\n");

    uart_puts("\nFile Opening Test\n");

    res = (char)pf_open("001");
    uart_putc(res+48);
    uart_puts("\n");

    uart_puts("\nFile Read Test\n");

    char data;
    res = pf_read(&data, 1, &s1);
    uart_putc(res+48);
    uart_puts("\n");
    uart_putc(data);
    uart_puts("\n");

    uart_puts("\nlseek Test\n");

    res = pf_lseek(3);
    uart_putc(res+48);
    uart_puts("\n");

    pf_lseek(128);

    uart_puts("\nFile Write Test\n");

    res = pf_write("ABCD", 5, &w);
    pf_write(0, 0, &w);
    uart_putc(res+48);
    uart_puts("\n");

    pf_lseek(512); //we have a minimum of 512 to do this...
    res = pf_write("EFGH", 5, &w);
    pf_write(0, 0, &w);
    uart_putc(res+48);
    uart_puts("\n");





    
    while (1)
    { // test transmit
    }

    return 0;
}
