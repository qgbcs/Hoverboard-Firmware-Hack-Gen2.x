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

#include "gd32f1x0.h"
#include "../Inc/it.h"
#include "../Inc/comms.h"
#include "../Inc/commsSteering.h"
#include "../Inc/setup.h"
#include "../Inc/config.h"
#include "../Inc/defines.h"
#include "../Inc/bldc.h"
#include "stdio.h"
#include "string.h"

// Only master communicates with steerin device
#ifdef MASTER
//#define USART_STEER_TX_BYTES 2   // Transmit byte count including start '/' and stop character '\n'
#define USART_STEER_RX_BYTES 8   // Receive byte count including start '/' and stop character '\n'

extern uint8_t usartSteer_COM_rx_buf[USART_STEER_COM_RX_BUFFERSIZE];
static uint8_t sUSARTSteerRecordBuffer[USART_STEER_RX_BYTES];
static int16_t iRecordingPos = -1;		// if >= 0 incoming bytes are recorded until message size reached
void CheckUSARTSteerInput(uint8_t u8USARTBuffer[]);

extern int32_t steer;
extern int32_t speed;

typedef struct{
   uint8_t cStart;		//  = '/';
   int16_t  iSpeed;
   int16_t  iSteer;
   uint16_t checksum;
   uint8_t cEnd;			//  = '\n';
} SerialServer2Hover;

extern float batteryVoltage; 							// global variable for battery voltage
extern float currentDC; 									// global variable for current dc
extern float realSpeed; 									// global variable for real Speed

#define START_FRAME         0xABCD       // [-] Start frme definition for reliable serial communication

typedef struct{
   uint16_t cStart;		//  = 0xABCD;
   int16_t iSpeedL;		// 100* km/h
   int16_t iSpeedR;		// 100* km/h
   uint16_t iVolt;		// 100* V
   int16_t iAmpL;		// 100* A
   int16_t iAmpR;		// 100* A
   uint16_t checksum;
} SerialHover2Server;

int16_t swap_int16( int16_t val ) 
{
    return (val << 8) | ((val >> 8) & 0xFF);
}

//----------------------------------------------------------------------------
// Send frame to steer device
//----------------------------------------------------------------------------
void SendSteerDevice(void)
{
	// Ask for steer input
	
	SerialHover2Server oData;
	oData.cStart = START_FRAME;
	oData.iVolt = (uint16_t)	(batteryVoltage * 100);
	oData.iAmpL = (int16_t) (currentDC * 100);
	oData.iAmpR = 42;
	oData.iSpeedL = (int16_t) (realSpeed * 100);
	oData.iSpeedR = -42;
	oData.checksum = 	CalcCRC((uint8_t*) &oData, sizeof(oData) - 2);	// (first bytes except crc)
	SendBuffer(USART_STEER_COM, (uint8_t*) &oData, sizeof(oData));

/*	
	uint8_t buffer[2];
	int index = 0;
	buffer[0] = '/';
	buffer[1] = '\n';
	
	SendBuffer(USART_STEER_COM, buffer, 2);
	*/
}

//----------------------------------------------------------------------------
// Update USART steer input
//----------------------------------------------------------------------------
void UpdateUSARTSteerInput(void)
{
	uint8_t character = usartSteer_COM_rx_buf[0];
	if (character == '/')	// Start character is captured, start record
		iRecordingPos = 0;

	if (iRecordingPos >= 0)
	{
		sUSARTSteerRecordBuffer[iRecordingPos++] = character;
		if (iRecordingPos >= USART_STEER_RX_BYTES)
		{
			iRecordingPos = -1;
			CheckUSARTSteerInput (sUSARTSteerRecordBuffer);	// Check input
		}
	}
}

//----------------------------------------------------------------------------
// Check USART steer input
//----------------------------------------------------------------------------
void CheckUSARTSteerInput(uint8_t USARTBuffer[])
{
	if ( USARTBuffer[0] != '/' ||	USARTBuffer[USART_STEER_RX_BYTES - 1] != '\n')
		return;
	
	uint16_t crc = CalcCRC(USARTBuffer, USART_STEER_RX_BYTES - 3);	// (first bytes except crc and stop byte)
	
	if ( USARTBuffer[USART_STEER_RX_BYTES - 2] != ((crc >> 8) & 0xFF) ||
				USARTBuffer[USART_STEER_RX_BYTES - 3] != (crc & 0xFF))
		return;
	
	speed = (int16_t)((USARTBuffer[2] << 8) | USARTBuffer[1]);	// speed value -1000 to 1000
	steer = (int16_t)((USARTBuffer[4] << 8) | USARTBuffer[3]);	// steering value -1000 to 1000

	//SerialServer2Hover* pData = (SerialServer2Hover*) USARTBuffer;
	//speed = swap_int16(pData->iSpeed);
	//steer = swap_int16(pData->iSteer);
	//if (speed > 300) speed = 300	else if (speed < -300) speed = -300;

	
	// Reset the pwm timout to avoid stopping motors
	ResetTimeout();
}
#endif
