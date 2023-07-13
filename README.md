# Door Lock Security System
Here I developed a door lock security system as part of my work on embedded systems. The system employs two ATmega32 microcontrollers, one acting as a human interface and the other for control. 

To design and test the system, I created a system schematic using Proteus software. 


Here's a view of the system schematic:
![Proteus Simulation](https://github.com/SublimeAdel/ES_DLSS/blob/main/Proteus%20Simulation.jpeg "Proteus Simulation")

### Quick system rundown:
The door lock security system comprises two ATmega32 microcontrollers with distinct roles. The first microcontroller serves as the human interface, featuring a keypad for user input and an LCD display to present system messages. This microcontroller is connected to the second microcontroller via UART for data transfer.

The second microcontroller serves as the control unit, with several key components connected to it. An external EEPROM is connected via TWI to store the password securely. A buzzer is also directly connected to the control unit, which emits an alarm signal in case the maximum number of incorrect password entries is reached. Finally, the control unit uses an L293D to manage the door motors and enable secure locking and unlocking.

For this embedded system, I implemented a layered software architecture that consists of three distinct layers. To keep the code organized and modular, I created a separate folder for each microcontroller unit (MCU), and included the corresponding layer of the software architecture in each folder. 

### The three layers of the software architecture are as follows:

### - APP
  This layer contains the main application logic that governs the behavior of the entire system.
### - HAL
  This layer includes drivers for all the hardware components used in the system, making it easier to interface with the hardware and abstracting away low-level details.
### - MCAL
   This layer contains drivers for the microcontroller entities themselves, providing a standardized interface for the upper layers of the software stack to interact with the microcontroller hardware.
