#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>

#include "pindef.h"
#include "onewire.h"
#include "ds18b20.h"

#include "uart.h"
#include "ADC.h"
#include "HD44780.h"
#include "lcd.h"
#include "DS3231.h"
//#define DEBUG 1
#define time_krok 5

const gpin_t sensorPin = { &PORTB, &PINB, &DDRB, PB0 };

volatile unsigned char linear_brightness_curve[256] = { 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5,
		5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 9,
		9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13,
		14, 14, 14, 15, 15, 15, 16, 16, 16, 17, 17, 18, 18, 18, 19, 19, 20, 20,
		21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 28, 28, 29, 30, 30,
		31, 32, 32, 33, 34, 35, 35, 36, 37, 38, 39, 40, 40, 41, 42, 43, 44, 45,
		46, 47, 48, 49, 51, 52, 53, 54, 55, 56, 58, 59, 60, 62, 63, 64, 66, 67,
		69, 70, 72, 73, 75, 77, 78, 80, 82, 84, 86, 88, 90, 91, 94, 96, 98, 100,
		102, 104, 107, 109, 111, 114, 116, 119, 122, 124, 127, 130, 133, 136,
		139, 142, 145, 148, 151, 155, 158, 161, 165, 169, 172, 176, 180, 184,
		188, 192, 196, 201, 205, 210, 214, 219, 224, 229, 234, 239, 244, 250,
		255 };

volatile int g = 0;
volatile int LED = 0;
volatile int LED_manual= 0;
void init_io(void);
void init_PWM(void);
void i2c_init(void);
void silnik_krokowy_otworz(void);
void silnik_krokowy_zamknij(void);

volatile int temp_ZADANA = 2300;
volatile int w_zadana = 3000;
volatile int predkosc_wentylatora;
volatile int wynik;

volatile int PWM_krokowy;
volatile int PWM_LED;

volatile int wy, calkaL = 0, calka = 0, uchyb = 0;
volatile int RTi = 20;						// odwrotnoæ sta³ej czasowej
volatile int RKp = 2;							// wzmocnienie cz³onu prop.
volatile int q = 0;

volatile uint16_t w_aktualna;

volatile int transmisja_pomiaru_wilgotnosci = 0;
volatile int transmisja_pomiaru_temperatury = 0;
volatile int transmisja_zadanej_wartosci_temperatury = 0;
volatile int transmisja_zadanej_wartosci_wilgotnosci = 0;
volatile int transmisja_zadanej_wartosci_obrotow_wentylatora = 0;
volatile int transmisja_stanu_przepustnic =0;
volatile int transmisja_nastaw_Kp =0;
volatile int transmisja_nastaw_Ti =0;



int f_silnik_krokowy_otworz=0;
int f_silnik_krokowy_zamknij=1;
char LCD_tab[15];

int temp;
int a = 1;
int czujnik_1, czujnik_2;

uint8_t second, minute, hour, dayOfWeek, dayOfMonth, month, year;

