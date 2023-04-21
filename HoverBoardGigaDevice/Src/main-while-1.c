#ifdef MASTER
		steerCounter++;	
		if ((steerCounter % 2) == 0)
		{	
			// Request steering data
			SendSteerDevice();
		}
		
		#ifdef TEST_SPEED
			speed = 3 * (ABS((	((int32_t)steerCounter+100) % 400) - 200) - 100);
		//speed = 300;
		#endif
		
		// Calculate expo rate for less steering with higher speeds
		expo = MAP((float)ABS(speed), 0, 1000, 1, 0.5);
		
	  // Each speedvalue or steervalue between 50 and -50 means absolutely no pwm
		// -> to get the device calm 'around zero speed'
		scaledSpeed = speed < 50 && speed > -50 ? 0 : CLAMP(speed, -1000, 1000) * SPEED_COEFFICIENT;
		scaledSteer = steer < 50 && steer > -50 ? 0 : CLAMP(steer, -1000, 1000) * STEER_COEFFICIENT * expo;
		
		// Map to an angle of 180 degress to 0 degrees for array access (means angle -90 to 90 degrees)
		steerAngle = MAP((float)scaledSteer, -1000, 1000, 180, 0);
		xScale = lookUpTableAngle[(uint16_t)steerAngle];

		// Mix steering and speed value for right and left speed
		if(steerAngle >= 90)
		{
			pwmSlave = CLAMP(scaledSpeed, -1000, 1000);
			pwmMaster = CLAMP(pwmSlave / xScale, -1000, 1000);
		}
		else
		{
			pwmMaster = CLAMP(scaledSpeed, -1000, 1000);
			pwmSlave = CLAMP(xScale * pwmMaster, -1000, 1000);
		}
		
		// Read charge state
		chargeStateLowActive = gpio_input_bit_get(CHARGE_STATE_PORT, CHARGE_STATE_PIN);
		
		// Enable is depending on charger is connected or not
		enable = chargeStateLowActive;
		
		// Enable channel output
		SetEnable(enable);

		// Decide if slave will be enabled
		enableSlave = (enable == SET && timedOut == RESET) ? SET : RESET;
		
		// Decide which process value has to be sent
		switch(sendSlaveIdentifier)
		{
			case 0:
				sendSlaveValue = currentDC * 100;
				break;
			case 1:
				sendSlaveValue = batteryVoltage * 100;
				break;
			case 2:
				sendSlaveValue = realSpeed * 100;
				break;
				default:
					break;
		}
		
    // Set output
		SetPWM(pwmMaster);

		#ifdef USART_MASTERSLAVE
			SendSlave(-pwmSlave, enableSlave, RESET, chargeStateLowActive, sendSlaveIdentifier, sendSlaveValue);
		#endif
		
		// Increment identifier
		sendSlaveIdentifier++;
		if (sendSlaveIdentifier > 2)
		{
			sendSlaveIdentifier = 0;
		}
		
		// Show green battery symbol when battery level BAT_LOW_LVL1 is reached
    if (batteryVoltage > BAT_LOW_LVL1)
		{
			// Show green battery light
			ShowBatteryState(LED_GREEN);
			
			// Beeps backwards
			BeepsBackwards(beepsBackwards);
		}
		// Make silent sound and show orange battery symbol when battery level BAT_LOW_LVL2 is reached
    else if (batteryVoltage > BAT_LOW_LVL2 && batteryVoltage < BAT_LOW_LVL1)
		{
			// Show orange battery light
			ShowBatteryState(LED_ORANGE);
			
      buzzerFreq = 5;
      buzzerPattern = 8;
    }
		// Make even more sound and show red battery symbol when battery level BAT_LOW_DEAD is reached
		else if  (batteryVoltage > BAT_LOW_DEAD && batteryVoltage < BAT_LOW_LVL2)
		{
			// Show red battery light
			ShowBatteryState(LED_RED);
			
      buzzerFreq = 5;
      buzzerPattern = 1;
    }
		// Shut device off, when battery is dead
		else if (batteryVoltage < BAT_LOW_DEAD)
		{
      ShutOff();
    }
		else
		{
			ShutOff();
    }

		// Shut device off when button is pressed
		if (gpio_input_bit_get(BUTTON_PORT, BUTTON_PIN))
		{
      while (gpio_input_bit_get(BUTTON_PORT, BUTTON_PIN)) {}
			ShutOff();
    }
		
		// Calculate inactivity timeout (Except, when charger is active -> keep device running)
    if (ABS(pwmMaster) > 50 || ABS(pwmSlave) > 50 || !chargeStateLowActive)
		{
      inactivity_timeout_counter = 0;
    }
		else
		{
      inactivity_timeout_counter++;
    }
		
		// Shut off device after INACTIVITY_TIMEOUT in minutes
    if (inactivity_timeout_counter > (INACTIVITY_TIMEOUT * 60 * 1000) / (DELAY_IN_MAIN_LOOP + 1))
		{ 
      ShutOff();
    }
#endif	