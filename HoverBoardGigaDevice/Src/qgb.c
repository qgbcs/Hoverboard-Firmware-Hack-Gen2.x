#ifndef GD32F1X0_H
	#include "gd32f1x0.h"
#endif 

#include <stdio.h>
int fputc(int ch, FILE* stream){
    usart_data_transmit(USART1,ch);
	while (usart_flag_get(USART1, USART_FLAG_TBE) == RESET) {}
    return ch;
}
int fgetc(FILE* file)
{
	while (usart_flag_get(USART1, USART_FLAG_RBNE)!= 1) {
		fwdgt_counter_reload();
	}		
	
	return usart_data_receive(USART1);
	
	// usart_data_transmit(USART1,ch);
	// while (usart_flag_get(USART1, USART_FLAG_TBE) == RESET) {}
}
void _sys_exit(int x){
	x = x;

}
FILE __stdout;//must or not run main qgb
FILE __stdin;//must or not run main qgb

void USART_config(uint32_t usart_periph,uint32_t baudval)
{
	rcu_usart_clock_config(CK_APB2);         
	rcu_periph_clock_enable(RCU_USART0) ;    
	rcu_periph_clock_enable(RCU_USART1) ;    //??USART1????
	
	gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_2);
	gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_2 );
	gpio_output_options_set(GPIOA,GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
   
	gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_3);
	gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_3 );  
			gpio_output_options_set(GPIOA,GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
	
	
	// nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
	
	usart_deinit(usart_periph);    //复位USART
   
	usart_baudrate_set(usart_periph,baudval);   //设置波特率
	usart_enable(usart_periph);                                 //使能USART(UEN=1)
	usart_transmit_config(usart_periph,USART_TRANSMIT_ENABLE);  //使能发送器(TEN=1)
	usart_receive_config(usart_periph,USART_RECEIVE_ENABLE);    //使能接收器(REN=1)
}
