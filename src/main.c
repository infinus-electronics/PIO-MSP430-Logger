// #define DEBUG

#include <msp430g2452.h>

#include <stdint.h>
// #include <stdio.h>
#include <spi.h>
#include <uart.h>
// #include <stdlib.h>

#include <pff.h>

#ifdef DEBUG
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
#endif

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

    // BCSCTL1 |= 0b1111; // select 16MHz mode
    BCSCTL1 = CALBC1_16MHZ; // Set range
    DCOCTL = CALDCO_16MHZ;  // SMCLK = DCO = 16MHz

    P1DIR |= (1 | 1 << 6); // set LED at P1.0 to output and MOSI to output
    P1OUT &= ~0x01;

    // char *ptr;
    // char outstr[128]; // line buffer
    char *outstr = malloc(128); //for some reason it needs this malloc to work???
    // long p1, p2;
    BYTE res = 0;
    UINT s1, s2, s3, ofs, cnt, w;
    FATFS fs;    /* File system object */
    DIR dir;     /* Directory object */
    FILINFO fno; /* File information */

    // #ifdef DEBUG
    uart_init();

    // uart_puts("\nPFF test monitor\n");
    // res = disk_initialize();
    // uart_putc(res+48);
    // uart_puts("\n");
    

    uart_puts("\nMounting Test\n");

    res = (char)pf_mount(&fs);
    // uart_putc(res+48);
    // uart_puts("\n");

    uart_puts("\nFile Opening Test\n");

    res = (char)pf_open("001");
    // uart_putc(res+48);
    // uart_puts("\n");

    uart_puts("\nFile Read Test\n");

    char data;
    res = pf_read(&data, 1, &s1);
    // uart_putc(res+48);
    // uart_puts("\n");
    // uart_putc(data);
    // uart_puts("\n");

    uart_puts("\nlseek Test\n");

    res = pf_lseek(3);
    // uart_putc(res+48);
    // uart_puts("\n");

    pf_lseek(128);
    int k;
    if (res){
        for ( k = 0; k < 128; k++)
    {
        *(outstr+k) = 0x42;/* code */
    }
    }
    else{
        for ( k = 0; k < 128; k++)
    {
        *(outstr+k) = 0x43;/* code */
    }
    }
    
    // uart_puts(outstr);
    

    uart_puts("\nFile Write Test\n");

    res = pf_write(outstr, 128, &w);
    pf_write(0, 0, &w);
    // uart_putc(res+48);
    // uart_puts("\n");

    pf_lseek(512); //we have a minimum of 512 to do this...
    res = pf_write("EFGH", 5, &w);
    pf_write(0, 0, &w);
    // uart_putc(res+48);
    // uart_puts("\n");

    // #endif





    
    while (1)
    { // test transmit
    }

    return 0;
}
