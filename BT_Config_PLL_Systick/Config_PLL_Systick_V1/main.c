#include "Gpio.h"
#include "Softtimer.h"

int main(void)
{
	
	
	Change_Clock();
	/** Call Function intialize led and button */
	Gpio_Init();
	/**	call Function Interrupt	*/
	PORTC_IRQHandler();
	
	
	Softtimer_Init();
	//Softtimer_StartTimer(Timer1,1,5000,CONTINUOUS,&Turn_off_blue);
	
	ClearAllLed();
	Gpio_SetPinValue(GPIOD,PIN0,LEVEL_LOW);	/*	Turn on led Blue after pressed button reset	*/

	Softtimer_StartTimer(ID_Sofftimer0,T5_Second,ONESHOT,&Turn_off_blue);
	
	Softtimer_StartTimer(ID_Softtimer1,T1_Second,CONTINUOS,&Function_Program_1);
	
	Softtimer_StartTimer(ID_Softtimer2,T500_Milisecond,CONTINUOS,&Function_Program_2);
	
		while(1)
	{
		/*	Call Soft_Mainfunction	*/
		Softtimer_Mainfunction();
	}
}
