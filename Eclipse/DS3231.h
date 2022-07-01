//
//  Preston DS3231.h
//  RTC, EEPROM, TEMP, IIC test
//
//  Created by Preston Sundar on 06/05/16.
//  
//

#ifndef DS3231_h
#define DS3231_h


#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"


#define  DS3231_ADDRESS      0x68
#define  DS3231_REG_SEC		 0x00
#define  DS3231_REG_MIN		 0x01
#define  DS3231_REG_HOUR     0x02
#define  DS3231_REG_DOW		 0x03
#define  DS3231_REG_DATE     0x04
#define  DS3231_REG_MON		 0x05
#define  DS3231_REG_YEAR     0x06
#define  DS3231_REG_CON		 0x0E
#define  DS3231_REG_STATUS	 0x0F
#define  DS3231_REG_AGING	 0x10
#define  DS3231_REG_TEMPM	 0x11
#define  DS3231_REG_TEMPL	 0x12


// Convert normal decimal numbers to binary coded decimal
uint8_t decimalToBcd(uint8_t val){
    return( (val/10*16) + (val%10) );
}

// Convert binary coded decimal to normal decimal numbers
uint8_t bcdToDec(uint8_t val){
    return( (val/16*10) + (val%16) );
}



void DS3231_setTime (uint8_t second, uint8_t minute,uint8_t hour,
                    uint8_t dayOfWeek,
                    uint8_t dayOfMonth,
                    uint8_t month,
                    uint8_t year){
    
    
    i2c_start();
    i2c_write(0xD0);
    i2c_write(0x00);    //move pointer location 0 which is seconds
    i2c_write(decimalToBcd(second));
    i2c_write(decimalToBcd(minute));
    i2c_write(decimalToBcd(hour));
    i2c_write(decimalToBcd(dayOfWeek));
    i2c_write(decimalToBcd(dayOfMonth));
    i2c_write(decimalToBcd(month));
    i2c_write(decimalToBcd(year));
    i2c_stop();
    
    
}

void DS3231_getTime(uint8_t *second, uint8_t *minute,
                    uint8_t *hour,
                    uint8_t *dayOfWeek,
                    uint8_t *dayOfMonth,
                    uint8_t *month,
                    uint8_t *year){
    
	i2c_start();
	    i2c_write(DS3231_ADDRESS<<1|(int)0);
	    i2c_write(0x00);            // set DS3231 register pointer to 00h
	    i2c_stop();



	    i2c_start();
	    i2c_write(DS3231_ADDRESS<<1|(int)1);

	    *second     = bcdToDec(i2c_read(ACK) & 0x7f);
	    *minute     = bcdToDec(i2c_read(ACK));
	    *hour       = bcdToDec(i2c_read(ACK) & 0x3f);
	    *dayOfWeek  = bcdToDec(i2c_read(ACK));
	    *dayOfMonth = bcdToDec(i2c_read(ACK));
	    *month      = bcdToDec(i2c_read(ACK));
	    *year       = bcdToDec(i2c_read(ACK));



}


/*float DS3231_getTemperature(void){
//    uint8_t _msb = _readRegister(REG_TEMPM);
//    uint8_t _lsb = _readRegister(REG_TEMPL);
//    return (float)_msb + ((_lsb >> 6) * 0.25f);
    
    uint8_t tmpMsbbuf[1];
    uint8_t tmpLsbbuf[1];

    i2c_read()(DS3231_ADDRESS, 1, DS3231_REG_TEMPM, tmpMsbbuf);
    i2c_read()(DS3231_ADDRESS, 1, DS3231_REG_TEMPL, tmpLsbbuf);
    
    return (float)tmpMsbbuf[0] + ((tmpLsbbuf[0] >> 6) * 0.25f);
}*/

#endif /* DS3231_h */

