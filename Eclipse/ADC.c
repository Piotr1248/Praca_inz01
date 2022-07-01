/*
 * we.c
 *
 *  Created on: 6 paź 2018
 *      Author: Jan S
 */

#include <avr/io.h>


/*!
Inicjalizacja przetwornika 
*/
void ADC_init(void){
ADMUX|=(1<<REFS0);
ADCSRA=0b11000111;
}

/*!
funkcja do odczytu z przetwornika

jako argument należy podać nr przetwornika, z którego ma odczytać napięcie
funkcja zwraca wartość napięcia

*/
uint16_t pomiar(uint8_t nr){
	ADMUX=(ADMUX & 0xF8) | nr;
	ADCSRA=0b11000111;

	while(ADCSRA &(1<<ADSC));

	return ADC;

}
