#include "Gpio_Register.h"
#include "Gpio.h"



/**	Function : Set value Pin */
void Gpio_SetPinValue(GPIO_Type* GPIO_Port, E_GPIO_Pin_Type GPIO_PinNum_E, const unsigned int GPIO_Value)
{

	
		if (GPIO_Value == 1u)	
			{
				GPIO_Port->PDOR	|= (1u << GPIO_PinNum_E);	
			}
			else if (GPIO_Value == 0u)
			{
				GPIO_Port->PDOR	&=	~(1u << GPIO_PinNum_E);
			}
}


/**	Function : Get value Pin */
void Gpio_GetPinValue(GPIO_Type* GPIO_Port, E_GPIO_Pin_Type GPIO_PinNum_E,unsigned int* GPIO_value)
{
	*GPIO_value = (GPIO_Port->PDIR >> GPIO_PinNum_E) & 1u;	
}


/**	Read value Bit of PORT	*/
unsigned int	Port_ReadBitValue(PORT_Type* PORT_PCRn,E_GPIO_Pin_Type PORT_PinNum_E, unsigned int PORT_BitField)
{
	unsigned int Bit_Value = (PORT_PCRn->PCR[PORT_PinNum_E] >> PORT_BitField  & 1u);
	
	return Bit_Value;
}

/**	Write value Bit of PORT	*/
void	Port_WriteBitValue(PORT_Type* PORT_PCRn, E_GPIO_Pin_Type PORT_PinNum_E,unsigned int PORT_BitField, unsigned int PORT_Value)
{
	if (PORT_Value == 1u)
	{
		PORT_PCRn->PCR[PORT_PinNum_E] |= (1u << PORT_BitField);
	}
	else
		PORT_PCRn->PCR[PORT_PinNum_E]	&=	~(1u<< PORT_BitField);
}

/**		Clear all Led		*/
void	ClearAllLed(void)
{
	Gpio_SetPinValue(GPIOD, PIN0, LEVEL_HIGH);  /*  Turn off led_blue */
	Gpio_SetPinValue(GPIOD, PIN15, LEVEL_HIGH); /*  Turn off led_red  */
	Gpio_SetPinValue(GPIOD, PIN16, LEVEL_HIGH);	/*  Turn off led_green  */
}



/**	Function :Intinialize Button and Led	*/
void Gpio_Init(void)
{
		/* Pins definitions
	* ===================================================
	* Pin number        | Function
	* ----------------- |------------------
	* PTC12             | GPIO [BUTTON1]
	* PTC13             | GPIO [BUTTON2]
	*/
	/*	1.	Setting clocking	*/
	PCC->PCC_PORTC |= (1u<<30u);							/*	CGC: bit 30 ,Enable clock for PORTC	*/
	
	/*	2.	Set pin as GPIO function	*/
	PORTC->PCR[BUTTON1]	|= (1u<<8u);						/*	MUX: bits 8-10 */
	PORTC->PCR[BUTTON2]	|= (1u<<8u);						/*	MUX: bits 8-10 */
	
	/*	3.	Disable Pull-up/pull-down	*/
	PORTC->PCR[BUTTON1]	&=	~(1u<<1u);						/*	PE: bit 1	*/
	PORTC->PCR[BUTTON2]	&=	~(1u<<1u);						/*	PE: bit 1	*/
		
	/*	4.	Set interrupt type */
	PORTC->PCR[BUTTON1]	|= (10u<<16u);						/*	IRQC: bit 16-19,Set interrupt falling edge */
	PORTC->PCR[BUTTON2]	|= (10u<<16u);						/*	IRQC: bit 16-19,Set interrupt falling edge */
	
	/*	5.	Set input Pin	*/
	GPIOC->PDDR	&=	~(1u<<BUTTON1);							/*	Set Input for pin12 of PORTC	*/
	GPIOC->PDDR	&=	~(1u<<BUTTON2);							/*	Set Input for pin13 of PORTC	*/
	
	/*	Enable NVIC for port C	*/
	NVIC->ISER[1]	|= (1u<<29u);
	/*	32 + 29 = 61 => ID NVIC interrupt of PORTC- table excel attack Reference manual*/
	
	
	/* Pins definitions
	* ===================================================
	* Pin number        | Function
	* ----------------- |------------------
	* PTD0              | GPIO [BLUE LED]
	* PTD15             | GPIO [RED LED]
	* PTD16             | GPIO [GREEN LED]
	*/

	/* 1.  Setting Clocking */
	PCC->PCC_PORTD |= (1u<<30u);				/* CGC: bit 30, Enable clock for PORTD */
	/* 2. Set pins as GPIO function */
	PORTD ->PCR[LED_BLUE]  |= (1<<8u);
	PORTD ->PCR[LED_RED] 	 |= (1<<8u);
	PORTD ->PCR[LED_GREEN] |= (1<<8u);

	/* 3. Set pins as output pin */
	GPIOD ->PDDR |= (1<<0u);
	GPIOD ->PDDR |= (1<<15u);
	GPIOD ->PDDR |= (1<<16u);
	
}