int main(void) {

	HD44780 *lcd;
	uint8_t char_array_left[8] = { 0x2, 0x6, 0xa, 0x12, 0xa, 0x6, 0x2, 0x0 };
	uint8_t char_array_right[8] = { 0x8, 0xc, 0xa, 0x9, 0xa, 0xc, 0x8, 0x0 };

	uint32_t cz1_w;
	uint32_t cz2_w;
	uint32_t cz3_w;

	char tp[20];	//deklaracja tablicy tp 20-elementowej
	char tp1[8];	//deklaracja tablicy tp1 8-elementowej
	char tp2[8];	//deklaracja tablicy tp2 8-elementowej
	char tp3[8];	//deklaracja tablicy tp3 8-elementowej
	char tp4[8];	//deklaracja tablicy tp4 8-elementowej
	char tp5[8];	//deklaracja tablicy tp5 8-elementowej
	char tp6[8];	//deklaracja tablicy tp6 8-elementowej
	char tp7[8];	//deklaracja tablicy tp7 8-elementowej
	char tp8[8];	//deklaracja tablicy tp8 8-elementowej
	char tp9[8];	//deklaracja tablicy tp9 8-elementowej


	uart_init();		//inicjalizacja UART
	init_io();			//inicjalizacja I/O
	init_PWM();			//inicjalizacja PWM
	ADC_init();			//inicjalizacja ADC
	i2c_init();			//inicjalizacja i2c
	sei();				//inicjalizacja przerwañ

	lcd = lcd_init(63);						//inicjalizacja wyswietlacza LCD
	lcd_set_char(lcd, 1, char_array_left);
	lcd_set_char(lcd, 2, char_array_right);

	pcf8574_pin_on(lcd->controller, 3);
	lcd_update(lcd, 0, 3, " Wykonal ", 9);//wpis tekstu na górny panel wyswietlacza
	lcd_update(lcd, 1, 0, "Piotr Bartosiak ", 15);//wpis tekstu na dolny panel wyswietlacza
	lcd_refresh(lcd);								//odwierzenie wyswietlacza

	_delay_ms(3000);
	lcd_clear(lcd);									//czyszczenie wyswietlacza


		while (1) {

		//sprintf(tp, "1");
		//	USART_Transmit_string(tp, strlen(tp));
		//	silnik_krokowy_ruch_lewo();
			//_delay_ms(1000);



		//	sprintf(tp, "   2");
			//		USART_Transmit_string(tp, strlen(tp));


		if (!onewire_reset(&sensorPin)) {
			//lcd_clear(lcd);							//czyszczenie wyswietlacza
			//lcd_update(lcd, 0, 0, "BRAK CZUJNIKOW ", 15);//wpis tekstu na górny panel wyswietlacza
			//_delay_ms(1000);
			continue;
		}




		ds18b20_convert(&sensorPin); 					//Start konwersji
		_delay_ms(300);

		// Wyszukanie nowego urz¹dzenia
		onewire_search_state search;
		onewire_search_init(&search);

		// Search and dump temperatures until we stop finding devices
		while (onewire_search(&sensorPin, &search)) {
			if (!onewire_check_rom_crc(&search)) {


				continue;
			}

			uint16_t reading = ds18b20_read_slave(&sensorPin, search.address);

			if (reading != kDS18B20_CrcCheckFailed) {
				temp = reading;
//tp[0]=search.address[1];
			//	uart_puts(tp);
			//	sprintf(tp, "temp %d \n",temp);
				//				uart_puts(tp);
//
				if (search.address[1] == 140) {

					czujnik_1 = temp * 6.25;


				} else if (search.address[1] == 33) {

					czujnik_2 = temp * 6.25;


				}

			} else {
				//sprintf(tp, "bad temp CRC \n");
				//uart_puts(tp);
			}
		}

		if ((czujnik_1 > 4500) || (czujnik_1 < 200))// warunek blêdnego pomiaru czujnika 1
				{
			wynik = czujnik_2;			//pomiar z czujnika 2 jest prawidlowy
		} else if ((czujnik_2 > 4500) || (czujnik_2 < 200)) // warunek blêdnego pomiaru czujnika 2
				{
			wynik = czujnik_1;			//pomiar z czujnika 1 jest prawidlowy
		} else
			wynik = ((czujnik_1 + czujnik_2) / 2); //oba czujniki wskazuja poprawna wartosc



		cz1_w = pomiar(0);						//pomiar napiêcia na porcie PA4 oraz przypisanie wartoœci do zmiennej cz1_w
		cz2_w = pomiar(1);						//pomiar napiêcia na porcie PA1 oraz przypisanie wartoœci do zmiennej cz2_w
		cz3_w = pomiar(2);						//pomiar napiêcia na porcie PA6 oraz przypisanie wartoœci do zmiennej cz3_w
		//sprintf(tp,"cz1_w=%d \n",cz1_w);

//uart_puts(tp);
//sprintf(tp,"cz2_w=%d \n",cz2_w);
		//		uart_puts(tp);
		//	sprintf(tp,"cz3_w=%d \n",cz3_w);
//
			//uart_puts(tp);
		cz1_w = cz1_w * 5000 / 1024; // ADC --> mv
		cz1_w=30 * (cz1_w - 500) / 1000;  // mv na procenty
		cz2_w = cz2_w * 5000 / 1024; // ADC --> mv
		cz2_w=30 * (cz2_w - 500) / 1000;  // mv na procenty

		if ((cz1_w > 100) || (cz1_w < 0))// warunek blêdnego pomiaru czujnika 1
						{
				w_aktualna = cz2_w;			//pomiar z czujnika 2 jest prawidlowy
				} else if ((cz2_w > 100) || (cz2_w < 0)) // warunek blêdnego pomiaru czujnika 2
						{
					w_aktualna = cz1_w;			//pomiar z czujnika 1 jest prawidlowy
				} else
					w_aktualna = ((cz1_w + cz2_w) / 2); //oba czujniki wskazuja poprawna wartosc



		predkosc_wentylatora = (OCR1A * 100) / 255;  // 255 --> 100 %

		LCD_menu(lcd);

		DS3231_getTime(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year); //odczyt czasu z modulu ds3231
		//if(hour==22&&minute==0&&second==0){LED=1;}
		//else if (hour==6&&minute==0&&second==0){LED=0;}
		//sprintf(tp, "s= %d, LED=%d, g=%d\n", second,LED,g);
		//uart_puts(tp);
		if (LED_manual == 1) {

					if (LED == 1) {

						PORTD |= (1 << PD7);

					} else if (LED == 0) {

						PORTD &= ~(1 << PD7);

					}
				} else {

					if (second < 30) {
						PORTD |= (1 << PD7);
					} else {
						PORTD &= ~(1 << PD7);
					}
				}






/////////TRANSMIJA DANYCH//////////



		sprintf(tp1, "%d %%", w_zadana / 100);

		sprintf(tp2, "%d.%d C", temp_ZADANA / 100, abs(temp_ZADANA % 100));

		sprintf(tp3, "%d %%", predkosc_wentylatora);

		sprintf(tp4, "%d.%d C", wynik / 100, abs(wynik % 100));

		sprintf(tp5, "%d %%", w_aktualna);

		sprintf(tp6, "%d",f_silnik_krokowy_otworz);

		sprintf(tp7, "%d",RKp);
		sprintf(tp8, "%d",RTi);

		if (transmisja_zadanej_wartosci_wilgotnosci) {
			USART_Transmit_string(tp1, strlen(tp1));
			transmisja_zadanej_wartosci_wilgotnosci = 0;
		}

		else if (transmisja_zadanej_wartosci_temperatury) {
			USART_Transmit_string(tp2, strlen(tp2));
			transmisja_zadanej_wartosci_temperatury = 0;
		}

		else if (transmisja_zadanej_wartosci_obrotow_wentylatora) {
			USART_Transmit_string(tp3, strlen(tp3));
			transmisja_zadanej_wartosci_obrotow_wentylatora = 0;
		}

		else if (transmisja_pomiaru_temperatury) {
			USART_Transmit_string(tp4, strlen(tp4));
			transmisja_pomiaru_temperatury = 0;
		}

		else if (transmisja_pomiaru_wilgotnosci) {
			USART_Transmit_string(tp5, strlen(tp5));
			transmisja_pomiaru_wilgotnosci = 0;
		}
		else if (transmisja_stanu_przepustnic) {
					USART_Transmit_string(tp6, strlen(tp6));
					transmisja_stanu_przepustnic = 0;
				}
		else if (transmisja_nastaw_Kp) {
							USART_Transmit_string(tp7, strlen(tp7));

							transmisja_nastaw_Kp = 0;
						}
		else if (transmisja_nastaw_Ti) {

									USART_Transmit_string(tp8, strlen(tp8));
									transmisja_nastaw_Ti = 0;
								}





////////////////////////////////////////////////////////////////////////////

		if (wynik - temp_ZADANA > 300) {


			silnik_krokowy_otworz();
		}

		if (temp_ZADANA - wynik > 300) {


			silnik_krokowy_zamknij();
		}

	}
}


