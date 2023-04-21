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

#define ARM_MATH_CM3

#include "gd32f1x0.h"
int HALL_A_PIN=GPIO_PIN_11;
int HALL_A_PORT=GPIOB;
int HALL_B_PIN=GPIO_PIN_1;
int HALL_B_PORT=GPIOA;
int HALL_C_PIN=GPIO_PIN_14;
int HALL_C_PORT=GPIOC;

#include "../Inc/setup.h"
#include "../Inc/config.h"
#include "../Inc/defines.h"
#include "../Inc/it.h"
#include "../Inc/bldc.h"
#include "../Inc/commsMasterSlave.h"
#include "../Inc/commsSteering.h"
#include "../Inc/commsBluetooth.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <math.h>     
//#include "arm_math.h" 

#ifdef MASTER


DataSlave oDataSlave;

int32_t steer = 0; 												// global variable for steering. -1000 to 1000
int32_t speed = 0; 												// global variable for speed.    -1000 to 1000
FlagStatus activateWeakening = RESET;			// global variable for weakening
FlagStatus beepsBackwards = SET;  			// global variable for beeps backwards
			
extern uint8_t buzzerFreq;    						// global variable for the buzzer pitch. can be 1, 2, 3, 4, 5, 6, 7...
extern uint8_t buzzerPattern; 						// global variable for the buzzer pattern. can be 1, 2, 3, 4, 5, 6, 7...
			
extern float batteryVoltage; 							// global variable for battery voltage
extern float currentDC; 									// global variable for current dc
extern float realSpeed; 									// global variable for real Speed
uint8_t slaveError = 0;										// global variable for slave error
	
extern FlagStatus timedOut;								// Timeoutvariable set by timeout timer

uint32_t inactivity_timeout_counter = 0;	// Inactivity counter
uint32_t steerCounter = 0;								// Steer counter for setting update rate

void ShowBatteryState(uint32_t pin);
void BeepsBackwards(FlagStatus beepsBackwards);
void ShutOff(void);
#endif

const float lookUpTableAngle[181] =  
{
  -1,
  -0.937202577,
  -0.878193767,
  -0.822607884,
  -0.770124422,
  -0.720461266,
  -0.673369096,
  -0.628626737,
  -0.58603728,
  -0.545424828,
  -0.506631749,
  -0.46951635,
  -0.433950895,
  -0.399819915,
  -0.367018754,
  -0.335452314,
  -0.30503398,
  -0.275684674,
  -0.24733204,
  -0.219909731,
  -0.193356783,
  -0.167617063,
  -0.142638788,
  -0.118374098,
  -0.094778672,
  -0.071811398,
  -0.049434068,
  -0.027611115,
  -0.006309372,
  0.014502141,
  0.03485241,
  0.054768601,
  0.074276213,
  0.093399224,
  0.112160212,
  0.130580478,
  0.148680146,
  0.166478264,
  0.183992885,
  0.201241154,
  0.218239378,
  0.235003093,
  0.251547129,
  0.267885663,
  0.284032276,
  0.3,
  0.315801365,
  0.331448439,
  0.34695287,
  0.362325923,
  0.377578512,
  0.392721236,
  0.407764409,
  0.422718089,
  0.437592106,
  0.45239609,
  0.467139493,
  0.48183162,
  0.496481645,
  0.511098642,
  0.5256916,
  0.540269454,
  0.554841097,
  0.569415411,
  0.584001283,
  0.598607627,
  0.613243408,
  0.627917665,
  0.642639528,
  0.657418247,
  0.672263213,
  0.687183982,
  0.702190301,
  0.717292134,
  0.732499689,
  0.747823448,
  0.763274197,
  0.778863056,
  0.794601516,
  0.810501473,
  0.826575268,
  0.842835728,
  0.859296209,
  0.875970644,
  0.892873598,
  0.910020317,
  0.927426794,
  0.94510983,
  0.963087109,
  0.981377271,
  1,
  1.018976116,
  1.038327677,
  1.058078086,
  1.07825222,
  1.098876565,
  1.119979359,
  1.141590767,
  1.163743061,
  1.186470823,
  1.209811179,
  1.23380405,
  1.258492439,
  1.283922754,
  1.310145166,
  1.33721402,
  1.365188293,
  1.394132116,
  1.42411537,
  1.455214362,
  1.487512601,
  1.521101681,
  1.556082309,
  1.592565485,
  1.630673867,
  1.670543366,
  1.712325006,
  1.7561871,
  1.802317825,
  1.85092826,
  1.902255998,
  1.956569473,
  2.014173151,
  2.075413814,
  2.140688197,
  2.210452351,
  2.28523318,
  2.365642792,
  2.452396478,
  2.546335439,
  2.648455802,
  2.75994605,
  2.882235846,
  3.01706052,
  3.166547428,
  3.333333333,
  3.520726642,
  3.732935875,
  3.97539819,
  4.255263139,
  4.582124498,
  4.96916252,
  5.434992778,
  6.006790189,
  6.72584757,
  7.658112588,
  8.915817681,
  10.70672711,
  13.46326037,
  18.25863694,
  28.69242032,
  68.95533643,
  -158.4943784,
  -36.21729907,
  -20.22896451,
  -13.92536607,
  -10.55089693,
  -8.447794056,
  -7.010715755,
  -5.965979741,
  -5.171786508,
  -4.547320366,
  -4.043147824,
  -3.62733258,
  -3.278323283,
  -2.981049637,
  -2.72465641,
  -2.501126036,
  -2.304408198,
  -2.129851283,
  -1.973820239,
  -1.833433222,
  -1.706376086,
  -1.590769119,
  -1.485069639,
  -1.387999671,
  -1.29849148,
  -1.21564602,
  -1.138700863,
  -1.067005175,
  -1
};

