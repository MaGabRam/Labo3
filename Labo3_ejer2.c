#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

//*****************************************************************************
// Función de manejo de errores (solo en modo DEBUG)
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

//*****************************************************************************
// Función principal
//*****************************************************************************
int
main(void)
{
  
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);

   
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {}

   
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);

   
    while(1)
    {
       
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0); // Enciende PN0
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0); // Enciende PF0
        SysCtlDelay(120000000 / 3); // Retardo de ~1 segundo

       
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1); // Enciende PN1
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4); // Enciende PF4
        SysCtlDelay(120000000 / 3); // Retardo de ~1 segundo

        
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x00); // Apaga PN0
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x00); // Apaga PF0
        SysCtlDelay(120000000 / 3); // Retardo de ~1 segundo

        
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x00); // Apaga PN1
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x00); // Apaga PF4
        SysCtlDelay(120000000 / 3); // Retardo de ~1 segundo
    }
}
