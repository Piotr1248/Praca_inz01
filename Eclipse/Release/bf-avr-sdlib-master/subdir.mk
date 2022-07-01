################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bf-avr-sdlib-master/AVRSDLib.c \
../bf-avr-sdlib-master/FAT32.c \
../bf-avr-sdlib-master/SD_routines.c \
../bf-avr-sdlib-master/SPI_routines.c \
../bf-avr-sdlib-master/UART_routines.c 

OBJS += \
./bf-avr-sdlib-master/AVRSDLib.o \
./bf-avr-sdlib-master/FAT32.o \
./bf-avr-sdlib-master/SD_routines.o \
./bf-avr-sdlib-master/SPI_routines.o \
./bf-avr-sdlib-master/UART_routines.o 

C_DEPS += \
./bf-avr-sdlib-master/AVRSDLib.d \
./bf-avr-sdlib-master/FAT32.d \
./bf-avr-sdlib-master/SD_routines.d \
./bf-avr-sdlib-master/SPI_routines.d \
./bf-avr-sdlib-master/UART_routines.d 


# Each subdirectory must supply rules for building sources it contributes
bf-avr-sdlib-master/%.o: ../bf-avr-sdlib-master/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


