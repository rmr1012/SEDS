#include "sys.h"   

//IO direction set-up
#define DS18B20_IO_IN()  {GPIOA->CRL&=0XFFFFFFF0;GPIOA->CRL|=8<<0;}
#define DS18B20_IO_OUT() {GPIOA->CRL&=0XFFFFFFF0;GPIOA->CRL|=3<<0;}
//IO											   
#define	DS18B20_DQ_OUT PAout(0) //数据端口	PA0 
#define	DS18B20_DQ_IN  PAin(0)  //数据端口	PA0 
u8 DS18B20_Init(void);//initialize DS18B20
void DS18B20_Write_Addr(u32 dath,u32 datl);
short DS18B20_Get_Temp(u8 ch);//get temp
void DS18B20_Start(void);//start conversion
void DS18B20_Write_Byte(u8 dat);//weite 1 byte
u8 DS18B20_Read_Byte(void);//rd 1b
u8 DS18B20_Read_Bit(void);//rd 1 bit
u8 DS18B20_Check(void);
void DS18B20_Rst(void);//reset   
void startconv(void);
















