# 1 "main.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "main.c"
# 1 "Gpio_Register.h" 1
# 9 "Gpio_Register.h"
typedef struct {
  volatile unsigned int PCR[32u];
} PORT_Type;
# 23 "Gpio_Register.h"
typedef struct {
  volatile unsigned int PDOR;
  volatile unsigned int PSOR;
  volatile unsigned int PCOR;
  volatile unsigned int PTOR;
  volatile const unsigned int PDIR;
  volatile unsigned int PDDR;
  volatile unsigned int PIDR;
} GPIO_Type;
# 47 "Gpio_Register.h"
typedef struct {
  volatile unsigned int PCCn[122u];
} PCC_Type;
# 74 "Gpio_Register.h"
typedef struct {
  volatile unsigned int ISER[8u];
      unsigned int RESERVED_0[24];
  volatile unsigned int ICER[8u];
           unsigned int RESERVED_1[24];
  volatile unsigned int ISPR[8u];
           unsigned int RESERVED_2[24];
  volatile unsigned int ICPR[8u];
           unsigned int RESERVED_3[24];
  volatile unsigned int IABR[8u];
       unsigned char RESERVED_4[224];
  volatile unsigned char IP[240u];
       unsigned char RESERVED_5[2576];
  volatile unsigned int STIR;
} NVIC_Type;
# 2 "main.c" 2







typedef enum Led_State
{
 BLUE,
 RED,
 GREEN
} Led_State_t;

typedef enum Mode_State
{
 STOP,
 START
} Mode_State_t;

typedef enum Direction_State
{
 FORWARD,
 BACKWARD
} Direction_State_t;


static const unsigned char arr_Led_Pin[] = {(0u), (15u), (16u)};
static volatile Led_State_t Led_current_state = GREEN;
static volatile Mode_State_t Mode_current_state = STOP;
static volatile Direction_State_t Direction_current_state = FORWARD;


static volatile Led_State_t Led_red_state = RED;


void Buttons_init(void);
void Leds_init(void);
void PORTC_IRQHandler(void);
void Delay(void);
void turn_on_Led(Led_State_t state);
void process_Led_State(void);

int mode = 0;
int main()
{

 int a = 0;
 int b = 0;
 int c = 0;
 int flag_blue ;
 ((GPIO_Type*)((0x400FF0C0u)))->PDOR |= ((1u) | (1u<<15u) | (1u<<16u));



 Buttons_init();


 Leds_init();

 PORTC_IRQHandler();
 while (1)
 {

  if (b <= 6000000)
  {
   b++;
   ((GPIO_Type*)((0x400FF0C0u)))->PDOR &=~ ( 1u<< 0u );
   flag_blue = 1;
  }
  else
  {
   flag_blue = 0;
   ((GPIO_Type*)((0x400FF0C0u)))->PDOR |= ( 1u<< 0u );
  }


  switch (mode)
  {
   case 1:
    c = 0;
    a++;
    if(a <= 500000)
    {
     if (flag_blue == 1){
      ((GPIO_Type*)((0x400FF0C0u)))->PDOR |= (1u<<16u);
     }
     else if(flag_blue == 0)
     {
      ((GPIO_Type*)((0x400FF0C0u)))->PDOR |= ((1u<<0u)|(1u<<16u));
     }
     ((GPIO_Type*)((0x400FF0C0u)))->PDOR &=~ ( 1u<< 15u );
    }
    else if (a > 500000 && a <= 1000000)
    {
     ((GPIO_Type*)((0x400FF0C0u)))->PDOR |= ((1u<<15u)|(1u<<16u));
     ((GPIO_Type*)((0x400FF0C0u)))->PDOR &=~ ( 1u<< 0u );



    }
    else if (a > 1000000 && a <= 1500000)
    {
     if (flag_blue == 1){
      ((GPIO_Type*)((0x400FF0C0u)))->PDOR |= (1u<<15u);
     }
     else if(flag_blue == 0)
     {
      ((GPIO_Type*)((0x400FF0C0u)))->PDOR |= ((1u<<0u)|(1u<<15u));
     }
     ((GPIO_Type*)((0x400FF0C0u)))->PDOR &=~ ( 1u<< 16u );
    }
    else
    {
     a = 0;
    }
    break;
   case 2:
    c++;
    a = 0;
    if(c <= 500000){
     if (flag_blue == 1){
      ((GPIO_Type*)((0x400FF0C0u)))->PDOR |= (1u<<15u);
     }
     else if(flag_blue == 0)
     {
      ((GPIO_Type*)((0x400FF0C0u)))->PDOR |= ((1u<<0u)|(1u<<15u));
     }
     ((GPIO_Type*)((0x400FF0C0u)))->PDOR &=~ ( 1u<< 16u );
    }
    else if(c > 500000 && c <= 1000000){
     if (flag_blue == 1){
      ((GPIO_Type*)((0x400FF0C0u)))->PDOR |= (1u<<16u);
     }
     else if(flag_blue == 0)
     {
      ((GPIO_Type*)((0x400FF0C0u)))->PDOR |= ((1u<<0u)|(1u<<16u));
     }
     ((GPIO_Type*)((0x400FF0C0u)))->PDOR &=~ ( 1u<< 15u );
    }
    else
    {
     c =0;
    }
   break;

  }
 }
# 207 "main.c"
}


