
Update

I have more pins figured out with a few minor changes to the defines_2-4.h file but I have a few questions.

First let me say thank you so much for the help. I am learning so much on this project and really appreciate it.
My knowledge of PCB design is still fairly limited so I don't completely understand where to look to find some of the pins. These are the ones I have left over still:

// Mosfet output
#define MOSFET_OUT_PIN GPIO_PIN_13	//TODO
#define MOSFET_OUT_PORT GPIOC		//TODO

// Timer BLDC short circuit emergency shutoff define
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PIN GPIO_PIN_12	//TODO
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PORT GPIOB		//TODO

// ADC defines
#define VBATT_PIN	GPIO_PIN_4			//TODO
#define VBATT_PORT GPIOA				//TODO
#define VBATT_CHANNEL ADC_CHANNEL_4
#define CURRENT_DC_PIN	GPIO_PIN_6		//TODO
#define CURRENT_DC_PORT GPIOA			//TODO
#define CURRENT_DC_CHANNEL ADC_CHANNEL_6

// Self hold defines
#define SELF_HOLD_PIN GPIO_PIN_2		//TODO
#define SELF_HOLD_PORT GPIOB			//TODO

// Charge state defines
#define CHARGE_STATE_PIN GPIO_PIN_0		//TODO
#define CHARGE_STATE_PORT GPIOF			//TODO

I'm gonna do some research on ADCs tonight and see if I can figure out how this works. I tried to probe around a little and I just don't know enough to get any valuable information out of it. Everything I probed just went to vss or vdd pins but no GPIOs.

I think the self hold is a latching circuit? I don't know much about those yet either so I'll be looking into that as well.

I don't even know where to begin for the charge state pins... I thought that was handled in the charger itself.

And I had some questions about these ones:

#define UPPER_LED_PIN GPIO_PIN_1	//TODO
#define UPPER_LED_PORT GPIOA		//TODO
#define LOWER_LED_PIN GPIO_PIN_0	//TODO
#define LOWER_LED_PORT GPIOA		//TODO

Are these only for hoverboards that had under glow lighting?

// Debug pin defines
#define DEBUG_PIN GPIO_PIN_4	//TODO
#define DEBUG_PORT GPIOB		//TODO

Is this referring to a debug header? Like this one?
image

I have a lot more photos and better documentation for these boards now and I took apart another one to document where some of the other headers went to. The photos aren't complete yet but I've added the new routes I found today and some labels for the unknown connectors.
Lines
A Layout
Documentation

Here is the documentation I have so far in markdown format:

MCU: https://www.gigadevice.com/product/mcu/arm-cortex-m3/gd32f130c8t6


# A Board
## Buzzer
PB8

# B Board
## MOSFETs
#### Driver A (G)
PA10 -> HIN
PB15 -> LIN

#### Driver B (B)
PA9   -> HIN
PB14 -> LIN

#### Driver C (Y)
PA8   -> HIN
PB13 -> LIN


## BLE Speaker
TODO

## HALL
HALL C (Y) -> PB4
HALL B (B) -> PB5
HALL A (G) -> PB0

## UNPOP 1 (LED 0)
**PINS**
`  0  |  1   |   2  |  3 `
`NULL | NULL | NULL | V+`

**MCU**
0 -> PC13
1 -> PC14
2 -> PC15

## UNPOP 2
LED 0 PINS rotated 90° CC

## LED 1
**PINS**
`  0  |     1     |   2  |  3 `
`NULL | GREEN LED | NULL | V+`

**MCU**
0 -> PF0 (RED)
1 -> PF1 (GREEN)
2 -> PB2 (BLUE)

## TO MASTER
` 0  | 1 | 2 | 3 `
0 -> V+
1 -> PA2
2 -> PA3
3 -> GND

## UNPOP 3
` 0 | 1 `
0 -> V+
1 -> PA7

