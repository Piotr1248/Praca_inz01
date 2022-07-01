#pragma once
#include "i2c.h"

#define PCF8574_WRITE 0
#define PCF8574_READ 1

#define PCF8574_PIN_ON 1
#define PCF8574_PIN_OFF 0

typedef struct {
   uint8_t addr;
   uint8_t port;
} PCF8574;

PCF8574 *pcf8574_init(uint8_t addr);
void pcf8574_free(PCF8574 *device);

uint8_t pcf8574_port_read(PCF8574 *device);
void pcf8574_port_write(PCF8574 *device, uint8_t state);
void pcf8574_port_toggle(PCF8574 *device);
void pcf8574_port_blink(PCF8574 *device);

uint8_t pcf8574_pin_read(PCF8574 *device, uint8_t pin);
void pcf8574_pin_on(PCF8574 *device, uint8_t pin);
void pcf8574_pin_off(PCF8574 *device, uint8_t pin);
void pcf8574_pin_toggle(PCF8574 *device, uint8_t pin);
void pcf8574_pin_blink(PCF8574 *device, uint8_t pin);
