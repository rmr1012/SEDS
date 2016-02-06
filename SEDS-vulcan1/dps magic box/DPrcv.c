#include <reg60s2.h>
#include <intrins.h>

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define FOSC 18432000L      //System frequency
#define BAUD 9600           //UART baudrate
unsigned int RCV,pass,goahead;
sbit ot1 = P0^0;
sbit ot2 = P0^1;
sbit ot3 = P0^2;
sbit ot4 = P0^3;
sbit ot5 = P0^4;
sbit ot6 = P0^5;
sbit ot7 = P0^6;
sbit ot8 = P0^7;


sbit r1 = P2^0;
sbit r2 = P2^1;
sbit r3 = P2^2;
sbit r4 = P2^3;
sbit r5 = P2^4;
sbit r6 = P2^5;
sbit r7 = P2^6;
sbit r8 = P2^7;
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
	P0M0=0x80;
	P0M1=0x00;
	PCON &= 0x7F;		//??????
	SCON = 0x50;		//8???,?????
	AUXR &= 0xFB;		//???????????Fosc/12,?12T
	BRT = 0xFD;		//?????????????
	AUXR |= 0x01;		//??1?????????????????
	AUXR |= 0x10;		//??????????
	ES = 1;                 //Enable UART interrupt
	EA = 1;                    //Open master interrupt switch
	while(1)
	{
		while(!goahead);
		goahead=0;
		if(SBUF==0xa5)
			pass=0;
		else
			pass=1;
		while(!goahead&!pass);
		 goahead=0;
		if(!pass)
			RCV=SBUF;
		while(!goahead&!pass);
		goahead=0;
		if(SBUF==0x5a)
			P0=RCV;   
		pass=0;
	}
}

/*----------------------------
UART interrupt service routine
----------------------------*/
void Uart_Isr() interrupt 4 using 1
{
	IND=!IND;
		if (RI)
    {
        RI = 0;             //Clear receive interrupt flag
        goahead=1;
		}
		TI=0;
}






