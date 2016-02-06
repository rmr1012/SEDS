#include <stm32f10x_lib.h>
#include "sys.h"	
#include "delay.h"	
#include "stdio.h"
#include "init.h"
//#include "ds18b20.h"	
 

u8 USART_RX_BUF[256];    //RXT buffer maxium 255bytes
u8 USART_RX_STA=0;       //RX Compleate	 
u8 USART_RX_CNT=0;       //RX Entre Count	
u16 echo=0x7855;
u16 adcx[],Gyro_raw,Batt,prd,dtc;
u16 temp[]; 
u8 cntt=1,freshtemp=0;
char pussy='b';	
int c,d,e,f;
char mem=1;
int main(void)
{	
//	u8 i;		   	
 	Stm32_Clock_Init(9); //system clock init   always init first
	IO_Init();
	delay_init(72);	     //delay init
<<<<<<< HEAD
	uart_init(72,230400);  //uart init
	PWM4_Init(15000,18);				 // flowmeter sample pulse	 //PB6
	PWM5_Init(15000,18);				 // flowmeter sample pulse	 //PB6
	Timer2_Init(100,1800);	 //count to 100, freq/1800	 //IR aqusition pulse	  //no need for SEDS
	Timer3_Init(65535,256);	  //time refrence for echo/ultrasonic			  //no need for SEDS
	
	EXTIX_Init();
	Adc_Init();
=======
	uart_init(72,115200);  //uart init
	PWM4_Init(150,18000);				 // ultra ping sig

//	PWM2_2Init(100,1800);	 //count to 100, freq/1800	 //IR aqusition pulse
	Timer3_Init(65535,256);	  //time refrence for echo/ultrasonic

//	setup 5 for motors?
	Timer2_Init(65535,10);	// motor try1
	motor_Init();

	EXTIX_Init();
//	Adc_Init();
>>>>>>> 549c792ab31d606ac47ed82c636935393f51a1a1
//	LED0_PWM_VAL2_2=0x44;
//	LED0_PWM_VAL2_1=0x34;
//	IRO=0;//turn on IR LEDs
/*	while(DS18B20_Init())//
	{
		printf("no fucking way\n");
		delay_ms(100);
	}				   */
   	while(1)
	{	
		freshtemp=1;  

	/*	startconv();  //start converting for all
		for(i=0;i<8;i++)
		{
			TIM2->DIER&=0<<6;   //disable update interrupt
			TIM2->DIER&=0<<0;   //disable update interrupt
			temp[i]=DS18B20_Get_Temp(i);
			TIM2->DIER|=1<<6;   //allow update interrupt
			TIM2->DIER|=1<<0;   //disable update interrupt
			TIM2->EGR=1<<0;	
		}			  */
	//	delay_ms(200);
		prd=TIM4->CCR2;
		dtc=TIM4->CCR1;
	//	USART1->DR=echo/0xff;
	//	while((USART1->SR&0X40)==0);//wait for transfer to compleate
//		LED0=!LED0; 
//		delay_us(100000);//wait for the end of transmission	   
	}	 
} 																						 

void EXTI0_IRQHandler(void)
{
	EXTI->PR=1<<0;  //Clear Interrupt flag
//	delay_us(50);
	if(PBin(0)==1&&mem==0)
	{
		TIM3->CR1|=0x01;   //start timer
		mem=1;
	}
	else if(PBin(0)==0&&mem==1)
	{
		TIM3->CR1&=0xfe;//stop timer
		echo=TIM3->CNT;	//read value
		TIM3->CNT=0x00; //clear timer
		mem=0;
	} 
}

void USART1_IRQHandler(void)
{
	u8 res;	    
	if(USART1->SR&(1<<5))//RXT recieved
	{	 
		res=USART1->DR;	 //read out data and clear interrupt flag
//		LED0_PWM_VAL=res;
		if(!USART_RX_STA)
		{ 	
			USART_RX_BUF[USART_RX_CNT++]=res;
			if(USART_RX_CNT==255)USART_RX_CNT=0;//RXT data over flow,start over	  
		}
	}  											 
}


void TIM2_IRQHandler(void)	 
{ 		    		  			    
	if(TIM2->SR&0X0001)//Overflow Interrupt
	{
<<<<<<< HEAD
		ADC1->CR2|=1<<22;
//		if(freshtemp){printf("Temp: %u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\n",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7]);freshtemp=0;}
//		printf("adcx1\tadcx2\tadcx3\tadcx4\tGyro\tBatt\techo\n");
		printf("(%u)\t%u\t%u\t%u\t%u\t%u\t%u\t%u\t\n",mux,adcx[1],adcx[2],adcx[3],adcx[4],adcx[5],adcx[6],adcx[7]);
			    				   				     	    	
=======
	
			CDSTEP=!CDSTEP;
			ABSTEP=!ABSTEP;
					    				   				     	    	
>>>>>>> 549c792ab31d606ac47ed82c636935393f51a1a1
	}				   
	TIM2->SR&=~(1<<0);//Clear Interrupt flag 	    
}

void ADC1_2_IRQHandler(void)	 
{ 		    		  			    
	switch (cntt){
		case 1:
			adcx[cntt]=ADC1->DR;
			ADC1->DR=0;
			break;
		case 2:
			adcx[cntt]=ADC1->DR;
			ADC1->DR=0;
		 	break;
		case 3:
			adcx[cntt]=ADC1->DR;
			ADC1->DR=0;
			break;
		case 4:
			adcx[cntt]=ADC1->DR;
			ADC1->DR=0;
			break;
		case 5:
			adcx[cntt]=ADC1->DR;
			ADC1->DR=0;
			break;
		case 6:
			adcx[cntt]=ADC1->DR;
			ADC1->DR=0;
			break;
		case 7:
			adcx[cntt]=ADC1->DR;
			ADC1->DR=0;
			break;
	}
	cntt++;
	if(cntt==8){
		mux=!mux;
		cntt=0;
	//	delay_us(40);
	}
//	else
	//	ADC1->CR2|=1<<0;
//	IRO=!IRO;//defult 1	    				   				     	    	   
}


