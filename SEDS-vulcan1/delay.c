#include <stm32f10x_lib.h>
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 

static u8  fac_us=0;//us delay factor
static u16 fac_ms=0;//ms delay factor

//SYSTICK goes at the rate of HCLK clock's 1/8

void delay_init(u8 SYSCLK)
{
	SysTick->CTRL&=0xfffffffb;//clear bit2,Slect external clock  HCLK/8
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
}	

//SysTick->LOAD is a 24 bit regester,maxium delay is:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK(Hz),nms(ms)
//when running at 72M,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//load time(SysTick->LOAD is 24bit)
	SysTick->VAL =0x00;           //clear counter
	SysTick->CTRL=0x01 ;          //start counting  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//wait    
	SysTick->CTRL=0x00;       //turn off counter
	SysTick->VAL =0X00;       //clear counter	  	    
}   
		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 	  		 
	SysTick->VAL=0x00;        
	SysTick->CTRL=0x01 ;      	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));  
	SysTick->CTRL=0x00;       
	SysTick->VAL =0X00;      	 
}




































