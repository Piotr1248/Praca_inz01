################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../HD44780.c \
../PCF8574.c \
../crc.c \
../ds18b20.c \
../i2c.c \
../lcd.c \
../main.c \
../onewire.c \
../pindef.c \
../uart.c 

OBJS += \
./ADC.o \
./HD44780.o \
./PCF8574.o \
./crc.o \
./ds18b20.o \
./i2c.o \
./lcd.o \
./main.o \
./onewire.o \
./pindef.o \
./uart.o 

C_DEPS += \
./ADC.d \
./HD44780.d \
./PCF8574.d \
./crc.d \
./ds18b20.d \
./i2c.d \
./lcd.d \
./main.d \
./onewire.d \
./pindef.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


