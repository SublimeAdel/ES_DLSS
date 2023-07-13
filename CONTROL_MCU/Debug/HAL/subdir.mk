################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/buzzer.c \
../HAL/dc_motor.c \
../HAL/external_eeprom.c \
../HAL/twi.c 

OBJS += \
./HAL/buzzer.o \
./HAL/dc_motor.o \
./HAL/external_eeprom.o \
./HAL/twi.o 

C_DEPS += \
./HAL/buzzer.d \
./HAL/dc_motor.d \
./HAL/external_eeprom.d \
./HAL/twi.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c HAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Embedded Systems\Projects\final_project\CONTROL_MCU" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


