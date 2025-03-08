#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

//*****************************************************************************
//
// Blink the on-board LED.
//
//*****************************************************************************
int
main(void)
{
    // Configura el reloj del sistema a 120 MHz
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);

    // Habilita el periférico GPIO para el puerto N
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

    // Espera a que el periférico esté listo
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
    {
    }

    // Configura los pines PN0 y PN1 como salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    while(1)
    {
        // Enciende el LED en PN0
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        
        // Retardo de 1 segundo (aproximadamente)
        SysCtlDelay(120000000 / 3);
        
        // Enciende el LED en PN1
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
        
        // Retardo de 1 segundo (aproximadamente)
        SysCtlDelay(120000000 / 3);
        
        // Apaga ambos LEDs
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, 0x00);
        
        // Retardo de 1 segundo (aproximadamente)
        SysCtlDelay(120000000 / 3);
    }
    
    return 0; 
}
