#include    "Softtimer_Register.h"
#include		"Softtimer.h"





/*	define variable TimeCountMs	*/
volatile unsigned int TimeCountMs = 0;

typedef struct Softtimer
{
	unsigned char TimerEnable;
	unsigned char ModeTimer;
	unsigned char padding[2];			/*	Alignment struct	*/
	unsigned int TimeOutValue;
	unsigned int CurrentTime;
	CALLBACK Callback;
} Softtimer;


//static Softtimer Timer1;
static Softtimer Timer_Array[MAX_SIZE_TIMER];

void	Softtimer_Init (void)
{
	unsigned int count;
  for ( count = 0; count < MAX_SIZE_TIMER; count++)
  {
    Timer_Array[count].TimerEnable = FALSE;
    Timer_Array[count].TimeOutValue = 0;
    Timer_Array[count].CurrentTime = 0;
    Timer_Array[count].ModeTimer = ONESHOT;
    Timer_Array[count].Callback = NULL_PTR;
  }

  /**  Init systick  */
	//	1.	disable system tick timer
	SYSTICK->CSR = (unsigned int) 0ul;
	
	//	2.	write reload value = 48000
	SYSTICK->RVR = (unsigned int) (48000ul - 1ul);
	
	//	3.	clear current value register and COUNTFLAG - write 0 to CVR => clear bit counter flag
	SYSTICK->CVR = (unsigned int) (0ul);
	
	//	4.	set source clock - processor clock
	SYSTICK->CSR |= (unsigned int) (0x00000004ul);
	
	//	5.	Enable interrupt
	SYSTICK->CSR |= (unsigned int) (0x00000002ul);
	
	//	6.	Enable systick counter
	SYSTICK->CSR |= (unsigned int) (0x00000001ul);
}



void Softtimer_StartTimer(int TimerID,
									        unsigned int TimeoutValue,
													unsigned char Mode,
													CALLBACK Event)
{
  Timer_Array[TimerID].TimerEnable = TRUE;
	Timer_Array[TimerID].TimeOutValue = TimeoutValue;
  Timer_Array[TimerID].ModeTimer = Mode;
  Timer_Array[TimerID].Callback = Event;
}



void Softtimer_Mainfunction(void)
{ 
	unsigned int count1;
  for(count1 = 0; count1 < MAX_SIZE_TIMER ; count1++)
  {
    if (Timer_Array[count1].TimerEnable == TRUE && (TimeCountMs >= (Timer_Array[count1].CurrentTime + Timer_Array[count1].TimeOutValue)))
    {
      Timer_Array[count1].Callback();
      if (Timer_Array[count1].ModeTimer == CONTINUOS)
      {
        Timer_Array[count1].CurrentTime = TimeCountMs;
      }
      else if (Timer_Array[count1].ModeTimer == ONESHOT)
      {
        Timer_Array[count1].TimerEnable = FALSE;
      }
    }
  }
}

void SysTick_Handler(void)
{
	TimeCountMs++;	
}



void Change_Clock (void)
{
	/*	For any writeable SCG registers, only 32-bits writes are allowed */
	/*	check unlock		*/
	while (SCG_SPLLCSR &(1u<<23u)) {}
		
	/** Step 1.	disable SPLL*/
	SCG_SPLLCSR  = 0x00000000;
	
	/*	Step 2 and 3. Dividers 1 = 1 and div 2 = 1 	*/
	SCG_SPLLDIV = (0x00000101);
	
	/*	Step 4. Set PLL configuration - div = 8 - mul = 16 - source = Fast IRC	*/
	SCG_SPLLCFG = (0x00000701);
		
	/*check unlock	*/
	while (SCG_SPLLCSR &(1u<<23u)) {}
			
	/* Step 5. clear Register */

	/* Step 6. Enable */
	SCG_SPLLCSR = (0x00000001);
		
	/*	Step 7. wait for SPLL to initialize */
	while (!(SCG_SPLLCSR & (1u<<24u))){}
		
	/*	mode = PLL	-Divcore = 2 - div bus = 2 - divSlow = 2  */
	SCG_RCCR = (0x06010012);
		
	//SCG_RCCR = (0x06000000); /* divslow = 0000 => error (default = 0001) */
	
	//SCG_RCCR = (0x06000012);	/*  div core = 0000	*/
		
	//SCG_RCCR = (0x06000002);	/*  div core = 0000 and divbus = 0000	*/
		
	/* Wait for sync clock	*/
	while ((SCG_CSR & (0x0F000000))>>23u != 6){}
}



