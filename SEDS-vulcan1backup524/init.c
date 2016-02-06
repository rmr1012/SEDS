#include "init.h"
void SystemInit(void);
void motor_Init()
{
	CDDECAY=0;
	ABDECAY=0;
	CDUSM0=0; 
	CDUSM1=0;
	ABUSM0=0; 
	ABUSM1=0;//microsteppign config
	CDRESETN=0;
	ABRESTN=0;
	delay_us(100); 
	CDRESETN=1;
	ABRESTN=1;
}
void IO_Init()
{
	RCC->APB2ENR|=1<<4;    //Enable PortC Clock
	RCC->APB2ENR|=1<<3;    //Enable PortB Clock	  
	RCC->APB2ENR|=1<<2;    //Enable PortA Clock
	GPIOA->CRH=0x100118B1;//
	GPIOA->CRL=0x00000000;//
	GPIOB->CRH=0x1114F411;//
	GPIOB->CRL=0x44311404;
	GPIOC->CRH=0x11144444;
	GPIOC->CRL=0x44444444;	 
	GPIOB->ODR|=1<<7;//PB7 Pull up	
}
void EXTIX_Init(void)
{				
				  
	JTAG_Set(JTAG_SWD_DISABLE);//turn off JTAG&SWD   
				   	
	Ex_NVIC_Config(GPIO_B,0,0x03); //edge trigger

	MY_NVIC_Init(1,1,EXTI0_IRQChannel,2);   
	   
}
void PWM5_Init(u16 arr,u16 psc)
{		 					 
	RCC->APB1ENR|=1<<3;    //TIM4 Clock Enable    
	


	TIM5->ARR=arr;//Auto Reload Value 
	TIM5->PSC=psc;//Freq Devider
	
	TIM5->CCMR1=0x1111;  //CH2 PWM2 mode		 

	TIM5->CCER=0x0031;   //OC2 output enable	   

	TIM5->CR1=0x80;     //ARPE enable
	TIM5->CR1|=0x01;    //enable timer4 
	TIM5->SMCR=0x0054;															  
}  

void PWM4_Init(u16 arr,u16 psc)
{		 					 
	RCC->APB1ENR|=1<<2;    //TIM4 Clock Enable    
	
<<<<<<< HEAD

=======
	
>>>>>>> 549c792ab31d606ac47ed82c636935393f51a1a1

	TIM4->ARR=arr;//Auto Reload Value 
	TIM4->PSC=psc;//Freq Devider
	
	TIM4->CCMR1=0x1111;  //CH2 PWM2 mode		 

	TIM4->CCER=0x0031;   //OC2 output enable	   

	TIM4->CR1=0x80;     //ARPE enable
	TIM4->CR1|=0x01;    //enable timer4 
	TIM4->SMCR=0x0054;															  
}  
void PWM2_2Init(u16 arr,u16 psc)
{		 					 
	RCC->APB1ENR|=1<<0;    //TIM2 Clock Enable    

	GPIOA->ODR|=1<<1;//PA1 Pull up	

	TIM2->ARR=arr;//Auto Reload Value 
	TIM2->PSC=psc;//Freq Devider
	
	TIM2->CCMR1|=7<<12;  //CH2 PWM2 mode		 
	TIM2->CCMR1|=1<<11; //CH2preload enable   

	TIM2->CCER|=1<<4;   //OC2 output enable	   

	TIM2->CR1=0x80;     //ARPE enable
	TIM2->CR1|=0x01;    //enable timer2 									  
} 
void PWM2_1Init(u16 arr,u16 psc) //adc clock /IR clock
{		 					 
	RCC->APB1ENR|=1<<0;    //TIM2 Clock Enable    

	GPIOA->ODR|=1<<1;//PA1 Pull up	

	TIM2->ARR=arr;//Auto Reload Value 
	TIM2->PSC=psc;//Freq Devider
	
	TIM2->CCMR1|=7<<4;  //CH1 PWM2 mode		 
	TIM2->CCMR1|=1<<3; //CH1 preload enable   

	TIM2->CCER|=1<<0;   //OC1 output enable	   

	TIM2->CR1=0x80;     //ARPE enable
	TIM2->CR1|=0x01;    //enable timer2 									  
}
void Timer5_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<3;//TIM5 clock enable    
 	TIM5->ARR=arr;  //auto reload value 
	TIM5->PSC=psc;  //freq devider

	TIM5->DIER|=1<<0;   //allow update interrupt				
	TIM5->DIER|=1<<6;   //allow trigger interrupt	   
	TIM5->CR1|=0x01;    //enable Timer 4
  	MY_NVIC_Init(2,2,TIM5_IRQChannel,2);//Req1£¬SubPrioity3£¬Group2									 
}
void Timer6_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<4;//TIM6 clock enable    
 	TIM6->ARR=arr;  //auto reload value 
	TIM6->PSC=psc;  //freq devider

	TIM6->DIER|=1<<0;   //allow update interrupt				
	TIM6->DIER|=1<<6;   //allow trigger interrupt	   
	TIM6->CR1|=0x01;    //enable Timer 4
  	MY_NVIC_Init(2,2,TIM6_IRQChannel,2);//Req1£¬SubPrioity3£¬Group2									 
}	 
void Timer4_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<2;//TIM4 clock enable    
 	TIM4->ARR=arr;  //auto reload value 
	TIM4->PSC=psc;  //freq devider

	TIM4->DIER|=1<<0;   //allow update interrupt				
	TIM4->DIER|=1<<6;   //allow trigger interrupt	   
	TIM4->CR1|=0x01;    //enable Timer 4
  	MY_NVIC_Init(2,3,TIM4_IRQChannel,2);//Req1£¬SubPrioity3£¬Group2									 
}

