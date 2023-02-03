### Update 2.x:
- This is a fork from https://github.com/krisstakos/Hoverboard-Firmware-Hack-Gen2.1
- with different defines_2-x.h for two different board layouts :-) 
- Simply choose ` #define LAYOUT_2_0 ` or ` #define LAYOUT_2_1 ` in ` Inc/config.h ` :-))
- as only UART control is supported you can download compiled binaries [here](HoverBoardGigaDevice/ReadyToFlash/) or there: [pionierland.de/hoverhack/gen2/ReadyToFlash](https://pionierland.de/hoverhack/gen2/ReadyToFlash/) (the test-firmwares will ignore uart speed and will repeat speed from -300 to 300 instead)
- Make sure your board is one of the supported layouts ! **Wrong pin assignments can shortcut the battery and kill the mosfets !!**


#### Update 2.1:
- That's a fork from https://github.com/flo199213/Hoverboard-Firmware-Hack-Gen2
- Compiles with Keil version 6 :-))


#### version/layout 2.0:
![layout 2.0](https://raw.githubusercontent.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/main/Overview_2-0.jpg)
- [pin configuration](pins_2.0.md)
- [details](Schematics_2.0/)


#### version/layout 2.1:
![layout 2.1](https://raw.githubusercontent.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/main/Overview_2-1.jpg)


#### todo: version/layout 2.2:
![layout 2.2](https://raw.githubusercontent.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/main/Overview_2-2.jpg)
- [details](Schematics_2.2/)
- [how to unlock..](https://github.com/JRomainG/GD32F130K6-hoverboard-hack)


#### todo: version/layout 2.3:
![layout 2.2](https://raw.githubusercontent.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/main/Overview_2-3.jpg)
- [details](Schematics_2.3/)


### Hoverboard-Firmware-Hack-Gen2.x

Hoverboard Hack Firmware Generation 2.x for the Hoverboard with the two Mainboards instead of the Sensorboards (See Pictures).

This repo contains open source firmware for generic Hoverboards with two mainboards. It allows you to control the hardware of the new version of hoverboards (like the Mainboard, Motors and Battery) with an arduino or some other steering device for projects like driving armchairs.

The structure of the firmware is based on the firmware hack of Niklas Fauth (https://github.com/NiklasFauth/hoverboard-firmware-hack/). These "new" boards are using GD32F130C6, so the project is adapted to that ic

- It's required to install [Keil](https://www.keil.com/download/product/).

---

#### Hardware

The hardware has two main boards, which are identical equipped. They are connected via USART. Additionally there are some LED PCB connected at LED1(battery indicator) and LED2(auxiliry lights). There is an programming connector for ST-Link/V2 and they break out GND, USART/I2C, 5V on a second pinhead(look at the picture).

The reverse-engineered schematics of the mainboards can be found here(GEN 2):
https://github.com/krisstakos/Hoverboard-Firmware-Hack-Gen2.1/blob/main/Schematics/HoverBoard_CoolAndFun.pdf


---

#### Flashing
The firmware is built with Keil (free up to 32KByte). To build the firmware, open the Keil project file which is includes in repository. Right to the STM32, there is a debugging header with GND, 3V3, SWDIO and SWCLK. 
**Beware that some verions/layouts have  GND, SWDIO, SWCLK, 3V3 header !** So always check GND and the 3.3V pins with a multimeter, with DIO and CLK simply try and error :-)
Connect GND, SWDIO and SWCLK to your SWD programmer, like the ST-Link found on many STM devboards.

- If you never flashed your mainboard before, the controller is locked. To unlock the flash, use STM32 ST-LINK Utility or openOCD. [instructions here](https://github.com/EFeru/hoverboard-firmware-hack-FOC/wiki/How-to-Unlock-MCU-flash).
ST-Link-Utility is out of date and needs a few old mfc42.dll files! Please open an issue when you know how to unlock flash with the STM32CubeProgrammer.
- To flash the STM32, use the STM32 ST-LINK Utility (2023: STM32CubeProgrammer) as well, ST-Flash utility or Keil by itself. I was also having 100% success rate with platform.io project from [here](https://github.com/EFeru/hoverboard-sideboard-hack-GD) just for uploading. You have to rename the output file *.axf to **firmware.elf** and move/copy it to the platform.io project, then upload. 
Bonus: Kristian Kosev (krisstakos) has  included **rename.bat** which will rename and move your output file, but you have to specify the right paths.
- Hold the powerbutton while flashing the firmware, as the controller releases the power latch and switches itself off during flashing
- If Flashing with Keil using a ST-Link dongle crashes, download a fixed dll here: https://developer.arm.com/documentation/ka005381/latest
- ST-Link_Utility and Stm32CubeProgrammer seem to have problems to programm the GD32F130. Try ` st-flash write hoverboard.bin 0x8000000 ` with this open source utility: https://github.com/stlink-org/stlink/releases (ordinary Windows 10 64 bit: x86_64-w64-mingw32.zip )

#### Arduino IDE examples

![screenshot ](Arduino%20Examples/TestSpeed_screenshot.jpg)
- [download code here](Arduino%20Examples/)

