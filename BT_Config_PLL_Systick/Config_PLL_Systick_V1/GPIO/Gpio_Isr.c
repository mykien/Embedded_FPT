#include "Gpio.h"

void PORTC_IRQHandler(void)
{
	
		/* Check interrupt flag of BUTTON1 */
    if (Port_ReadBitValue(PORTC,PIN12,24u))
    {
				Port_WriteBitValue(PORTC, PIN12, 24u, LEVEL_HIGH);	/* Clear interrupt flag for BUTTON1 - Write 1 to clear */
        mode_program = PROGRAM1;    
    }
		/* Check interrupt flag of BUTTON2 */
    if (Port_ReadBitValue(PORTC,PIN13,24u))
    {
       Port_WriteBitValue(PORTC, PIN13, 24u, LEVEL_HIGH); /* Clear interrupt flag for BUTTON2 - Write 1 to clear	*/
        mode_program = PROGRAM2;
    }
}
