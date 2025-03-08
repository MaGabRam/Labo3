#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

int
main(void)
{
    
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);

  
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

   
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)) {}

    
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1); // PN0 y PN1
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4); // PF0 y PF4

    
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, 0x00); // Apaga PN0 y PN1
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, 0x00); // Apaga PF0 y PF4

    
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC); 
    TimerLoadSet(TIMER0_BASE, TIMER_A, 240000000);   
    TimerEnable(TIMER0_BASE, TIMER_A);               

    
    while(1)
    {
        
        while(!TimerIntStatus(TIMER0_BASE, false)) {}

        
        TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

        
        static uint8_t state = 0;
        switch (state)
        {
            case 0:
                GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0); 
                GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x00);       
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0); 
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x00);       
                break;
            case 1:
                GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x00);       
                GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1); 
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x00);       
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4); 
                break;
            case 2:
                GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0); 
                GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x00);       
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x00);       
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4); 
                break;
            case 3:
                GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x00);       // Apaga PN0
                GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1); // Enciende PN1
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0); // Enciende PF0
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x00);       // Apaga PF4
                break;
        }

        
        state = (state + 1) % 4;
    }
}
