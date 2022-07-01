/*
 * lcd.c
 *
 *  Created on: 22 gru 2020
 *      Author: Lenovo
 */

#include "lcd.h"

//obsluga przycisków
void przyciski_MENU(HD44780* lcd) {

	lcd_update(lcd, 1, 0, "^  v  OK", 8); //wpisanie do tablicy na dolny panel wyswietlacza
	if (Plus_przycisk) {
		_delay_ms(50); //eliminacja drgan styków
		while (Plus_przycisk) {
		}
		_delay_ms(50); //eliminacja drgan styków
		a++;
		if (a > 4)
			a = 1;
		lcd_clear(lcd);
	}
	//przycisk w lewo
	else if (Minus_przycisk) {
		_delay_ms(50); //eliminacja drgan styków
		while (Minus_przycisk) {
		}
		_delay_ms(50); //eliminacja drgan styków
		a--;

		if (a < 1)
			a = 4;
		lcd_clear(lcd);
	}
	//przycisk akceptacji
	else if (OK_LCD) {
		_delay_ms(50);
		while (OK_LCD) {
		}
		_delay_ms(50);
		a = a * 10;
		lcd_clear(lcd);
	}
}

void przyciski_PODMENU(HD44780* lcd) {

	lcd_update(lcd, 1, 0, "^  v  OK COFNIJ", 15); //wpisanie do tablicy na dolny panel wyswietlacza
	//przycisk akceptacji
	if (OK_LCD) {
		_delay_ms(50);
		while (OK_LCD) {
		}
		_delay_ms(50);
		a = a * 10;
		lcd_clear(lcd);
	} else if (Cofnij_LCD) {
		_delay_ms(50);
		while (Cofnij_LCD) {
		}
		_delay_ms(50);
		a = a / 10;
		lcd_clear(lcd);
	}

}

void przyciski_NASTAW(HD44780* lcd) {

	lcd_update(lcd, 1, 0, "+  -  OK COFNIJ", 15); //wpisanie do tablicy na dolny panel wyswietlacza
	//przycisk akceptacji

	if (Cofnij_LCD) {
		_delay_ms(50);
		while (Cofnij_LCD) {
		}
		_delay_ms(50);
		a = a / 10;
		lcd_clear(lcd);
	}
}

void LCD_menu(HD44780 *lcd)

