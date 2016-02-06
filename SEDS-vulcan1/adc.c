#include <stm32f10x_lib.h>
	   
//初始化ADC
//这里我们仅以规则通道为例
//我们默认将开启通道0~3																	   
 

//获得ADC值
//ch:通道值 0~3
u16 Get_Adc(u8 ch)   
{
	//设置转换序列	  		 
	ADC1->SQR3&=0XFFFFFFE0;//规则序列1 通道ch
	ADC1->SQR3|=ch;		  			    
	ADC1->CR2|=1<<22;       //启动规则转换通道 
	while(!(ADC1->SR&1<<1));//等待转换结束	 	   
	return ADC1->DR;		//返回adc值	
}




