#include "qgb.c"
//----------------------------------------------------------------------------
// MAIN function
//----------------------------------------------------------------------------
int main (void)
{
#ifdef MASTER
	FlagStatus enable = RESET;
	FlagStatus enableSlave = RESET;
	FlagStatus chargeStateLowActive = SET;
	int16_t sendSlaveValue = 0;
	uint8_t sendSlaveIdentifier = 0;
	int8_t index = 8;
  int16_t pwmSlave = 0;
	int16_t pwmMaster = 0;
	int16_t scaledSpeed = 0;
	int16_t scaledSteer  = 0;
	float expo = 0;
	float steerAngle = 0;
	float xScale = 0;
#endif
	
	//SystemClock_Config();
  SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock / 100);
	
	// Init watchdog
	if (
		Watchdog_init() == ERROR)
	{
		// If an error accours with watchdog initialization do not start device
		while(1);
	}
	
	// Init Interrupts
	Interrupt_init();
	
	// Init timeout timer
	TimeoutTimer_init();
	
	// Init GPIOs
	GPIO_init();
	
	// Activate self hold direct after GPIO-init
	gpio_bit_write(SELF_HOLD_PORT, SELF_HOLD_PIN, SET);

	// Init usart master slave
	// USART_MasterSlave_init();
	
	// Init ADC
	ADC_init();
	
	// Init PWM
	PWM_init();
	
	// Device has 1,6 seconds to do all the initialization
	// afterwards watchdog will be fired
	fwdgt_counter_reload();

	// Init usart steer/bluetooth
	USART_Steer_COM_init();

#ifdef MASTER
	// Startup-Sound
	for (; index >= 0; index--)
	{
    buzzerFreq = index;
    Delay(10);
  }
  buzzerFreq = 0;

	// Wait until button is pressed
	while (gpio_input_bit_get(BUTTON_PORT, BUTTON_PIN))
	{
		// Reload watchdog while button is pressed
		fwdgt_counter_reload();
	}
