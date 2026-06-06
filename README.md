# Multi-Channel-Configurable-Laser-Driver
A low-cost, Arduino-friendly four channel programmable LED/Laser driver using  750mA sink LED driver from Diode Inc. The current is controlled using ESP32-based NodeMCU32S microcontroller board. 

This driver is designed to be low-cost built on a 2-layers PCB, inexpensive microcontroller platform and LED drivers IC "AL5871" to make it affordable to hobbyists, students and low-budget projects.

**How it works:**
The LED/Laser driver is based on AL5871, a 750 mA current-sink driver with analog and PWM control options.
- Analog control:
The ESP32 control the amount of current the AL5871 chips can sink using two MCP4822 12-bit Digital-to-Analog Converters (DAC), each DAC controls two channels as follows:  
Channels 1 & 2 are controlled via U6 with chip-select pin connected to D5 of the ESP32, and channels 3 & 4 controlled via U7 with chip-select pin connected to D4 of the ESP32
- PWM control:
PWM pin of the all AL5871 chips are connected to digital pins D13, D14, D14, and D15 of the ESP32 for PWM control.

<img width="1532" height="862" alt="Image" src="https://github.com/user-attachments/assets/0202de85-8f6e-4c0f-9966-b2d89f722523" />
