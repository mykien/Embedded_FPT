#ifndef	_SOFTTIMER_REGISTER_H_
#define	_SOFTTIMER_REGISTER_H_

/** 5.	Define Register System stick timer	*/

typedef struct {
	volatile unsigned int CSR;				/*	Systick Control and Status Register	*/
	volatile unsigned int RVR;				/*	Systick Reload Value Register	*/				
	volatile unsigned int CVR;				/*	Systick Current Value Register	*/
	volatile unsigned int CALIB;			/*	Systick Calibration Value register	*/
}SysTick_Type;
	#define SYSTICK_BASE		(0xE000E010)
	#define	SYSTICK				((SysTick_Type*) SYSTICK_BASE)



/** 6. SCG - System Clock Generator */

	#define BASE_SCG				(0x40064000u)

	#define SCG_SOSCCFG			*((volatile unsigned int*)	(BASE_SCG + 0x108u))
	#define SCG_SOSCDIV			*((volatile unsigned int*)	(BASE_SCG	+	0x104u))
	#define	SCG_SOSCCSR			*((volatile unsigned int*)	(BASE_SCG	+	0x100u))

	#define SCG_SPLLCSR			*((volatile unsigned int*)	(BASE_SCG	+ 0x600u))
	#define SCG_SPLLDIV			*((volatile unsigned int*)	(BASE_SCG	+	0x604u))
	#define	SCG_SPLLCFG			*((volatile unsigned int*)	(BASE_SCG	+	0x608u))
		

	#define	SCG_RCCR				*((volatile unsigned int*)	(BASE_SCG	+	0x14u))
	#define SCG_CSR					*((volatile unsigned int*)	(BASE_SCG	+ 0x10u))
		


#endif