#endif

	USART_config(USART1,57600);
  while(1){
	steerCounter++;	
	printf("========== %d\r\n", steerCounter);	
	
	int n=0;
	int retVal;

	// do {
		/////// fflush(stdin); 
		retVal = scanf("%d", &n);
		if (retVal == 0) {
			printf("Invalid input! Please enter an integer %d \r\n",retVal);
		} 
	// } while(retVal == 0); 
	if(n==1){   //ABC
HALL_A_PIN =GPIO_PIN_1;
HALL_A_PORT=GPIOA;
HALL_B_PIN =GPIO_PIN_11;
HALL_B_PORT=GPIOB;
HALL_C_PIN =GPIO_PIN_14;
HALL_C_PORT=GPIOC;
printf("1 ABC");
}else if(n==2){   //ACB
HALL_A_PIN =GPIO_PIN_1;
HALL_A_PORT=GPIOA;
HALL_C_PIN =GPIO_PIN_11;
HALL_C_PORT=GPIOB;
HALL_B_PIN =GPIO_PIN_14;
HALL_B_PORT=GPIOC;
printf("2 ACB");
}else if(n==3){   //BAC
HALL_B_PIN =GPIO_PIN_1;
HALL_B_PORT=GPIOA;
HALL_A_PIN =GPIO_PIN_11;
HALL_A_PORT=GPIOB;
HALL_C_PIN =GPIO_PIN_14;
HALL_C_PORT=GPIOC;
printf("3 BAC");
}else if(n==4){   //BCA
HALL_B_PIN =GPIO_PIN_1;
HALL_B_PORT=GPIOA;
HALL_C_PIN =GPIO_PIN_11;
HALL_C_PORT=GPIOB;
HALL_A_PIN =GPIO_PIN_14;
HALL_A_PORT=GPIOC;
printf("4 BCA");
}else if(n==5){   //CAB
HALL_C_PIN =GPIO_PIN_1;
HALL_C_PORT=GPIOA;
HALL_A_PIN =GPIO_PIN_11;
HALL_A_PORT=GPIOB;
HALL_B_PIN =GPIO_PIN_14;
HALL_B_PORT=GPIOC;
printf("5 CAB");
}else if(n==6){   //CBA
HALL_C_PIN =GPIO_PIN_1;
HALL_C_PORT=GPIOA;
HALL_B_PIN =GPIO_PIN_11;
HALL_B_PORT=GPIOB;
HALL_A_PIN =GPIO_PIN_14;
HALL_A_PORT=GPIOC;
printf("6 CBA"); 
	}else if(n==7){
		ShutOff();
	}else if(n>8 || n<-8){
		
		printf("You entered: %d\r\n", n);	  
		SetEnable(SET);
		SetPWM(n);
		
	}else{
		SetEnable(RESET);
		SetPWM(0);
	}
	  
	
	

	
	//Delay(DELAY_IN_MAIN_LOOP);
	// Reload watchdog (watchdog fires after 1,6 seconds)
	fwdgt_counter_reload();
  }
}

#ifdef MASTER
//----------------------------------------------------------------------------
// Turns the device off
//----------------------------------------------------------------------------
void ShutOff(void)
{
	int index = 0;

	buzzerPattern = 0;
	for (; index < 8; index++)
	{
		buzzerFreq = index;
		Delay(10);
	}
	buzzerFreq = 0;

	
	#ifdef USART_MASTERSLAVE
		// Send shut off command to slave
		SendSlave(0, RESET, SET, RESET, RESET, RESET);
	
	// Disable usart
		usart_deinit(USART_MASTERSLAVE);
	#endif
	
	// Set pwm and enable to off
	SetEnable(RESET);
	SetPWM(0);
	
	gpio_bit_write(SELF_HOLD_PORT, SELF_HOLD_PIN, RESET);
	while(1)
	{
		// Reload watchdog until device is off
		fwdgt_counter_reload();
	}
}

//----------------------------------------------------------------------------
// Shows the battery state on the LEDs
//----------------------------------------------------------------------------
void ShowBatteryState(uint32_t pin)
{
	if(pin == LED_ORANGE){
		#ifdef THIRD_LED
		//gpio_bit_write(LED_ORANGE_PORT, LED_ORANGE, SET);
		#else
			gpio_bit_write(LED_GREEN_PORT, LED_GREEN, SET);
			gpio_bit_write(LED_RED_PORT, LED_RED, SET);
		#endif
	}
	else{
		gpio_bit_write(LED_GREEN_PORT, LED_GREEN, pin == LED_GREEN ? SET : RESET);
		gpio_bit_write(LED_RED_PORT, LED_RED, pin == LED_RED ? SET : RESET);
		gpio_bit_write(LED_ORANGE_PORT, LED_ORANGE, RESET);
	}
}

//----------------------------------------------------------------------------
// Beeps while driving backwards
//----------------------------------------------------------------------------
void BeepsBackwards(FlagStatus beepsBackwards)
{
	// If the speed is less than -50, beep while driving backwards
	if (beepsBackwards == SET && speed < -50)
	{
		buzzerFreq = 5;
    buzzerPattern = 4;
	}
	else
	{
		buzzerFreq = 0;
		buzzerPattern = 0;
	}
}
#endif
