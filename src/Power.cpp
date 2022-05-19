#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/io.h>
#include <util/delay.h>

const int relay = PB4;
const int optocoupler = PB1;
const int piIn = PB2;
const int piOut = PB3;


EMPTY_INTERRUPT(BADISR_vect);

void sleep(){
	GIMSK |= _BV(PCIE);
	PCMSK |= _BV(PCINT1);
	ADCSRA &= ~_BV(ADEN);
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sei();
	sleep_cpu();
	cli();
	sleep_disable();
}
int main(){
	int iter = 0;
	int iter2 = 0;
	DDRB = _BV(piOut)|_BV(relay);
	_delay_ms(500);
//	PORTB |= _BV(optocoupler);
//	for(iter=0;iter<5;iter++){
//	PORTB |= _BV(relay);
//	_delay_ms(200);
//	PORTB &= ~_BV(relay);}
	iter = 0;
	while(1){
		while(iter <= 254){
			if(PINB&_BV(optocoupler)){
				iter -= 30;
				sleep();
			}
			_delay_ms(13);
			iter++;
		} //Sleep until optocoupler is low consistently for 200ms
		iter = 0;

		PORTB |= _BV(piOut) | _BV(relay); //Turn on everything

		while(iter <= 254){
			if((PINB&_BV(optocoupler)) == 0){
				iter = 0;
			}
			_delay_ms(20);
			iter++;
			
		} //Sleep until optocoupler is high consistently for 200ms
		iter = 0;
		//Start shutdown
		PORTB &= ~_BV(piOut); //Signal pi to shutdown

		iter2 = 0;
		while(iter <=40 && iter2 <=7500){
			if((PINB&_BV(piIn)) == 0){
				iter = 0;
			}
			_delay_ms(2);
			iter++;
			iter2++;
			
		} //Sleep until piIn is low consistently for 200ms
		iter = 0;
		PORTB &= ~_BV(relay); //Kill power
		_delay_ms(1000);
	}
	return(0);
}