void Timer3_Init(u16 arr,u16 psc)	   //time measuring pulse
{
	RCC->APB1ENR|=1<<1;//TIM3 clock enable    
 	TIM3->ARR=arr;  //auto reload value 
	TIM3->PSC=psc;  //freq devider

//	TIM3->DIER|=1<<0;   //allow update interrupt				
//	TIM3->DIER|=1<<6;   //allow trigger interrupt	   

  	MY_NVIC_Init(3,4,TIM3_IRQChannel,2);//Req1£¬SubPrioity3£¬Group2									 
}
void Timer2_Init(u16 arr,u16 psc)	 //IR sample pulse
{
	RCC->APB1ENR|=1<<0;//TIM4 clock enable    
 	TIM2->ARR=arr;  //auto reload value 
	TIM2->PSC=psc;  //freq devider

	TIM2->DIER|=1<<0;   //allow update interrupt				
	TIM2->DIER|=1<<6;   //allow trigger interrupt	   
	TIM2->CR1|=0x01;    //enable Timer 4 

  	MY_NVIC_Init(2,4,TIM2_IRQChannel,2);//Req1£¬SubPrioity3£¬Group2									 
}
void uart_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//get USARTDIV
	mantissa=temp;				 //get natrual part
	fraction=(temp-mantissa)*16; //get decimal part
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //enable PortA clock  
	RCC->APB2ENR|=1<<14;  //enable USART clock 
		  
	RCC->APB2RSTR|=1<<14;   //reset usart1		  
	RCC->APB2RSTR&=~(1<<14);//stop reset	   	   

 	USART1->BRR=mantissa; // Baud Rate config	 
	USART1->CR1|=0x340C;  //1 stop bit, no check.


	USART1->CR1|=1<<8;    //PE interrupt enable
	USART1->CR1|=1<<5;    //RXT buffer non-empty interrupt enable	    	
	MY_NVIC_Init(3,3,USART1_IRQChannel,2);//group2£¬low priority 

}

			 
void  Adc_Init(void)
{    

 	RCC->APB2ENR|=1<<2;    //PORTA clk enable 
		 
	RCC->APB2ENR|=1<<9;    //ADC1 clk enable	  
	RCC->APB2RSTR|=1<<9;   //ADC1 reset
	RCC->APB2RSTR&=~(1<<9);//reset compleate	    
	RCC->CFGR&=~(3<<14);   //freq div clr	
//do not pass 14mhz
	RCC->CFGR|=2<<14;      	 

	ADC1->CR1|=0xC020<<0;   
	ADC1->CR2|=0x1E0000<<0;
     

	ADC1->SQR1|=0x00600006;
	ADC1->SQR2|=0x0A418826;    
	ADC1->SQR3|=0x0A418820;		   
//sampling time setting
	ADC1->SMPR2=0x00000000;	  

	     
									 //cr2  0x00160000
									 //cr1	0x00006820
									 //sqr1	0x00300000
						
	ADC1->CR2|=1<<0;	    //turn on ADC	 
	ADC1->CR2|=1<<3;        //enable reset calibration  
	while(ADC1->CR2&1<<3);   //wait for calibration 			 
     		 
	ADC1->CR2|=1<<2;        //enable AD calibration	   
	while(ADC1->CR2&1<<2);  //wait while calibrating

	MY_NVIC_Init(4,3,ADC1_2_IRQChannel,2);
}
