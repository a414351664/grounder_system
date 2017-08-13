#include "pwm.h"

//  ????PWM?
//----------------------------2016/11/26--???
//  void PWM_Init(void)
//  void Updata_PWM_(float DC1,float DC2,float DC3,float DC4)
//----------------------------------------------
//  ???:TIM4
//  ????:50MHz 
//  ???   m/1000 x100%
//  ?????? 2000000
//  PWM????  B6~B9
void PWM_GPIO(void){
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM4);
}


// PWM ?????
void Pwm_Init(unsigned long Frequency, uint16_t TimerPeriod, float DC1,float DC2,float DC3,float DC4)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
  TIM_OCInitTypeDef  TIM_OCInitStructure;   
  uint16_t Channel1Pulse = 0,Channel2Pulse = 0,Channel3Pulse = 0,Channel4Pulse = 0;
    //((1+0 )/(60*1000000))*(1+TimerPeriod )=1/f
  //TimerPeriod = (120*1000000 / (Frequency*8)) - 1; 
  Channel1Pulse = (uint16_t) (((uint32_t) DC1 * (TimerPeriod - 1)) / 1000);   
  Channel2Pulse = (uint16_t) (((uint32_t) DC2 * (TimerPeriod - 1)) / 1000); 
  Channel3Pulse = (uint16_t) (((uint32_t) DC3 * (TimerPeriod - 1)) / 1000);   
  Channel4Pulse = (uint16_t) (((uint32_t) DC4 * (TimerPeriod - 1)) / 1000);
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);     
  
  /* Time Base configuration */  
  TIM_TimeBaseStructure.TIM_Prescaler = (84*1000000)/(TimerPeriod*Frequency)-1;     //// ??????
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  ////????
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;    // ??????????
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;  
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;   ////?????,??????pwm???          
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);  
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;  
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;    ////???????

  //???,?????????,????????,?????????
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;    // //?????????
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;  ////???????
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;   // //?????????
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;  //????????????
  /* TIM1 counter enable */  
  TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;    // //???????
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;    // //???????
  TIM_OC2Init(TIM4, &TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_Pulse = Channel3Pulse;    // //???????
  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_Pulse = Channel4Pulse;    // //???????
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);
  
  TIM_Cmd(TIM4, ENABLE); 
  /* TIM1 Main Output Enable */  
  TIM_CtrlPWMOutputs(TIM4, ENABLE);  
}


//PWM?????
void UpdataDuty(unsigned long Frequency,uint16_t TimerPeriod,float DC1,float DC2,float DC3,float DC4)  
{  
  TIM4->CCR1 =(int)(DC1*(TimerPeriod - 1) / 1000);
  TIM4->CCR2 =(int)(DC2*(TimerPeriod - 1) / 1000);
  TIM4->CCR3 =(int)(DC3*(TimerPeriod - 1) / 1000);
  TIM4->CCR4 =(int)(DC4*(TimerPeriod - 1) / 1000);
}
//PWM???
void PWM_Init(void)
{
  PWM_GPIO();
  Pwm_Init(50,1000,0,0,0,0);
}
//PWM?????
void Updata_PWM_(float DC1,float DC2,float DC3,float DC4)
{
  UpdataDuty(50,1000,DC1,DC2,DC3,DC4);
}
