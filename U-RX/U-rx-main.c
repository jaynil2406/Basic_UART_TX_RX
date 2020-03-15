#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "uart0.h"
#include "ledpb.h"


/**
 * main.c
 */
void main(void)
{
    char ch;
       initUart0();
        initHw();
    while(1)
    {

    ch = getcUart0();
    if(ch == 'g')
    {  RED_LED=0; GREEN_LED=1;}
    else
    { GREEN_LED=0;  RED_LED=1;}
    }

}
