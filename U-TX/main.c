#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "uart0.h"

#define PUSH_BUTTON  (*((volatile uint32_t *)(0x42000000 + (0x400253FC-0x40000000)*32 + 4*4)))
#define PUSH_BUTTON_MASK 16

void initHw()
{
    // Configure HW to work with 16 MHz XTAL, PLL enabled, sysdivider of 5, creating system clock of 40 MHz
    SYSCTL_RCC_R = SYSCTL_RCC_XTAL_16MHZ | SYSCTL_RCC_OSCSRC_MAIN | SYSCTL_RCC_USESYSDIV | (4 << SYSCTL_RCC_SYSDIV_S);

    // Set GPIO ports to use APB (not needed since default configuration -- for clarity)
    SYSCTL_GPIOHBCTL_R = 0;

    // Enable GPIO port F peripherals
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

    // Configure LED and pushbutton pins
     GPIO_PORTF_DEN_R = PUSH_BUTTON_MASK ;  // enable LEDs and pushbuttons
     GPIO_PORTF_PUR_R = PUSH_BUTTON_MASK; // enable internal pull-up for push button
}
/**
 * main.c
 */
void main(void)
{
    initUart0();
    initHw();
    while(1)
    {
    if((GPIO_PORTF_DATA_R & PUSH_BUTTON_MASK)==0)
        putcUart0('g');
    else
        putcUart0('r');
    }

}
