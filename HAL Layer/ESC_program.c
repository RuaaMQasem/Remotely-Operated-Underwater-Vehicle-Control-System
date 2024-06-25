/*
 * ESC_program.c
 *
 * Created: 4/10/2021 11:57:32 AM
 *  Author: Laptop Market
 */ 
#define F_CPU		8000000UL

#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "GPIO_interface.h"
#include "ESC_interface.h"
#include "ESC_private.h"
#include "ESC_config.h"

//#include "UART_interface.h"

float Freq = 491;

void HESC_voidInit(esc * ptr_esc , u8 Delay )
{
	MTIMER_voidInit(MODE_ESC , ptr_esc->timer ,MODE_OPTION_ESC , PRESCALER_ESC );
	float duty_cycle =187;//0.15*61;  // f244 ->36  , f488 -> 73 
	MGPIO_voidSetPinDirection(ptr_esc->port , ptr_esc->pin, GPIO_OUTPUT);
	
	//UART_voidSendNumber(TIMER_TICK_TIME);
	//UART_voidPrintNewLine();
	//UART_voidSendNumber((u8)duty_cycle);
	
	MTIMERn_voidSetDutyCycle( (u8)duty_cycle ,ptr_esc->timer ,ptr_esc->channel);
	if (Delay)
	_delay_ms(3000);
}


void HESC_voidSetMotorSpeed(char speed , esc * ptr_esc)
{   float esc_speed = ((4 * speed) + 1500) ;
	float duty_cycle = ((float)esc_speed *Freq*255)/1000000 ;
	MTIMERn_voidSetDutyCycle( duty_cycle , ptr_esc->timer ,ptr_esc->channel);
}