void Buttons_init(void)
{
# 220 "main.c"
 ((PCC_Type *)(0x40065000u))->PCCn[75] |= (1u<<30u);


 ((PORT_Type *)(0x4004B000u)) ->PCR[(12u)] |= (1u<<8u);
 ((PORT_Type *)(0x4004B000u)) ->PCR[(13u)] |= (1u<<8u);





 ((PORT_Type *)(0x4004B000u)) ->PCR[(12u)] |= (1u<<1u);
 ((PORT_Type *)(0x4004B000u)) ->PCR[(13u)] |= (1u<<1u);


 ((PORT_Type *)(0x4004B000u)) ->PCR[(12u)] &= ~(1u<<0u);
 ((PORT_Type *)(0x4004B000u)) ->PCR[(13u)] &= ~(1u<<0u);






 ((PORT_Type *)(0x4004B000u)) ->PCR[(12u)] |= (10u<<16u);
 ((PORT_Type *)(0x4004B000u)) ->PCR[(13u)] |= (10u<<16u);


 ((GPIO_Type*)((0x400FF080u))) ->PDDR &=~ (1u<<(12u));
 ((GPIO_Type*)((0x400FF080u))) ->PDDR &=~ (1u<<(13u));


 ((NVIC_Type *)(0xE000E100u))->ISER[1] |= (1u<<29u);

}

void Leds_init(void)
{
# 266 "main.c"
 ((PCC_Type *)(0x40065000u))->PCCn[76] |= (1u<<30u);


 ((PORT_Type *)(0x4004C000u)) ->PCR[(0u)] |= (1<<8u);
 ((PORT_Type *)(0x4004C000u)) ->PCR[(15u)] |= (1<<8u);
 ((PORT_Type *)(0x4004C000u)) ->PCR[(16u)] |= (1<<8u);


 ((GPIO_Type*)((0x400FF0C0u))) ->PDDR |= (1<<0u);
 ((GPIO_Type*)((0x400FF0C0u))) ->PDDR |= (1<<15u);
 ((GPIO_Type*)((0x400FF0C0u))) ->PDDR |= (1<<16u);

}



void PORTC_IRQHandler(void)
{
 if( ((PORT_Type *)(0x4004B000u)) ->PCR[(12u)] & (1u<<24u) ){
  ((PORT_Type *)(0x4004B000u)) ->PCR[(12u)] |= (1u<<24u);
  mode = 1;
  ((GPIO_Type*)((0x400FF0C0u)))->PDOR |= ((1u) | (1u<<15u) | (1u<<16u));







 }
# 312 "main.c"
 if( ((PORT_Type *)(0x4004B000u)) ->PCR[(13u)] & (1u<<24u) ){
  ((PORT_Type *)(0x4004B000u)) ->PCR[(13u)] |= (1u<<24u);
  mode = 2;
  ((GPIO_Type*)((0x400FF0C0u)))->PDOR |= ((1u) | (1u<<15u) | (1u<<16u));
# 325 "main.c"
 }
# 339 "main.c"
}

void Delay(void)
{
 for(int i = 0; i<1000000; i++){}
}


void turn_on_Led(Led_State_t state)
{

 ((GPIO_Type*)((0x400FF0C0u)))->PDOR |= ((1u) | (1u<<15u) | (1u<<16u));


 ((GPIO_Type*)((0x400FF0C0u)))->PDOR &=~ ( 1u<< arr_Led_Pin[state] );

}


void process_Led_State(void)
{
 if( START == Mode_current_state )
 {
  if( FORWARD == Direction_current_state )
  {
   if( GREEN == Led_current_state ) Led_current_state = RED;
   else if ( RED == Led_current_state ) Led_current_state = BLUE;
   else Led_current_state = GREEN;
  }
  else
  {
   if( GREEN == Led_current_state ) Led_current_state = BLUE;
   else if ( RED == Led_current_state ) Led_current_state = GREEN;
   else Led_current_state = RED;
  }
 }
}
