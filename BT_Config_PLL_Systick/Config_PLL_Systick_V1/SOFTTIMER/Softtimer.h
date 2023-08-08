#ifndef _SOFTTIMER_H_
#define _SOFTTIMER_H_
/** =================Define===========================	*/

#define ONESHOT           ((unsigned char) 0u)
#define CONTINUOS         ((unsigned char) 1u)
#define MAX_SIZE_TIMER    ((unsigned int) 5u)
#define FALSE             ((unsigned char) 0u)
#define TRUE              ((unsigned char) 1u)
#define NULL_PTR          ((void*)0)				/*	Pointer NULL	*/

#define ID_Sofftimer0			((unsigned int)	0u)
#define	ID_Softtimer1			((unsigned int)	1u)
#define	ID_Softtimer2			((unsigned int)	2u)	
	
#define	T5_Second					((unsigned int) 5000u)
#define T1_Second					((unsigned int)	1000u)
#define T500_Milisecond		((unsigned int)	500u)



/** =================Variable===========================	*/

extern volatile unsigned int TimeCountMs;

/** =====================Type============================	*/

typedef void (*CALLBACK)(void);


/** =====================API============================	*/

void Softtimer_Init(void);

void Softtimer_StartTimer(int TimerID,
									        unsigned int TimeoutValue,
													unsigned char Mode,
													CALLBACK Event);
                          
void Softtimer_StopTimer(void);

void Softtimer_Mainfunction(void);

void SysTick_Handler(void);
													
void Change_Clock (void);

#endif
