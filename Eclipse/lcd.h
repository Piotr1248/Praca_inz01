/*
 * LCD.h
 *
 *  Created on: 26 lis 2020
 *      Author: Piotr‚
 */

#ifndef LCD_H_
#define LCD_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>


#include "HD44780.h"


#define Minus_przycisk !(PIND & (1<<PD2))
#define OK_LCD !(PINB & (1<<PB2))
#define Plus_przycisk !(PINB & (1<<PB4))
#define Cofnij_LCD !(PINB & (1<<PB3))


#define  MENU_TEMPERATURY  1
#define  MENU_TEMPERATURY_WYSWIETL  10
#define  MENU_TEMPERATURY_CZUJNIK1  11
#define  MENU_TEMPERATURY_CZUJNIK2  12

#define  MENU_TEMPERATURY_NASTAWA  100

#define  MENU_WILGOTNOSCI  2
#define  MENU_WILGOTNOSCI_WYSWIETL  20
#define  MENU_WILGOTNOSCI_NASTAWA  200

#define  MENU_WENTYLACJA  3
#define  MENU_WENTYLACJA_WENTYLATOR  30
#define  MENU_WENTYLACJA_PRZEPUSTNICA  31

#define  MENU_CZAS  4
#define  MENU_CZAS_WYSWIETL  40
#define  MENU_CZAS_WYSWIETL_DATE  41

#define  MENU_CZAS_NASTAWA_SEKUND   400
#define  MENU_CZAS_NASTAWA_MINUT    500
#define  MENU_CZAS_NASTAWA_GODZIN   600
#define  MENU_CZAS_NASTAWA_DNIA 	700
#define  MENU_CZAS_NASTAWA_MIESIACA 800
#define  MENU_CZAS_NASTAWA_LAT  	900

HD44780 *lcd;

extern char LCD_tab[15];
extern int a;
extern volatile int wynik;
extern uint8_t second, minute, hour, dayOfWeek, dayOfMonth, month, year;
extern volatile  int	temp_ZADANA;
extern volatile  int	w_zadana;
extern volatile	uint16_t w_aktualna;
extern  volatile  int	predkosc_wentylatora;
extern  int czujnik_1,czujnik_2;
int f_silnik_krokowy_otworz;
int f_silnik_krokowy_zamknij;

void LCD_menu(HD44780 *lcd);



#endif /* LCD_H_ */




