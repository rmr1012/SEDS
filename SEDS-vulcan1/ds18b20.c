#include "ds18b20.h"
#include "delay.h"
//#include "init.c"

void DS18B20_Rst(void)	   
{              
	DS18B20_IO_OUT(); //SET PA0 OUTPUT
    DS18B20_DQ_OUT=0; //set low DQ
    delay_us(550);    //for750us
    DS18B20_DQ_OUT=1; //DQ=1 
	delay_us(15);     //15US
}

u8 DS18B20_Check(void) 	   
{   
	u8 retry=0;
	DS18B20_IO_IN();//SET PA0 INPUT	 
    while (DS18B20_DQ_IN&&retry<100)
	{
		retry++;
		delay_us(1);
	}	 
	if(retry>=100)return 1;
	else retry=0;
    while (!DS18B20_DQ_IN&&retry<240)
	{
		retry++;
		delay_us(1);
	}
	if(retry>=240)return 1;
	return 0;
}

u8 DS18B20_Read_Bit(void) 			 // read one bit
{
    
	u8 data;
	DS18B20_IO_OUT();//SET PA0 OUTPUT
    DS18B20_DQ_OUT=0; 
	delay_us(2);
    DS18B20_DQ_OUT=1; 
	DS18B20_IO_IN();//SET PA0 INPUT
	delay_us(12);
	if(DS18B20_DQ_IN)data=1;
    else data=0;	 
    delay_us(50); 
    return data;
	
}
void OWWrite_bit(u8 v)
{
	if (v & 1) {
		
		DS18B20_IO_OUT();//SET PA0 OUTPUT
		DS18B20_DQ_OUT=0;
		delay_us(10);
		DS18B20_DQ_OUT=1;
		delay_us(55);
	} else {
		
		DS18B20_IO_OUT();//SET PA0 OUTPUT
		DS18B20_DQ_OUT=0;
		delay_us(65);
		DS18B20_DQ_OUT=1;
		delay_us(5);
	}
}

u8 DS18B20_Read_Byte(void)    // read one byte
{        
   	
    u8 i,j,dat;
    dat=0;
	for (i=1;i<=8;i++) 
	{
        j=DS18B20_Read_Bit();
        dat=(j<<7)|(dat>>1);
    }	
    return dat;
}
//write one byte to DS18B20

void DS18B20_Write_Byte(u8 dat)     
 {             
    
	u8 j;
    u8 testb;
	DS18B20_IO_OUT();//SET PA0 OUTPUT;

    for (j=1;j<=8;j++) 
	{
        testb=dat&0x01;
        dat=dat>>1;
        if (testb) 
        {
            DS18B20_DQ_OUT=0;// Write 1
            delay_us(2);                            
            DS18B20_DQ_OUT=1;
            delay_us(60);             
        }
        else 
        {
            DS18B20_DQ_OUT=0;// Write 0
            delay_us(60);             
            DS18B20_DQ_OUT=1;
            delay_us(2);                          
        }
    }
}
void DS18B20_Write_Addr(u32 dath,u32 datl)     
 {             
    
	u8 j;
    u8 testb;
	DS18B20_IO_OUT();//SET PA0 OUTPUT;

    for (j=1;j<=32;j++) 
	{
        testb=dath&0x01;
        dath=dath>>1;
        if (testb) 
        {
            DS18B20_DQ_OUT=0;// Write 1
            delay_us(2);                            
            DS18B20_DQ_OUT=1;
            delay_us(60);             
        }
        else 
        {
            DS18B20_DQ_OUT=0;// Write 0
            delay_us(60);             
            DS18B20_DQ_OUT=1;
            delay_us(2);                          
        }
    }
	for (j=1;j<=32;j++) 
	{
        testb=datl&0x01;
        datl=datl>>1;
        if (testb) 
        {
            DS18B20_DQ_OUT=0;// Write 1
            delay_us(2);                            
            DS18B20_DQ_OUT=1;
            delay_us(60);             
        }
        else 
        {
            DS18B20_DQ_OUT=0;// Write 0
            delay_us(60);             
            DS18B20_DQ_OUT=1;
            delay_us(2);                          
        }
    }
}

void DS18B20_Start(void)// ds1820 start convert
{   						               
    DS18B20_Rst();	   
	DS18B20_Check();
	delay_us(50);	 
    DS18B20_Write_Byte(0xcc);// skip rom
	delay_us(10);	
    DS18B20_Write_Byte(0x44);// convert
} 

