#include "sys.h"
#define LED0_PWM_VAL4 TIM4->CCR2
#define LED0_PWM_VAL2_1 TIM2->CCR1
#define LED0_PWM_VAL2_2 TIM2->CCR2 
<<<<<<< HEAD

=======
#define IRO PAout(5) 
>>>>>>> 549c792ab31d606ac47ed82c636935393f51a1a1
//Human-Interface-input

//Human-Interface-output

#define mux PCout(15)


void Adc_Init(void);
u16  Get_Adc(u8 ch); 
void IO_Init(void);
void Motors_Init(u16 USM,u16 DECAY);
void motor_Init(void);	  	
void uart_init(u32 pclk2,u32 bound);
void Timer2_Init(u16 arr,u16 psc);
void Timer3_Init(u16 arr,u16 psc);
void Timer4_Init(u16 arr,u16 psc);
void Timer5_Init(u16 arr,u16 psc);
void Timer6_Init(u16 arr,u16 psc);
void PWM2_1Init(u16 arr,u16 psc);
void PWM2_2Init(u16 arr,u16 psc);
void PWM4_Init(u16 arr,u16 psc);
void PWM5_Init(u16 arr,u16 psc);
void PWM5_IN_Init(u16 arr,u16 psc);
void EXTIX_Init(void);
