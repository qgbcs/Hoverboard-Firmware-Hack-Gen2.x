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


// LED defines CORRECT
#define LED_GREEN GPIO_PIN_3
#define LED_GREEN_PORT GPIOB
#define LED_ORANGE GPIO_PIN_4
#define LED_ORANGE_PORT GPIOB
#define LED_RED GPIO_PIN_15
#define LED_RED_PORT GPIOA

#define UPPER_LED_PIN GPIO_PIN_5
#define UPPER_LED_PORT GPIOB
#define LOWER_LED_PIN GPIO_PIN_8
#define LOWER_LED_PORT GPIOB

// Mosfet output CORRECT
#define MOSFET_OUT_PIN GPIO_PIN_13
#define MOSFET_OUT_PORT GPIOC

// Brushless Control DC (BLDC) defines
// Channel G CORRECT
#define RCU_TIMER_BLDC RCU_TIMER0
#define TIMER_BLDC TIMER0
#define TIMER_BLDC_CHANNEL_G TIMER_CH_2
#define TIMER_BLDC_GH_PIN GPIO_PIN_10
#define TIMER_BLDC_GH_PORT GPIOA
#define TIMER_BLDC_GL_PIN GPIO_PIN_15
#define TIMER_BLDC_GL_PORT GPIOB
// Channel B CORRECT
#define TIMER_BLDC_CHANNEL_B TIMER_CH_1
#define TIMER_BLDC_BH_PIN GPIO_PIN_9
#define TIMER_BLDC_BH_PORT GPIOA
#define TIMER_BLDC_BL_PIN GPIO_PIN_14
#define TIMER_BLDC_BL_PORT GPIOB
// Channel Y CORRECT
#define TIMER_BLDC_CHANNEL_Y TIMER_CH_0
#define TIMER_BLDC_YH_PIN GPIO_PIN_8
#define TIMER_BLDC_YH_PORT GPIOA
#define TIMER_BLDC_YL_PIN GPIO_PIN_13
#define TIMER_BLDC_YL_PORT GPIOB

// Timer BLDC short circuit emergency shutoff define LOOKS LIKE
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PIN GPIO_PIN_12
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PORT GPIOB

// Hall sensor defines CORRECT
#define HALL_A_PIN GPIO_PIN_0
#define HALL_A_PORT GPIOA
#define HALL_C_PIN GPIO_PIN_11
#define HALL_C_PORT GPIOB
#define HALL_B_PIN GPIO_PIN_1
#define HALL_B_PORT GPIOA

// Usart master slave defines CORRECT
#define USART_MASTERSLAVE USART1
#define USART_MASTERSLAVE_TX_PIN GPIO_PIN_2
#define USART_MASTERSLAVE_TX_PORT GPIOA
#define USART_MASTERSLAVE_RX_PIN GPIO_PIN_3
#define USART_MASTERSLAVE_RX_PORT GPIOA

// ADC defines CORRECT
#define VBATT_PIN	GPIO_PIN_4
#define VBATT_PORT GPIOA
#define VBATT_CHANNEL ADC_CHANNEL_4
#define CURRENT_DC_PIN	GPIO_PIN_6
#define CURRENT_DC_PORT GPIOA
#define CURRENT_DC_CHANNEL ADC_CHANNEL_6

// Self hold defines CORRECT
#define SELF_HOLD_PIN GPIO_PIN_2
#define SELF_HOLD_PORT GPIOB

// Button defines CORRECT - voltage is too low
#define BUTTON_PIN GPIO_PIN_5
#define BUTTON_PORT GPIOA

// Usart steer defines CURRENTLY USED AS I2C MPU 6050
#define USART_STEER_COM USART0
#define USART_STEER_COM_TX_PIN GPIO_PIN_6
#define USART_STEER_COM_TX_PORT GPIOB
#define USART_STEER_COM_RX_PIN GPIO_PIN_7
#define USART_STEER_COM_RX_PORT GPIOB

#ifdef MASTER
// Buzzer defins CORRECT
#define BUZZER_PIN GPIO_PIN_9
#define BUZZER_PORT GPIOB

// Charge state defines CORRECT
#define CHARGE_STATE_PIN GPIO_PIN_15
#define CHARGE_STATE_PORT GPIOC
#endif

