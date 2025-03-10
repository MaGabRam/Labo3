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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

   
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)) {}

    
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1); // PN0 y PN1
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4); // PF0 y PF4

    
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1); // PJ0 (USR_SW1) y PJ1 (USR_SW2)

   
    GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, 0x00); // Apaga PN0 y PN1
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, 0x00); // Apaga PF0 y PF4

 int cont=0;

    
    while(1)
    {
        
        uint8_t buttonState = GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1);

            
        if ((buttonState & GPIO_PIN_0) == 0x00) // Si PJ0 está en bajo (presionado)
        {
            cont++;
            SysCtlDelay(120000000 / 3);
        }

        
        if ((buttonState & GPIO_PIN_1) == 0x00) // Si PJ1 está en bajo (presionado)
        {
            cont--;
            SysCtlDelay(120000000 / 3);
        }
        if(cont>=4){
        	cont=4;
        }
        if(cont<=0){
        	cont=0;
        }
        if(cont<=0){
                    // Apaga todos los LEDs
		    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, 0x00);
		    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, 0x00);
		    }
        if(cont==1){
                    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
                    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x00); // Enciende PN0
		    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x00);
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x00);
                    
	}
        if(cont==2){
                    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
                    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0); // Enciende PN0
		    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x00);
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x00);
	}
	if(cont==3){
                    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
                    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0); // Enciende PN0
		    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x00);
	}
	if(cont==4){
                    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
                    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0); // Enciende PN0
		    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
	}
    }
}
