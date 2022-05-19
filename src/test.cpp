#include <avr/io.h>
#include <util/delay.h>

int main(){
	int i = 0;
        DDRB=1<<4;
        while(1){
		if(PINB&2)
                PORTB^=1<<4;
                _delay_ms(10000);
        }

}
