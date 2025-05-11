# Dam Safety Monitoring System – STM32F429

This project implements a dam safety monitoring and alert system using the STM32F429 Discovery development board. It reads the water level through an analog sensor, displays the value on an LCD, and triggers a buzzer when the level exceeds a critical threshold.

Developed as part of the Microcontrollers course at Ștefan cel Mare University of Suceava.

## Features

- Real-time water level monitoring using an analog sensor
- LCD interface displaying water level in percentage
- Acoustic alert using a buzzer when the level exceeds safety limits
- Implemented on STM32F429 using GPIO and ADC peripherals

## System Overview

The system operates in three distinct states:

- State 0: Dam is empty (sensor reading ≈ 0%). Buzzer is off.
- State 1: Water level is under the critical threshold. Buzzer remains off.
- State 2: Water level reaches the critical point. Buzzer is activated for alert.

## Hardware Used

- STM32F429I Discovery Board (Cortex-M4 core)
- Analog water level sensor (3.3V signal, analog output)
- Passive buzzer (5V)
- LCD display
- 1kΩ resistor (in series with buzzer)
- Breadboard and jumper wires

## Pin Configuration

| Pin   | Mode   | Connected Component         | Description                                       |
|-------|--------|-----------------------------|---------------------------------------------------|
| PA0   | ADC    | Water level sensor (analog) | Reads water level signal (converted analog input) |
| PB2   | GPIO   | Buzzer                      | Activates buzzer via digital HIGH/LOW signal      |
| LCD   | GPIO   | LCD Display                 | Displays current water level and alert status     |

## How It Works

1. The analog signal from the water level sensor is read via PA0 using the ADC.
2. The signal is processed and converted into a percentage.
3. The percentage is displayed on the LCD.
4. If the value exceeds a predefined threshold, the buzzer (connected to PB2) is triggered.

## Getting Started

1. Flash the firmware onto the STM32F429 board using STM32CubeIDE or equivalent.
2. Connect:
   - Water level sensor to 3.3V, GND, and PA0
   - Buzzer to PB2 via a 1kΩ resistor and GND
   - LCD to GPIO as required
3. Power the board via USB.
4. The system will begin monitoring automatically.

## Applications

- Dam and reservoir safety monitoring
- Flood detection and early warning systems
- Tank level alerts in industrial automation