/*ISR(TIMER2_OVF_vect) {

	if (obsluga_LED == 1) {


		if (LED == 1) {

			g = 255;

		}
		if (LED == 0) {

			g = 0;

		}

		OCR2 = linear_brightness_curve[g];

	}

	else

	{
		if (second < 30) {
			LED = 1;
		} else {
			LED = 0;
		}

		if (LED == 1) {
			g++;
			if (g > 255) {
				g = 255;
			}
		}
		if (LED == 0) {
			g--;
			if (g < 0) {
				g = 0;
			}
		}

		OCR2 = linear_brightness_curve[g];

	}
}
*/
ISR(TIMER0_OVF_vect) {
	//reg. PI
	uchyb = wynik - temp_ZADANA;		//uchyb
	uchyb = uchyb * RKp;			    //uchyb pomnozony przez wzmocnienie
	wy = (uchyb + calka / 255);			//wezel sumacyjny

	if (wy < 0) {
		wy = 0;
	}

	else if (wy > 255) {			//ograniczenie przepelnienia zakresu
		wy = 255;
	} else
		calka = calka + (uchyb / RTi);	    //ograniczenie wind-up
											// RTi ->czas zdwojenia
	if (calka > 65535)				//ograniczenie przepelnienia zakresu
			{
		calka = 65535;
	}

	OCR1A = wy;
	if (temp_ZADANA > wynik) {
		OCR1A = 0;
	}
}

