// Basic example driving Channel 1 and 2 of the multi-channel Configurable LED/Laser Driver
// The code requires the following libraries: MCP48xx and uTimerLib
// The LED/Laser driver is based on AL5871, a 750 mA current-sink driver with both analog and PWM control
// Analog control:
// The ESP32 control the amount of current the AL5871 chips can sink using two MCP4822 12-bit Digital-to-Analog Converters (DAC), each DAC controls two channels as follows:  
// Channels 1 and 2 are controlled via U6 with chip-select pin connected to D5 of the ESP32, 
// and channels 3 & 4 controlled via U7 with chip-select pin connected to D4 of the ESP32
// For AL5871 PWM control, use the following pins for channels 1 to 4, respectively: D13, D14, D14, D15
 
#include "Arduino.h"
#include "uTimerLib.h"
#include <MCP48xx.h>

#ifndef LED_BUILTIN
	// change to fit your needs
	// Use 0 or 1 to use DigiSpark AVR internal LED (depending revision, mine is 1)
	#define LED_BUILTIN 13
#endif

uint16_t SineLUT64[] = { 2048, 2248, 2447, 2642, 2831, 3013, 3185, 3346,
3495, 3630, 3750, 3853, 3939, 4007, 4056, 4085,
4095, 4085, 4056, 4007, 3939, 3853, 3750, 3630,
3495, 3346, 3185, 3013, 2831, 2642, 2447, 2248,
2048, 1847, 1648, 1453, 1264, 1082, 910, 749,
600, 465, 345, 242, 156, 88, 39, 10,
0, 10, 39, 88, 156, 242, 345, 465,
600, 749, 910, 1082, 1264, 1453, 1648, 1847};

MCP4822 dac1(5);	//create instance of MCP4822 DAC (U6) to control channels 1 and 2
MCP4822 dac2(4);	//create instance of MCP4822 DAC (U7) to control channels 3 and 4

uint8_t counter = 0;

volatile bool status = 0;

// Create a sine wave on channel 1 
void timed_function() 
{
  status = !status;
  dac1.setVoltageA(SineLUT64[counter]);
  dac1.updateDAC();
  if(counter < 63)
       counter++;
else
    counter = 0;
}

void setup() 
{
  // We call the init() method to initialize the instance
  dac1.init();
  dac2.init();

  // The channels are turned off at startup so we need to turn the channel we need on
  dac1.turnOnChannelA();
  dac1.turnOnChannelB();
  dac2.turnOnChannelA();
  dac2.turnOnChannelB();
  
  // We configure the channels in High gain
  // It is also the default value so it is not really needed
  dac1.setGainA(MCP4822::High);
  dac1.setGainB(MCP4822::High);
  dac2.setGainA(MCP4822::High);
  dac2.setGainB(MCP4822::High);

	pinMode(LED_BUILTIN, OUTPUT);
	TimerLib.setInterval_us(timed_function, 50);
}

void loop() 
{
	digitalWrite(LED_BUILTIN, status);
}
