#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>

#include "PCF8574.h"

PCF8574 *pcf8574_init(uint8_t addr){
  PCF8574 *device = (PCF8574 *)malloc(sizeof(PCF8574));

  device->addr = addr;
  device->port = 0;
  
  return device;
}

void pcf8574_free(PCF8574 *device){
  free(device);
}
  

uint8_t pcf8574_port_read(PCF8574 *device){
  uint8_t temp;
  
  i2c_start();
  i2c_write((device->addr << 1) | PCF8574_READ);
  temp = i2c_read(ACK);
  i2c_stop();

  return temp;
}

void pcf8574_port_write(PCF8574 *device, uint8_t state){
  device->port = state;
  i2c_start();
  i2c_write((device->addr << 1) | PCF8574_WRITE);
  i2c_write(device->port);
  i2c_stop();
}
    
void pcf8574_port_toggle(PCF8574 *device){
  pcf8574_port_write(device, (device->port ^ 0xFF));
}

void pcf8574_port_blink(PCF8574 *device){
  pcf8574_port_write(device, 0xFF);
  _delay_ms(1);
  pcf8574_port_write(device, 0x00);
}


uint8_t pcf8574_pin_read(PCF8574 *device, uint8_t pin){
  return ((pcf8574_port_read(device) >> pin) & 1);
}

void pcf8574_pin_on(PCF8574 *device, uint8_t pin){
  pcf8574_port_write(device, (device->port | (1 << pin)));
}

void pcf8574_pin_off(PCF8574 *device, uint8_t pin){
  pcf8574_port_write(device, (device->port & ~(1 << pin)));
}
  
void pcf8574_pin_toggle(PCF8574 *device, uint8_t pin){
  pcf8574_port_write(device, (device->port ^ (1 << pin)));
}

void pcf8574_pin_blink(PCF8574 *device, uint8_t pin){
  pcf8574_pin_on(device, pin);
  _delay_ms(1);
  pcf8574_pin_off(device, pin);
}
