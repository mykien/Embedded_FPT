#ifndef GPIO_REGISTER_H_
#define GPIO_REGISTER_H_

/***	1.PORT - Size of Registers Arrays - 32 elements */
#define PORT_PCR_COUNT				32u

/** PORT module */
typedef struct {
	volatile unsigned int PCR[PORT_PCR_COUNT];
}	PORT_Type;

/** Peripheral PORTC base address */
#define PORTC_BASE						(0x4004B000u)
/** Peripheral PORTC base pointer */
#define PORTC									((PORT_Type*)PORTC_BASE)


/** Peripheral PORTD base address */
#define PORTD_BASE						(0x4004C000u)
/** Peripheral PORTD base pointer */
#define PORTD									((PORT_Type*)PORTD_BASE)

/***	2.GPIO	*/
typedef struct{
	volatile unsigned int PDOR;	/**< Port Data Output Register, offset: 0x0 */
	volatile unsigned int PSOR;	/**< Port Set Output Register, offset: 0x4 */
	volatile unsigned int PCOR;	/**< Port Clear Output Register, offset: 0x8 */
	volatile unsigned int PTOR;	/**< Port Toggle Output Register, offset: 0xC */
	volatile unsigned int PDIR;	/**< Port Data Input Register, offset: 0x10 */
	volatile unsigned int PDDR;	/**< Port Data Direction Register, offset: 0x14 */
	volatile unsigned int PIDR;	/**< Port Input Disable Register, offset: 0x18 */
}GPIO_Type;

/**	GPIOC base address	*/
#define	GPIOC_BASE						(0x400FF080u)
#define GPIOC									((GPIO_Type*)GPIOC_BASE)

/**	GPIOD base address	*/
#define GPIOD_BASE						(0x400FF0C0u)
#define GPIOD									((GPIO_Type*)GPIOD_BASE)



/**	3. PCC */
typedef struct {
  char PCC_dummy0[128];
  volatile unsigned int PCC_FTFC;
  volatile unsigned int PCC_DMAMUX;
  char PCC_dummy1[8];
  volatile unsigned int PCC_FlexCAN0;
  volatile unsigned int PCC_FlexCAN1;
  volatile unsigned int PCC_FTM3;
  volatile unsigned int PCC_ADC1;
  char PCC_dummy2[12];
  volatile unsigned int PCC_FlexCAN2;
  volatile unsigned int PCC_LPSPI0;
  volatile unsigned int PCC_LPSPI1;
  volatile unsigned int PCC_LPSPI2;
  char PCC_dummy3[8];
  volatile unsigned int PCC_PDB1;
  volatile unsigned int PCC_CRC;
  char PCC_dummy4[12];
  volatile unsigned int PCC_PDB0;
  volatile unsigned int PCC_LPIT;
  volatile unsigned int PCC_FTM0;
  volatile unsigned int PCC_FTM1;
  volatile unsigned int PCC_FTM2;
  volatile unsigned int PCC_ADC0;
  char PCC_dummy5[4];
  volatile unsigned int PCC_RTC;
  char PCC_dummy6[8];
  volatile unsigned int PCC_LPTMR0;
  char PCC_dummy7[32];
  volatile unsigned int PCC_PORTA;
  volatile unsigned int PCC_PORTB;
  volatile unsigned int PCC_PORTC;
  volatile unsigned int PCC_PORTD;
  volatile unsigned int PCC_PORTE;
  char PCC_dummy8[24];
  volatile unsigned int PCC_SAI0;
  volatile unsigned int PCC_SAI1;
  char PCC_dummy9[16];
  volatile unsigned int PCC_FlexIO;
  char PCC_dummy10[24];
  volatile unsigned int PCC_EWM;
  char PCC_dummy11[16];
  volatile unsigned int PCC_LPI2C0;
  volatile unsigned int PCC_LPI2C1;
  char PCC_dummy12[8];
  volatile unsigned int PCC_LPUART0;
  volatile unsigned int PCC_LPUART1;
  volatile unsigned int PCC_LPUART2;
  char PCC_dummy13[4];
  volatile unsigned int PCC_FTM4;
  volatile unsigned int PCC_FTM5;
  volatile unsigned int PCC_FTM6;
  volatile unsigned int PCC_FTM7;
  char PCC_dummy14[4];
  volatile unsigned int PCC_CMP0;
  char PCC_dummy15[8];
  volatile unsigned int PCC_QSPI;
  char PCC_dummy16[8];
  volatile unsigned int PCC_ENET;
} PCC_Type;

#define PCC_BASE_ADDRS (0x40065000u)
#define PCC ((PCC_Type*)PCC_BASE_ADDRS)

	
/***	4. S32_NVIC - Size of Registers Arrays */
#define S32_NVIC_ISER_COUNT                      8u
#define S32_NVIC_ICER_COUNT                      8u
#define S32_NVIC_ISPR_COUNT                      8u
#define S32_NVIC_ICPR_COUNT                      8u
#define S32_NVIC_IABR_COUNT                      8u
#define S32_NVIC_IP_COUNT                        240u

/** S32_NVIC - Register Layout Typedef */
typedef struct {
  volatile unsigned int ISER[S32_NVIC_ISER_COUNT];         /**< Interrupt Set Enable Register n, array offset: 0x0, array step: 0x4 */
					 unsigned int RESERVED_0[24];
  volatile unsigned int ICER[S32_NVIC_ICER_COUNT];         /**< Interrupt Clear Enable Register n, array offset: 0x80, array step: 0x4 */
           unsigned int RESERVED_1[24];
  volatile unsigned int ISPR[S32_NVIC_ISPR_COUNT];         /**< Interrupt Set Pending Register n, array offset: 0x100, array step: 0x4 */
           unsigned int RESERVED_2[24];
  volatile unsigned int ICPR[S32_NVIC_ICPR_COUNT];         /**< Interrupt Clear Pending Register n, array offset: 0x180, array step: 0x4 */
           unsigned int RESERVED_3[24];
  volatile unsigned int IABR[S32_NVIC_IABR_COUNT];         /**< Interrupt Active bit Register n, array offset: 0x200, array step: 0x4 */
       unsigned char RESERVED_4[224];
  volatile unsigned char IP[S32_NVIC_IP_COUNT];              /**< Interrupt Priority Register n, array offset: 0x300, array step: 0x1 */
       unsigned char RESERVED_5[2576];
  volatile  unsigned int STIR;                              /**< Software Trigger Interrupt Register, offset: 0xE00 */
} NVIC_Type;

/* S32_NVIC - Peripheral instance base addresses */
/** Peripheral S32_NVIC base address */
#define NVIC_BASE                            (0xE000E100u)
/** Peripheral S32_NVIC base pointer */
#define NVIC                                 ((NVIC_Type *)NVIC_BASE)

#endif