{

	//przycisk w prawo

	//Menu
	switch (a) {
	case MENU_TEMPERATURY:

		lcd_update(lcd, 0, 0, "Temperatura", 11); //wpisanie do tablicy na górny panel wyswietlacza
		przyciski_MENU(lcd);
		lcd_refresh(lcd);

		break;

	case MENU_TEMPERATURY_WYSWIETL:

		sprintf(LCD_tab, "Biezaca=%d.%2d C ", wynik / 100, abs(wynik % 100)); //tworzenie zmiennej do wyswietlania temperatury
		lcd_update(lcd, 0, 0, LCD_tab, strlen(LCD_tab)); //wpisanie do tablicy na górny panel wyswietlacza
		przyciski_PODMENU(lcd);
		lcd_refresh(lcd);
		_delay_ms(20);
		if (Plus_przycisk) {
			_delay_ms(50); //eliminacja drgan styków
			while (Plus_przycisk) {
			}
			_delay_ms(50); //eliminacja drgan styków
			a++;
			if (a > 12)
				a = 10;
			lcd_clear(lcd);
		}
		//przycisk w lewo
		else if (Minus_przycisk) {
			_delay_ms(50); //eliminacja drgan styków
			while (Minus_przycisk) {
			}
			_delay_ms(50); //eliminacja drgan styków
			a--;

			if (a < 10)
				a = 12;
			lcd_clear(lcd);
		}

		break;
	case MENU_TEMPERATURY_CZUJNIK1:

		sprintf(LCD_tab, "Czujnik_1=%d.%2d C ", czujnik_1 / 100,
				abs(czujnik_1 % 100)); //tworzenie zmiennej do wyswietlania temperatury
		lcd_update(lcd, 0, 0, LCD_tab, strlen(LCD_tab)); //wpisanie do tablicy na górny panel wyswietlacza
		przyciski_PODMENU(lcd);
		lcd_refresh(lcd);
		_delay_ms(20);
		if (Plus_przycisk) {
			_delay_ms(50); //eliminacja drgan styków
			while (Plus_przycisk) {
			}
			_delay_ms(50); //eliminacja drgan styków
			a++;
			if (a > 12)
				a = 10;
			lcd_clear(lcd);
		}
		//przycisk w lewo
		else if (Minus_przycisk) {
			_delay_ms(50); //eliminacja drgan styków
			while (Minus_przycisk) {
			}
			_delay_ms(50); //eliminacja drgan styków
			a--;

			if (a < 10)
				a = 12;
			lcd_clear(lcd);
		}

		break;
	case MENU_TEMPERATURY_CZUJNIK2:

		sprintf(LCD_tab, "Czujnik_2=%d.%2d C ", czujnik_2 / 100,abs(czujnik_2 % 100)); //tworzenie zmiennej do wyswietlania temperatury
		lcd_update(lcd, 0, 0, LCD_tab, strlen(LCD_tab)); //wpisanie do tablicy na górny panel wyswietlacza
		przyciski_PODMENU(lcd);
		lcd_refresh(lcd);
		_delay_ms(20);
		if (Plus_przycisk) {
			_delay_ms(50); //eliminacja drgan styków
			while (Plus_przycisk) {
			}
			_delay_ms(50); //eliminacja drgan styków
			a++;
			if (a > 12)
				a = 10;
			lcd_clear(lcd);
		}
		//przycisk w lewo
		else if (Minus_przycisk) {
			_delay_ms(50); //eliminacja drgan styków
			while (Minus_przycisk) {
			}
			_delay_ms(50); //eliminacja drgan styków
			a--;

			if (a < 10)
				a = 12;
			lcd_clear(lcd);
		}

		break;
	case MENU_TEMPERATURY_NASTAWA:

		sprintf(LCD_tab, "Zadana=%d.%2d C ", temp_ZADANA / 100,
				abs(temp_ZADANA % 100)); //tworzenie zmiennej do wyswietlania temperatury
		lcd_update(lcd, 0, 0, LCD_tab, strlen(LCD_tab));
		przyciski_NASTAW(lcd);
		lcd_refresh(lcd);
		_delay_ms(20);

		if (Plus_przycisk) {
			temp_ZADANA = temp_ZADANA + 50;
		}
		if (Minus_przycisk) {
			temp_ZADANA = temp_ZADANA - 50;
		}

		break;
	case MENU_WILGOTNOSCI:

		lcd_update(lcd, 0, 0, "Wilgotnosc", 10); //wpisanie do tablicy na górny panel wyswietlacza
		przyciski_MENU(lcd);
		lcd_refresh(lcd);

		break;
	case MENU_WILGOTNOSCI_WYSWIETL:

		sprintf(LCD_tab, "Biezaca=15 %% ", w_aktualna); // %d powinno byc zamiast 15
		lcd_update(lcd, 0, 0, LCD_tab, strlen(LCD_tab)); //wpisanie do tablicy na górny panel wyswietlacza
		przyciski_PODMENU(lcd);
		lcd_refresh(lcd);
		_delay_ms(20);

		break;
	case MENU_WILGOTNOSCI_NASTAWA:

		sprintf(LCD_tab, "Zadana=%d %% ", w_zadana / 100);
		lcd_update(lcd, 0, 0, LCD_tab, strlen(LCD_tab));
		przyciski_NASTAW(lcd);
		lcd_refresh(lcd);
		_delay_ms(20);

		if (Plus_przycisk) {
			w_zadana = w_zadana + 100;
		}
		if (Minus_przycisk) {
			w_zadana = w_zadana - 100;
		}

		break;
	case MENU_WENTYLACJA:

		lcd_update(lcd, 0, 0, "Wentylacja", 10); //wpisanie do tablicy na górny panel wyswietlacza
		przyciski_MENU(lcd);
		lcd_refresh(lcd);

		break;
	case MENU_WENTYLACJA_WENTYLATOR:

		sprintf(LCD_tab, "Obroty_w=%d %%", predkosc_wentylatora);
		lcd_update(lcd, 0, 0, LCD_tab, strlen(LCD_tab)); //wpisanie do tablicy na górny panel wyswietlacza
		przyciski_PODMENU(lcd);
		lcd_refresh(lcd);
		if (Plus_przycisk) {
			_delay_ms(50); //eliminacja drgan styków
			while (Plus_przycisk) {
			}
			_delay_ms(50); //eliminacja drgan styków
			a++;
			if (a > 31)
				a = 30;
			lcd_clear(lcd);
		}
		//przycisk w lewo
		else if (Minus_przycisk) {
			_delay_ms(50); //eliminacja drgan styków
			while (Minus_przycisk) {
			}
			_delay_ms(50); //eliminacja drgan styków
			a--;

			if (a < 30)
				a = 31;
			lcd_clear(lcd);
		}
		_delay_ms(20);
		break;
	case MENU_WENTYLACJA_PRZEPUSTNICA:

		sprintf(LCD_tab, "Przepustnica: %d",f_silnik_krokowy_otworz);
		lcd_update(lcd, 0, 0, LCD_tab, strlen(LCD_tab)); //wpisanie do tablicy na górny panel wyswietlacza
		przyciski_PODMENU(lcd);
		lcd_refresh(lcd);
		_delay_ms(20);

		if (Plus_przycisk) {
			_delay_ms(50); //eliminacja drgan styków
			while (Plus_przycisk) {
			}
			_delay_ms(50); //eliminacja drgan styków
			a++;
			if (a > 31)
				a = 30;
			lcd_clear(lcd);
		}
		//przycisk w lewo
		else if (Minus_przycisk) {
			_delay_ms(50); //eliminacja drgan styków
			while (Minus_przycisk) {
			}
			_delay_ms(50); //eliminacja drgan styków
			a--;

			if (a < 30)
				a = 31;

			break;

			case MENU_CZAS:

			lcd_update(lcd, 0, 0, "Czas", 4); //wpisanie do tablicy na górny panel wyswietlacza
			przyciski_MENU(lcd);
			lcd_refresh(lcd);

			break;

			case MENU_CZAS_WYSWIETL:

			sprintf(LCD_tab, "Czas=%2d:%2d:%2d", hour, minute, second);
			lcd_update(lcd, 0, 0, LCD_tab, strlen(LCD_tab)); //wpisanie do tablicy na górny panel wyswietlacza
			przyciski_PODMENU(lcd);
			lcd_refresh(lcd);
			_delay_ms(20);
			if (Plus_przycisk) {
				_delay_ms(50); //eliminacja drgan styków
				while (Plus_przycisk) {
				}
				_delay_ms(50); //eliminacja drgan styków
				a++;
				if (a > 41)
					a = 40;
				lcd_clear(lcd);
			}
			//przycisk w lewo
			else if (Minus_przycisk) {
				_delay_ms(50); //eliminacja drgan styków
				while (Minus_przycisk) {
				}
				_delay_ms(50); //eliminacja drgan styków
				a--;

				if (a < 40)
					a = 41;

				break;

				case MENU_CZAS_WYSWIETL_DATE:

				sprintf(LCD_tab, "Data=%2d:%2d:%2d", dayOfMonth, month, year);
				lcd_update(lcd, 0, 0, LCD_tab, strlen(LCD_tab)); //wpisanie do tablicy na górny panel wyswietlacza
				przyciski_PODMENU(lcd);
				lcd_refresh(lcd);
				_delay_ms(20);
				if (Plus_przycisk) {
					_delay_ms(50); //eliminacja drgan styków
					while (Plus_przycisk) {
					}
					_delay_ms(50); //eliminacja drgan styków
					a++;
					if (a > 41)
						a = 40;
					lcd_clear(lcd);
				}
				//przycisk w lewo
				else if (Minus_przycisk) {
					_delay_ms(50); //eliminacja drgan styków
					while (Minus_przycisk) {
					}
					_delay_ms(50); //eliminacja drgan styków
					a--;

					if (a < 40)
						a = 41;

					break;

					case MENU_CZAS_NASTAWA_SEKUND:
					sprintf(LCD_tab, "Sekunda:%2d", second);
					lcd_update(lcd, 0, 0, LCD_tab, strlen(LCD_tab)); //wpisanie do tablicy na górny panel wyswietlacza
					lcd_update(lcd, 1, 0, "+  -  OK COFNIJ", 15); //wpisanie do tablicy na dolny panel wyswietlacza
					lcd_refresh(lcd);
					_delay_ms(20);
					if (Plus_przycisk) {
						second++;
					}
					if (Minus_przycisk) {
						second--;
					}
					if (OK_LCD) {
						a = a + 100;
						if (a == 1000)
							a = 400;
						lcd_clear(lcd);
					} else if (Cofnij_LCD) {
						_delay_ms(50);
						while (Cofnij_LCD) {
						}
						_delay_ms(50);
						a = a / 10;
						lcd_clear(lcd);
					}

					break;
					case MENU_CZAS_NASTAWA_MINUT:

					sprintf(LCD_tab, "Minuta:%2d", minute);
					lcd_update(lcd, 0, 0, LCD_tab, strlen(LCD_tab)); //wpisanie do tablicy na górny panel wyswietlacza
					lcd_update(lcd, 1, 0, "+  -  OK COFNIJ", 15); //wpisanie do tablicy na dolny panel wyswietlacza
					lcd_refresh(lcd);
					_delay_ms(20);
					if (Plus_przycisk) {
						minute++;
					}
					if (Minus_przycisk) {
						minute--;
					}
					if (OK_LCD) {
						a = a + 100;
						if (a == 1000)
							a = 400;
						lcd_clear(lcd);
					} else if (Cofnij_LCD) {
						_delay_ms(50);
						while (Cofnij_LCD) {
						}
						_delay_ms(50);
						a = a / 10;
						lcd_clear(lcd);
					}
					break;
					case MENU_CZAS_NASTAWA_GODZIN:

					sprintf(LCD_tab, "Godzina:%2d", hour);
					lcd_update(lcd, 0, 0, LCD_tab, strlen(LCD_tab)); //wpisanie do tablicy na górny panel wyswietlacza
					lcd_update(lcd, 1, 0, "+  -  OK COFNIJ", 15); //wpisanie do tablicy na dolny panel wyswietlacza
					lcd_refresh(lcd);
					_delay_ms(20);
					if (Plus_przycisk) {
						hour++;
					} else if (Minus_przycisk) {
						hour--;
					} else if (OK_LCD) {
						a = a + 100;
						if (a == 1000)
							a = 400;
						lcd_clear(lcd);
					} else if (Cofnij_LCD) {
						_delay_ms(50);
						while (Cofnij_LCD) {
						}
						_delay_ms(50);
						a = a / 10;
						lcd_clear(lcd);

					}
					break;
					case MENU_CZAS_NASTAWA_DNIA:

					sprintf(LCD_tab, "Dzien:%2d", dayOfMonth);
					lcd_update(lcd, 0, 0, LCD_tab, strlen(LCD_tab)); //wpisanie do tablicy na górny panel wyswietlacza
					lcd_update(lcd, 1, 0, "+  -  OK COFNIJ", 15); //wpisanie do tablicy na dolny panel wyswietlacza
					lcd_refresh(lcd);
					_delay_ms(20);
					if (Plus_przycisk) {
						dayOfMonth++;
					} else if (Minus_przycisk) {
						dayOfMonth--;
					} else if (OK_LCD) {
						a = a + 100;
						if (a == 1000)
							a = 400;
						lcd_clear(lcd);
					} else if (Cofnij_LCD) {
						_delay_ms(50);
						while (Cofnij_LCD) {
						}
						_delay_ms(50);
						a = a / 10;
						lcd_clear(lcd);
					}

					break;

					case MENU_CZAS_NASTAWA_MIESIACA:

					sprintf(LCD_tab, "Miesiac:%2d", month);
					lcd_update(lcd, 0, 0, LCD_tab, strlen(LCD_tab)); //wpisanie do tablicy na górny panel wyswietlacza
					lcd_update(lcd, 1, 0, "+  -  OK COFNIJ", 15); //wpisanie do tablicy na dolny panel wyswietlacza
					lcd_refresh(lcd);
					_delay_ms(20);
					if (Plus_przycisk) {
						month++;
					} else if (Minus_przycisk) {
						month--;
					} else if (OK_LCD) {
						a = a + 100;
						if (a == 1000)
							a = 400;
						lcd_clear(lcd);
					} else if (Cofnij_LCD) {
						_delay_ms(50);
						while (Cofnij_LCD) {
						}
						_delay_ms(50);
						a = a / 10;
						lcd_clear(lcd);

					}
					break;
					case MENU_CZAS_NASTAWA_LAT:

					sprintf(LCD_tab, "Rok:%2d", year);
					lcd_update(lcd, 0, 0, LCD_tab, strlen(LCD_tab)); //wpisanie do tablicy na górny panel wyswietlacza
					lcd_update(lcd, 1, 0, "+  -  OK COFNIJ", 15); //wpisanie do tablicy na dolny panel wyswietlacza
					lcd_refresh(lcd);
					_delay_ms(20);
					if (Plus_przycisk) {
						year++;
					} else if (Minus_przycisk) {
						year--;
					} else if (OK_LCD) {
						a = a + 100;
						if (a == 1000)
							a = 400;
						lcd_clear(lcd);
					} else if (Cofnij_LCD) {
						_delay_ms(50);
						while (Cofnij_LCD) {
						}
						_delay_ms(50);
						a = a / 10;
						lcd_clear(lcd);
					}
					break;
					default:
					break;
				}
			}
		}
	}
}