unsigned int mode_program = 0u;		/*	Define 1 variable then declare this variable at file.header to use other file*/

static int Flag_blue = 1;			/*	Flag 5 seconds after pressing reset button	*/

/**	
 * Function turn_off_blue
 * ======================	
*/
void	Turn_off_blue	(void)
{
	Gpio_SetPinValue(GPIOD,PIN0,LEVEL_HIGH);
	Flag_blue = 0;
}

/**
  * Process mode_program 1:
============================================
  * RED(~1s) => BLUE(~1s) => GREEN(~1s)
*/
void Function_Program_1 (void)
{
  if (mode_program == PROGRAM1)
  {
    static int step_mode1 = 1;
    if (step_mode1 == 1)
    {
          Gpio_SetPinValue(GPIOD, PIN15, LEVEL_LOW);                                                  /*  Turn On led_red  */
					Flag_blue?Gpio_SetPinValue(GPIOD,PIN0,LEVEL_LOW):Gpio_SetPinValue(GPIOD,PIN0,LEVEL_HIGH);   /*  Check flag_blue if = 1 then turn on led_blue, otherwise turn off led_blue */
          Gpio_SetPinValue(GPIOD, PIN16, LEVEL_HIGH);                                                 /*  Turn off led_green  */
          step_mode1 = 2;
    }
    else if (step_mode1 == 2)
    {
          Gpio_SetPinValue(GPIOD, PIN15, LEVEL_HIGH);
          Gpio_SetPinValue(GPIOD, PIN0, LEVEL_LOW);
          Gpio_SetPinValue(GPIOD, PIN16, LEVEL_HIGH);
          step_mode1 = 3;
    }
    else if (step_mode1 == 3)
    {
          Gpio_SetPinValue(GPIOD, PIN15, LEVEL_HIGH);
          Flag_blue?Gpio_SetPinValue(GPIOD,PIN0,LEVEL_LOW):Gpio_SetPinValue(GPIOD,PIN0,LEVEL_HIGH);
          Gpio_SetPinValue(GPIOD, PIN16, LEVEL_LOW);
          step_mode1 = 1;
    }
  }
}

/**
 * process	mode_program 2:
============================================
 * GREEN(~0.5s) <=> RED(~0.5s)
*/		
void Function_Program_2  (void)
{
  if (mode_program == PROGRAM2)
  {
    static int step_mode2 = 1;
    if (step_mode2 == 1)
    {
          Gpio_SetPinValue(GPIOD, PIN15, LEVEL_LOW);
          Gpio_SetPinValue(GPIOD, PIN16, LEVEL_HIGH);
					Flag_blue?Gpio_SetPinValue(GPIOD,PIN0,LEVEL_LOW):Gpio_SetPinValue(GPIOD,PIN0,LEVEL_HIGH);
			
          step_mode2 = 2;
    }
    else if (step_mode2 == 2)
    {
          Gpio_SetPinValue(GPIOD, PIN15, LEVEL_HIGH);
          Gpio_SetPinValue(GPIOD, PIN16, LEVEL_LOW);
					Flag_blue?Gpio_SetPinValue(GPIOD,PIN0,LEVEL_LOW):Gpio_SetPinValue(GPIOD,PIN0,LEVEL_HIGH);
          step_mode2 = 1;
    }
  }
}
