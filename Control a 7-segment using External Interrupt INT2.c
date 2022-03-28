/*
 * Control a 7-segment using External Interrupt INT2
 *
 * Created: 12/7/2021
 * Author: sayed_shalby
 */

#include <avr/io.h>
#include <avr/interrupt.h>

/* global variable contain the 7-seg count value */
unsigned char g_num = 0;

/* External INT2 Interrupt Service Routine */
ISR(INT2_vect)
{
	// check if overflow occurs at the 7-segment as its maximum count is 9
	if((PORTC & 0x0F) == 9)
	{
		g_num = 0;
		PORTC = (PORTC & 0xF0) | (g_num & 0x0F);
	}
	else
	{
		// increment 7-segment every interrupt
		g_num++;
		PORTC = (PORTC & 0xF0) | (g_num & 0x0F);
	}
}

/* External INT2 enable and configuration function */
void INT2_Init(void)
{
	SREG   &= ~(1<<7);       // Disable interrupts by clearing I-bit
	DDRB   &= (~(1<<PB2));   // Configure INT2/PB2 as input pin
	GICR   |= (1<<INT2);	 // Enable external interrupt pin INT2
	MCUCSR |= (1<<ISC2);     // Trigger INT2 with the raising edge
	SREG   |= (1<<7);        // Enable interrupts by setting I-bit
}

int main(void)
{
	DDRC |= 0x0F; 			// Configure the first four pins in PORTC as output pins.
	PORTC &= 0xF0; 		    // 7-segment display zero at the beginning.

	INT2_Init(); 			// Enable external INT2

    while(1)
    {

	}
}
