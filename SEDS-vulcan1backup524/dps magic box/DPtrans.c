#include <reg60s2.h>
#include <intrins.h>

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define FOSC 18432000L      //System frequency
#define BAUD 9600           //UART baudrate
#define T1MS (65536-FOSC/12/25)
           //wakeup and clock output control register
sbit T0CLKO   = P3^4;               //timer0 clock output pin
sbit sw1 = P0^0;
sbit sw2 = P0^1;
sbit sw3 = P0^2;
sbit sw4 = P0^3;
sbit sw5 = P0^4;
sbit sw6 = P0^5;
sbit sw7 = P0^6;
sbit sw8 = P0^7;
sbit IND=P3^4;

void delay_ms(int m)		//@24.000MHz
{
	unsigned char i, j;

	i = 24*m;
	j = 85;
	do
	{
		while (--j);
	} while (--i);
}

void main()
{
	unsigned int Sav=0;
	PCON &= 0x7F;		//??????
	SCON = 0x50;		//8???,?????
	AUXR &= 0xFB;		//???????????Fosc/12,?12T
	BRT = 0xFD;		//?????????????
	AUXR |= 0x01;		//??1?????????????????
	AUXR |= 0x10;		//??????????
	ES = 1;                 //Enable UART interrupt
	EA = 1;                 //Open master interrupt switch
//	T1M0=0xff;//push pull
	//T1M1=0x00;
//	AUXR = 0x80; 
	//timer0 work in 1T mode
		TMOD = 0x01;                    //set timer0 as mode1 (16-bit)
    TL0 = T1MS;                     //initial timer0 low byte
    TH0 = T1MS >> 8;                //initial timer0 high byte
    TR0 = 1;                        //timer0 start running
    ET0 = 1;                        //enable timer0 interrupt
    EA = 1;                         //timer0 start running
	while(1)
	{
		P1=P0;
	}
}

/*----------------------------
UART interrupt service routine
----------------------------*/
void Uart_Isr() interrupt 4 using 1
{
	IND=!IND;
    if (TI)
    {
        TI = 0;             //Clear transmit interrupt flag
    }
}

void tm0_isr() interrupt 1 using 1
{
    TL0 = T1MS;                     //reload timer0 low byte
    TH0 = T1MS >> 8;               //reload timer0 high byte
    IND=!IND;
		SBUF=0xa5;
		delay_ms(1);
		SBUF=(0x01*sw4)|(0x02*sw6)|(0x04*sw3)|(0x08*sw5)|(0x10*sw1)|(0x20*sw8)|(0x40*sw2)|(0x80*sw7);
		delay_ms(1); 
		SBUF=0x5a;
}




