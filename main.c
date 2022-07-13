/*  freescale sample code  */



#include <stdio.h>
#include <stdlib.h>

#include "derivative.h" /* include peripheral declarations */


/* this macro attempt to enable watchdog module */
#if	defined (COP_CTRL)
	#define EnableWatchdog \
		COP_CTRL |= (0x2);
#elif defined ( COPCTL )
	#define EnableWatchdog \
		COPCTL |= (0x2);
#else
	#define EnableWatchdog	\
	printf(" no watchdog enable procedure\n");
#endif // #define EnableWatchdog

/* this macro attempt to disable watchdog module */
#if	defined (COP_CTRL)
	#define DisableWatchdog \
		COP_CTRL &= ~(0x2);
#elif defined ( COPCTL )
	#define DisableWatchdog \
		COPCTL &= ~(0x2);
#else
	#define DisableWatchdog	\
	printf(" no watchdog disable procedure\n");
#endif // #define DisableWatchdog
void timer();
void priority();
void CLK();
void isr();
void pwm();
void portB();
void portA();
void pulse();
int i=0;
int j=-2;
int main()
{
	CLK();
	timer();
	pwm();
	portB();
	portA();
	priority();
	while(1)
	{
		
	}
	return (0);
}
void CLK()
{
	PLLCR=0x0002;
	PLLDB=0x0013;
}

void timer()
{	
	TMRA0_LOAD=0;
	TMRA0_SCR=0x4000;
	TMRA0_CMP1=0;
	TMRA0_CTRL=0x3A20;
	TMRA0_CNTR=0;
}
void portB()
{
	            GPIO_B_PER=0;
	            GPIO_B_PUR=0;
				GPIO_B_IAR=0;
				GPIO_B_IENR=0;
				GPIO_B_IPOLR=0;
				GPIO_B_IPR=0;
				GPIO_B_IESR=0;
				GPIO_B_PPMODE=0;
				GPIO_B_RAWDATA=0;
				GPIO_B_DDR=0xff;
}
void portA()
{
	            GPIO_A_PER=0;
			    GPIO_A_IAR=0;
				GPIO_A_IENR=0xffff;
				GPIO_A_IPOLR=0xffff;
				GPIO_A_IPR=0;
				GPIO_A_IESR=0;
				GPIO_A_PUR=0;
				GPIO_A_PPMODE=0;
				GPIO_A_RAWDATA=0;
				GPIO_A_DDR=0;
				
}
void priority()
{
	INTC_IPR7=0xC000;
	INTC_IPR4=0x0020;
	asm(bfclr #$0300,sr);
	
}
void pwm()
{
	            PWMB_PMCFG=0x100E;
				PWMB_PWMCM=16669;// Modulus value	
				PWMB_PMOUT=0x8000;
				PWMB_PMCCR=0xC000;
				asm{bfset #$0002, x:$00f160};
				asm{bfset #$0001, x:$00f160};
				asm{bfset #$00C0, x:$00f160};
}
#pragma interrupt
void isr()
{
	i=i+1;
	if(i==1)
	{
		PWMB_PMOUT=0xA121;
	    TMRA0_CMP1=695;
		TMRA0_CTRL=0x3A20;
	}
	if(i==2)
	{
		PWMB_PMOUT=0x8101;
		TMRA0_CMP1=695;
		TMRA0_CTRL=0x3A20;
		
	}
	if(i==3)
		{
			PWMB_PMOUT=0x9111;
			TMRA0_CMP1=695;
			TMRA0_CTRL=0x3A20;
			
		}
	if(i==4)
		{
			PWMB_PMOUT=0x9010;
			TMRA0_CMP1=695;
			TMRA0_CTRL=0x3A20;
			
		}
	if(i==5)
		{
			PWMB_PMOUT=0xB030;
			TMRA0_CMP1=695;
			TMRA0_CTRL=0x3A20;
			
		}
	if(i==6)
		{
			PWMB_PMOUT=0xA020;
			TMRA0_CMP1=695;
			TMRA0_CTRL=0x3A20;
			
		}
	if(i==7)
		{
			PWMB_PMOUT=0xA121;
			TMRA0_CMP1=695;
			TMRA0_CTRL=0x3A20;
			
		}
	if(i==8)
		{
			PWMB_PMOUT=0x8101;
			TMRA0_CMP1=695;
			TMRA0_CTRL=0x3A20;
			
		}
	if(i==9)
		{
			PWMB_PMOUT=0x9111;
			TMRA0_CMP1=695;
			TMRA0_CTRL=0x3A20;
			
		}
	if(i==10)
		{
			PWMB_PMOUT=0x9010;
			TMRA0_CMP1=695;
			TMRA0_CTRL=0x3A20;
			i=4;
		}
	TMRA0_SCR=0x4000;
}
#pragma interrupt
void pulse()
{
	j=j+1;
	if(j==1)
	{
		GPIO_B_DR=0x20;
		GPIO_A_IPOLR=0xffff;
	}
	if(j==2)
	{
		GPIO_B_DR=0x60;
		GPIO_A_IPOLR=0;
	}
	if(j==3)
	{
		GPIO_B_DR=0x48;
		GPIO_A_IPOLR=0xffff;
	}
	if(j==4)
	{
		GPIO_B_DR=0x18;
		GPIO_A_IPOLR=0;
	}
	if(j==5)
	{
		GPIO_B_DR=0x10;
		GPIO_A_IPOLR=0xffff;
	}
	if(j==6)
	{
		GPIO_B_DR=0;
		GPIO_A_IPOLR=0;
		j=0;
	}
	if(j==-1)
	{
		GPIO_B_DR=0x20;
		j=j+2;
		GPIO_A_IPOLR=0xffff;
	}
	GPIO_A_IESR=0xffff;
}
