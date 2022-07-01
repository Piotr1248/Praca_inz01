################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HD44780.c \
../PCF8574.c \
../byteordering.c \
../ds18b20.c \
../fat.c \
../i2c.c \
../main.c \
../onewire.c \
../partition.c \
../sd_raw.c \
../uart.c 

OBJS += \
./HD44780.o \
./PCF8574.o \
./byteordering.o \
./ds18b20.o \
./fat.o \
./i2c.o \
./main.o \
./onewire.o \
./partition.o \
./sd_raw.o \
./uart.o 

C_DEPS += \
./HD44780.d \
./PCF8574.d \
./byteordering.d \
./ds18b20.d \
./fat.d \
./i2c.d \
./main.d \
./onewire.d \
./partition.d \
./sd_raw.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


