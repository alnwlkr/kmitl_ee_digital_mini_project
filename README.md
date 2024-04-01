
# RC Car Gesture controlled With Arduino Nano

## Project Description
This project use knowledge from DIGITAL SYSTEMS AND MICROPROCESSORS subject at KMITL to make a mini project using arduino platform.

## In this project I have learned
- How does arduino nano works, pro and cons of arduino nano
- How does arduino nano communicate to motor driver throught digital output pin and communicate to OLED Screen with I2C Protocol.


## How to run this project

### Step 1 : List of electronics component you need
#### Part 1 : RC Car Transmitter (Controller)
- 1 x Arduino Nano nRF24L01 integrated (You can use typical Arduino Nano but you need to connect nRF24L01 module to arduino nano later)
- 1 x GY-61 ADXL335 3 axis accelerometer
- 1 x Power supply for Arduino Nano
- 1 x nRF24L01 (If you use a typical Arduino Nano)

#### Part 2 : RC Car Reciever (Car)
- 1 x Arduino Nano (You can use typical Arduino Nano but you need to connect nrf24l01 module to arduino nano later)
- 1 x L298N Motor Driver
- 4 x Arduino TT wheel motor with Wheel Kit
- 1 x SSD1306 OLED 128x64 OLED Display I2C Connected
- 1 x nRF24L01 (If you use a typical Arduino Nano)

### Connect each component together

#### Part 1 : RC Transmitter (Controller)

| GY-61 ADXL335 | Arduino Nano |
|---------------|--------------|
| VCC           | 3.3V         |
| X_OUT         | A0           |
| Y_OUT         | A1           |
| Z_OUT         | -            |
| GND           | GND          |

| Power Supply (7-12VDC) | Arduino Nano |
|------------------------|--------------|
| +                      | Vin          |
| -                      | GND          |

If you use a typical Arduino Nano (without RF Module integrated.) you need to connect the nRF24L01 to Arduino Nano with these schematic.

| nRF24L01 | Arduino Nano |
|----------|--------------|
| VCC      | 3.3V         |
| CSN      | D10          |
| MOSI     | D11          |
| IRQ      | -            |
| MISO     | D12          |
| SCK      | D13          |
| CE       | D8           |
| GND      | GND          |

NOTE : If you use a Arduino Nano RF integrated,  
change ```RF24 radio(8,10);``` to ```RF24 radio(10,9);```.  
Vice versa if you use an Arduino Nano with nRF24L01 external module.
change ```RF24 radio(10,9);``` to ```RF24 radio(8ม10);```.  

If It's doesn't work IDK.
#### Part 2 : RC Reciever (Car)

| L298n Motor Driver | Arduino Nano |
|--------------------|--------------|
| ENA                | D3           |
| IN1                | D4           |
| IN2                | D5           |
| IN3                | D6           |
| IN4                | D7           |
| ENB                | D9           |
| OUT1               | -            |
| OUT2               | -            |
| OUT3               | -            |
| OUT4               | -            |
| VS (+12V)          | -            |
| GND                | GND          |
| VSS (+5V)          | Vin          |

| L298n Motor Driver | Power Supply |
|--------------------|--------------|
| ENA                |              |
| IN1                |              |
| IN2                |              |
| IN3                |              |
| IN4                |              |
| ENB                |              |
| OUT1               |              |
| OUT2               |              |
| OUT3               |              |
| OUT4               |              |
| VS (+12V)          | +12V         |
| GND                | GND          |
| VSS (+5V)          |              |

Note : When the motor is running and the power supply is a battery, It will make voltage drop and motor may not run anymore. The voltage regulator is recommended (may be a boost converter or something else).

The L298N Motor Driver can be supply between 5 to 35 VDC, I recommend you to connect the supply higher than 9V because the 5V Pin will accurate to 5V.

| L298n Motor Driver | Motor1 | Motor2 | Motor3 | Motor4 |
|--------------------|--------|--------|--------|--------|
| ENA                |        |        |        |        |
| IN1                |        |        |        |        |
| IN2                |        |        |        |        |
| IN3                |        |        |        |        |
| IN4                |        |        |        |        |
| ENB                |        |        |        |        |
| OUT1               | +      | -      |        |        |
| OUT2               | -      | +      |        |        |
| OUT3               |        |        | -      | +      |
| OUT4               |        |        | +      | -      |
| VS (+12V)          |        |        |        |        |
| GND                |        |        |        |        |
| VSS (+5V)          |        |        |        |        |

NOTE : the wiring diagram is up to the code logic, test it by yourself and modify the code to make it walk as you wish. I recommended you to connect the motor to breadbroad for an easier cable swapping.

| nRF24L01 | Arduino Nano |
|----------|--------------|
| VCC      | 3.3V         |
| CSN      | D10          |
| MOSI     | D11          |
| IRQ      | -            |
| MISO     | D12          |
| SCK      | D13          |
| CE       | D8           |
| GND      | GND          |
## Installation

After connect all component together as above. You can simply plug in Arduino Nano to your computer and upload ```TRANSMITTER_CODE.ino``` to your Arduino Nano using Arduino IDE fo the transmitter.
And upload ```RECIEVER_CODE.ino``` to your Arduino Nano using Arduino IDE fo the reciever.

WARNING & RECOMMENDATION.

From my experience, The nRF24L01 is slihtly time sensitive. I'm not recommend to modify the code by using ```delay()```. 

I highly recommend you to use serial monitor to monitor if the data is being sended by transmitter and recieved by reciever.

Sometime the data has been comminicate for a while and got lost. I don't really know why does this keep happen but keep the connection between RF and Nano connected should be fine.
## Transmitter Features.
- Send the data by struct datatype by having yAxis and Xaxis Value in the same struct.
- At the startup, The Arduino Nano start to read the data from ADXL335 for 42 values and find the average of the data to use as a base value to use in the next part (Calibration)
- Data that had sended to the car is the relative value (It's mean we send the data that have been subtracted by base value).
- Communication Status and Data is printed to Serial.

## Reciever Features.
- 4 Controllable Direction (Forward, Reverse, Turn Left, Turn Right) up to gesture of transmitter.
- 4 Mode of OLED Screen up to its direction.
- Sensitivity of the controller can be modified on ```s``` variable
- Communication Status and Data is printed to Serial.

PS. I found out that L298N used PWM Technique to control the speed of each motor. So if we do some calculation we can control the speed of the motor by how much the controller is tilted but in this code not. 
