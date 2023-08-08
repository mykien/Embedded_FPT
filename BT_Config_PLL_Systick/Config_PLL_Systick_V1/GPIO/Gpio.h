#ifndef _GPIO_H_
#define	_GPIO_H_
#include "Gpio_Register.h"


/** =================Define===========================	*/

#define LED_BLUE			(0u)
#define LED_RED				(15u)
#define	LED_GREEN			(16u)
#define	BUTTON1				(12u)
#define BUTTON2				(13u)

#define	LEVEL_HIGH		(1u)	
#define	LEVEL_LOW			(0u)

#define PROGRAM1			(1u)
#define	PROGRAM2			(2u)

/**	define time count */
#define T_HALF_1S				(T_1S / 2)
#define	T_1S						(150000u)
#define	T_2S						(T_1S * 2u)
#define	T_3S						(T_1S * 3u)
#define	T_5S						(T_1S	* 5u)




/** =================Variable===========================	*/

/** decaleration extern variable mode_program 	*/
extern unsigned int mode_program;


/** =================Type===========================	*/
typedef enum	GPIO_Pin_Type
{
	PIN0 = 0u,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15,
	PIN16,
	PIN17,
	PIN18,
	PIN19,
	PIN20,
	PIN21,
	PIN22,
	PIN23,
	PIN24,
	PIN25,
	PIN26,
	PIN27,
	PIN28,
	PIN29,
	PIN30,
	PIN31	
} E_GPIO_Pin_Type;
	
/** ===================API===========================	*/

void PORTC_IRQHandler(void);

void Gpio_Init(void);
void Gpio_SetPinValue(GPIO_Type* GPIO_Port, E_GPIO_Pin_Type PinNum_E, unsigned int value);
void Gpio_GetPinValue(GPIO_Type* GPIO_Port, E_GPIO_Pin_Type GPIO_PinNum_E,unsigned int* GPIO_value);


unsigned int	Port_ReadBitValue(PORT_Type* PORT_PCRn,E_GPIO_Pin_Type GPIO_PinNum_E, unsigned int PORT_BitField);
void	Port_WriteBitValue(PORT_Type* PORT_PCRn, E_GPIO_Pin_Type PORT_PinNum_E,unsigned int PORT_BitField, unsigned int PORT_Value);

void	ClearAllLed(void);
void	Main_Function(void);
void	Turn_off_blue(void);
void 	Function_Program_1(void);
void 	Function_Program_2(void);


#endif