ISR(USART_RXC_vect)

{
	static unsigned char odebrana_USART;

	odebrana_USART = UDR;

	//  uart_putc(odebrana_USART);

	if (odebrana_USART == 0x20) {
		LED = 1;

	} else if (odebrana_USART == 0x21) {
		LED = 0;

	} else if (odebrana_USART == 0x22) {
		temp_ZADANA++;
	} else if (odebrana_USART == 0x23) {
		temp_ZADANA--;
	} else if (odebrana_USART == 0x24) {
		temp_ZADANA = temp_ZADANA + 500;
	} else if (odebrana_USART == 0x25) {
		temp_ZADANA = temp_ZADANA - 500;
	} else if (odebrana_USART == 0x26) {
		w_zadana++;
	} else if (odebrana_USART == 0x27) {
		w_zadana--;
	}

	else if (odebrana_USART == 0x28) {
		RKp++;
	} else if (odebrana_USART == 0x29) {
		RKp--;
	} else if (odebrana_USART == 0x30) {
		RTi++;
	} else if (odebrana_USART == 0x31) {
		RTi--;
	} else if (odebrana_USART == 0x40) {
		LED_manual = 1;

	} else if (odebrana_USART == 0x41) {
		LED_manual = 0;
	}

	else if (odebrana_USART == 'q') {
		transmisja_pomiaru_temperatury = 1;
	} else if (odebrana_USART == 'w') {
		transmisja_zadanej_wartosci_wilgotnosci = 1;
	} else if (odebrana_USART == 'e') {
		transmisja_pomiaru_wilgotnosci = 1;
	} else if (odebrana_USART == 'r') {
		transmisja_zadanej_wartosci_obrotow_wentylatora = 1;
	} else if (odebrana_USART == 't') {
		transmisja_zadanej_wartosci_temperatury = 1;
	} else if (odebrana_USART == 'y') {
		transmisja_stanu_przepustnic = 1;
	} else if (odebrana_USART == 'u') {
		transmisja_nastaw_Kp = 1;
	} else if (odebrana_USART == 'i') {
		transmisja_nastaw_Ti = 1;
	}

}

void init_io(void)	// Inicjalizacja portów
{

	//	 DDRC=(1<<PC7);								//PB0 jako wyjscie 1-wire
	DDRB |= (1 << PB0);								//PB0 jako wyjscie 1-wire

	DDRA |= (1 << PA0);								//PA0 jako wyjscie LED BT

	DDRD |= (1 << PD7);								//PD7 jako wyjscie LED pwm

	DDRD &= ~(1 << PD2); // PD2 wejscie
	PORTD |= (1 << PD2); //

	DDRB &= ~(1 << PB2); // PB2 wejscie
	PORTB |= (1 << PB2); //

	DDRB &= ~(1 << PB4); // PB4 wejscie
	PORTB |= (1 << PB4); //

	DDRB &= ~(1 << PB3); // PB3 wejscie
	PORTB |= (1 << PB3); //

	DDRB &= ~(1 << PB2); // PB2 wejscie
	PORTB |= (1 << PB2); //



	//				A1     A2
		DDRA |= (1<<PA4)|(1<<PA5);

	//				B1      B2
		DDRC |= (1<<PC4)|(1<<PC5);
}

