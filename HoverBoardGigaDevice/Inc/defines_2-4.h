/*
* This file is part of the hoverboard-firmware-hack-V2 project. The 
* firmware is used to hack the generation 2 board of the hoverboard.
* These new hoverboards have no mainboard anymore. They consist of 
* two Sensorboards which have their own BLDC-Bridge per Motor and an
* ARM Cortex-M3 processor GD32F130C8.
*
* Copyright (C) 2018 Florian Staeblein
* Copyright (C) 2018 Jakob Broemauer
* Copyright (C) 2018 Kai Liebich
* Copyright (C) 2018 Christoph Lehnert
*
* The program is based on the hoverboard project by Niklas Fauth. The 
* structure was tried to be as similar as possible, so that everyone 
* could find a better way through the code.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


// LED defines
#define LED_GREEN GPIO_PIN_15	// Batman313v, color might be wrong
#define LED_GREEN_PORT GPIOC	// Batman313v
#define LED_ORANGE GPIO_PIN_14	// Batman313v, color might be wrong
#define LED_ORANGE_PORT GPIOC	// Batman313v
#define LED_RED GPIO_PIN_13		// Batman313v, color might be wrong
#define LED_RED_PORT GPIOC		// Batman313v

#define UPPER_LED_PIN GPIO_PIN_1	// Batman313v, color might be wrong
#define UPPER_LED_PORT GPIOF		// Batman313v
#define LOWER_LED_PIN GPIO_PIN_0	// Batman313v, color might be wrong
#define LOWER_LED_PORT GPIOF		// Batman313v

// Mosfet output
#define MOSFET_OUT_PIN GPIO_PIN_13	//TODO
#define MOSFET_OUT_PORT GPIOC		//TODO

// Brushless Control DC (BLDC) defines
// Channel G
#define RCU_TIMER_BLDC RCU_TIMER0
#define TIMER_BLDC TIMER0
#define TIMER_BLDC_CHANNEL_G TIMER_CH_2
#define TIMER_BLDC_GH_PIN GPIO_PIN_10	//SAME AS 2.0 :-)
#define TIMER_BLDC_GH_PORT GPIOA		//SAME AS 2.0 :-)
#define TIMER_BLDC_GL_PIN GPIO_PIN_15	//SAME AS 2.0 :-)
#define TIMER_BLDC_GL_PORT GPIOB		//SAME AS 2.0 :-)
// Channel B
#define TIMER_BLDC_CHANNEL_B TIMER_CH_1
#define TIMER_BLDC_BH_PIN GPIO_PIN_9	//SAME AS 2.0 :-)
#define TIMER_BLDC_BH_PORT GPIOA		//SAME AS 2.0 :-)
#define TIMER_BLDC_BL_PIN GPIO_PIN_14	//SAME AS 2.0 :-)
#define TIMER_BLDC_BL_PORT GPIOB		//SAME AS 2.0 :-)
// Channel Y
#define TIMER_BLDC_CHANNEL_Y TIMER_CH_0
#define TIMER_BLDC_YH_PIN GPIO_PIN_8	//SAME AS 2.0 :-)
#define TIMER_BLDC_YH_PORT GPIOA		//SAME AS 2.0 :-)
#define TIMER_BLDC_YL_PIN GPIO_PIN_13	//SAME AS 2.0 :-)
#define TIMER_BLDC_YL_PORT GPIOB		//SAME AS 2.0 :-)

// Timer BLDC short circuit emergency shutoff define
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PIN GPIO_PIN_12	//TODO
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PORT GPIOB		//TODO

// Hall sensor defines
#define HALL_A_PIN GPIO_PIN_0	// Batman313v
#define HALL_A_PORT GPIOB		// Batman313v
#define HALL_B_PIN GPIO_PIN_5	// Batman313v
#define HALL_B_PORT GPIOB		// Batman313v
#define HALL_C_PIN GPIO_PIN_4	// Batman313v
#define HALL_C_PORT GPIOB		// Batman313v

// Usart master slave defines
#define USART_MASTERSLAVE USART1
#define USART_MASTERSLAVE_TX_PIN GPIO_PIN_2		//SAME AS 2.0 :-)
#define USART_MASTERSLAVE_TX_PORT GPIOA			//SAME AS 2.0 :-)
#define USART_MASTERSLAVE_RX_PIN GPIO_PIN_3		//SAME AS 2.0 :-)
#define USART_MASTERSLAVE_RX_PORT GPIOA			//SAME AS 2.0 :-)

// ADC defines
#define VBATT_PIN	GPIO_PIN_0			// Batman313v, might be CURRENT_DC !!!
#define VBATT_PORT GPIOA				// Batman313v
#define VBATT_CHANNEL ADC_CHANNEL_4
#define CURRENT_DC_PIN	GPIO_PIN_1		// Batman313v, might be VBATT !!!
#define CURRENT_DC_PORT GPIOA			// Batman313v
#define CURRENT_DC_CHANNEL ADC_CHANNEL_6

// Self hold defines
#define SELF_HOLD_PIN GPIO_PIN_2		//TODO
#define SELF_HOLD_PORT GPIOB			//TODO

// Button defines
#define BUTTON_PIN GPIO_PIN_15		//TODO
#define BUTTON_PORT GPIOC			//TODO

// Usart steer defines
#define USART_STEER_COM USART0
#define USART_STEER_COM_TX_PIN GPIO_PIN_6	//SAME AS 2.0 but left open at missing bluetooth chip 
#define USART_STEER_COM_TX_PORT GPIOB		//SAME AS 2.0 but left open at missing bluetooth chip 
#define USART_STEER_COM_RX_PIN GPIO_PIN_7	//SAME AS 2.0 but left open at missing bluetooth chip 
#define USART_STEER_COM_RX_PORT GPIOB		//SAME AS 2.0 but left open at missing bluetooth chip 

#ifdef MASTER
// Buzzer defines
#define BUZZER_PIN GPIO_PIN_8		// Batman313v
#define BUZZER_PORT GPIOB			// Batman313v

// Charge state defines
#define CHARGE_STATE_PIN GPIO_PIN_0		//TODO
#define CHARGE_STATE_PORT GPIOF			//TODO
#endif

// Debug pin defines
#define DEBUG_PIN GPIO_PIN_4	//TODO
#define DEBUG_PORT GPIOB		//TODO