//return 1:does not excist
//0 excist    	 
u8 DS18B20_Init(void)
{

	RCC->APB2ENR|=1<<2;     
	GPIOA->CRL=3<<0;
	GPIOA->ODR|=1<<0;      
	DS18B20_Rst();
	return DS18B20_Check();
}  
void startconv()
{
	TIM2->DIER&=0<<6; 
	TIM2->DIER&=0<<0;  //allow update interrupt
    DS18B20_Rst();	   
	DS18B20_Check();
	delay_us(50);	 
    DS18B20_Write_Byte(0xcc);
	delay_us(10);			
    DS18B20_Write_Byte(0x44);// convert
	TIM2->DIER|=1<<6;   //allow update interrupt 
	TIM2->DIER|=1<<0;
	delay_ms(75);
} 
short DS18B20_Get_Temp(u8 ch)
{
   	u8 temp;
    u8 TL,TH;
	short tem;
	u32 ads[8]={0x186e0d3b,0x182d843b,0x186e743b,0x186b0c3b,0x1873ba3b,0x1835163b,0x1834fa3b,0x1873983b};
	u32 crc[8]={0x7f000000,0xa4000000,0x71000000,0x9a000000,0x6d000000,0x39000000,0xa0000000,0xb5000000};
    DS18B20_Rst();	   
	DS18B20_Check();
	delay_us(50);	 
    DS18B20_Write_Byte(0x55);
	delay_us(10);			   
    DS18B20_Write_Addr(ads[ch],crc[ch]);
	delay_us(10);
    DS18B20_Write_Byte(0xbe);// convert	    
    TL=DS18B20_Read_Byte(); // LSB   
    TH=DS18B20_Read_Byte(); // MSB  
	    	  
    if(TH>7)
    {
        TH=~TH;
        TL=~TL; 
        temp=0;//negative  
    }else temp=1;//positive	  	  
    tem=TH; //Hreg
    tem<<=8;    
    tem+=TL;//Lreg
    tem=(float)tem*0.625;//convert     
	if(temp)return tem; //return
	else return -tem;    
} 
u8 OWSearch(u8 *newAddr)
{
   u8 id_bit_number;
   u8 last_zero, rom_byte_number, search_result;
   u8 id_bit, cmp_id_bit;
   int i;
   unsigned char rom_byte_mask, search_direction;
   static unsigned char ROM_NO[8];
   static	u32  LastDiscrepancy = 0;
	static u8 LastDeviceFlag = FALSE;
	static u32 LastFamilyDiscrepancy = 0;

   // initialize for search
   id_bit_number = 1;
   last_zero = 0;
   rom_byte_number = 0;
   rom_byte_mask = 1;
   search_result = 0;

   // if the last call was not the last one
   if (!LastDeviceFlag)
   {
      // 1-Wire reset
	  DS18B20_Rst();
      if(DS18B20_Check())
      {
         // reset the search
         LastDiscrepancy = 0;
         LastDeviceFlag = FALSE;
         LastFamilyDiscrepancy = 0;
         return FALSE;
      }

      // issue the search command
      DS18B20_Write_Byte(0xF0);

      // loop to do the search
      do
      {
         // read a bit and its complement
         id_bit = DS18B20_Read_Bit();
         cmp_id_bit = DS18B20_Read_Bit();

         // check for no devices on 1-wire
         if ((id_bit == 1) && (cmp_id_bit == 1))
            break;
         else
         {
            // all devices coupled have 0 or 1
            if (id_bit != cmp_id_bit)
               search_direction = id_bit;  // bit write value for search
            else
            {
               // if this discrepancy if before the Last Discrepancy
               // on a previous next then pick the same as last time
               if (id_bit_number < LastDiscrepancy)
                  search_direction = ((ROM_NO[rom_byte_number] & rom_byte_mask) > 0);
               else
                  // if equal to last pick 1, if not then pick 0
                  search_direction = (id_bit_number == LastDiscrepancy);

               // if 0 was picked then record its position in LastZero
               if (search_direction == 0)
               {
                  last_zero = id_bit_number;

                  // check for Last discrepancy in family
                  if (last_zero < 9)
                     LastFamilyDiscrepancy = last_zero;
               }
            }

            // set or clear the bit in the ROM byte rom_byte_number
            // with mask rom_byte_mask
            if (search_direction == 1)
              ROM_NO[rom_byte_number] |= rom_byte_mask;
            else
              ROM_NO[rom_byte_number] &= ~rom_byte_mask;

            // serial number search direction write bit

            OWWrite_bit(search_direction);

            // increment the byte counter id_bit_number
            // and shift the mask rom_byte_mask
            id_bit_number++;
            rom_byte_mask <<= 1;

            // if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
            if (rom_byte_mask == 0)
            {
                rom_byte_number++;
                rom_byte_mask = 1;
            }
         }
      }
      while(rom_byte_number < 8);  // loop until through all ROM bytes 0-7

      // if the search was successful then
      if (!(id_bit_number < 65))
      {
         // search successful so set LastDiscrepancy,LastDeviceFlag,search_result
         LastDiscrepancy = last_zero;

         // check for last device
         if (LastDiscrepancy == 0)
            LastDeviceFlag = TRUE;

         search_result = TRUE;
      }
   }

   // if no device found then reset counters so next 'search' will be like a first
   if (!search_result || !ROM_NO[0])
   {
      LastDiscrepancy = 0;
      LastDeviceFlag = FALSE;
      LastFamilyDiscrepancy = 0;
      search_result = FALSE;
   }
   for (i = 0; i < 8; i++) newAddr[i] = ROM_NO[i];
   return search_result;
}