void i2c_init(void)			//inicjalizacja magistrali I2C
{

	i2c_start();
	i2c_write(0xD0);
	i2c_write(0x0E);
	i2c_write(0x20);
	i2c_write(0x08);
	i2c_stop();
	i2c_speed(SLOW);

}

void init_PWM(void) {
	DDRD |= (1 << PD5); 	// port OC1a
	DDRD |= (1 << PD4);	// port oc1b
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1);
	TCCR1A |= (1 << WGM10);

	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS12) | (1 << CS10);
	// 	  OCR1A=ustaw_predkosc_wentylatora; //wybieranie prêdkosci wentylatora MAX255

	//OCR1B = 50; // wybieranie prêdkosci narazie pusty
	DDRD |= (1 << PD7); // LED

	//ustawienie TIMER2 w tryb fast PWM
	// TCCR2 |= (1 << WGM21) | (1 << WGM20); //tryb fast PWM
	// TCCR2 |= (1 << COM21); //clear oc2 at top
	// TCCR2 |= (1 << CS22); //prescaler=64

	//	GICR|=(1<<INT0) ;	//wybor int0
	//	GICR = (1<<IVCE); // odblokowanie INT0

	TCCR0 |= (1 << CS00);
	TCCR0 |= (1 << CS02);
	TIMSK |= (1 << TOIE0);
	TIMSK |= (1 << TOIE2);
	TCCR0 |= (0 << WGM01);
	TCCR0 |= (0 << WGM00);

}

void silnik_krokowy_otworz(void) {
	if (f_silnik_krokowy_zamknij==1)
	{
	for( int i=0;i<128;i++) //512 to chyba 360-- do weryfikacji
			{
		PORTA |= (1 << PA4);//1
		PORTA &= ~(1 << PA5);//2

		PORTC |= (1 << PC4);//3
		PORTC &= ~(1 << PC5);//4

		_delay_ms(time_krok);

		//k2
		PORTA |= (1 << PA5);//2
		PORTA &= ~(1 << PA4);//1

		PORTC |= (1 << PC4);//3
		PORTC &= ~(1 << PC5);//4

		_delay_ms(time_krok);

		//k3
		PORTA |= (1 << PA5);//2
		PORTA &= ~(1 << PA4);//1

		PORTC |= (1 << PC5);//4
		PORTC &= ~(1 << PC4);//3

		_delay_ms(time_krok);

		//k4
		PORTA |= (1 << PA4);//1
		PORTA &= ~(1 << PA5);//2

		PORTC |= (1 << PC5);//4
		PORTC &= ~(1 << PC4);//3

		_delay_ms(time_krok);
		}
	_delay_ms(20); // obowi¹zkowa przerwa dla zmiany kierunku 20 MS MIN
	f_silnik_krokowy_otworz=1;
	f_silnik_krokowy_zamknij=0;
}
}
void silnik_krokowy_zamknij(void) {
	if (f_silnik_krokowy_otworz==1)
	{
	for( int i=0;i<128;i++) //512 to chyba 360-- do weryfikacji
			{

		//k4
		PORTA |= (1 << PA4); //1
		PORTA &= ~(1 << PA5); //2

		PORTC |= (1 << PC5); //4
		PORTC &= ~(1 << PC4); //3

		_delay_ms(time_krok);
		//k3
		PORTA |= (1 << PA5); //2
		PORTA &= ~(1 << PA4); //1

		PORTC |= (1 << PC5); //4
		PORTC &= ~(1 << PC4); //3

		_delay_ms(time_krok);
		//k2
		PORTA |= (1 << PA5); //2
		PORTA &= ~(1 << PA4); //1

		PORTC |= (1 << PC4); //3
		PORTC &= ~(1 << PC5); //4

		_delay_ms(time_krok);
		PORTA |= (1 << PA4); //1
		PORTA &= ~(1 << PA5); //2

		PORTC |= (1 << PC4); //3
		PORTC &= ~(1 << PC5); //4

		_delay_ms(time_krok);
		}
	_delay_ms(20); // obowi¹zkowa przerwa dla zmiany kierunku 20 MS MIN
	f_silnik_krokowy_zamknij=1;
	f_silnik_krokowy_otworz=0;
}}
