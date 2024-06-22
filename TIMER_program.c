/*
 * TIMER_program.c
 *
 * Created: 4/10/2021 11:55:37 AM
 *  Author: Laptop Market
 */ 


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <string.h>
#include <avr/io.h>
#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_config.h"
#include <avr/interrupt.h>
u16 DutyCycle;

void  MTIMER_voidInit(u8 Mode , u8 n , u8 ModeOption,u8 Prescalar_shift)
{
	
	u16 frequency = 1 ; // 400 Hz
	//freq = 244 Hz at sys clk 16 MHz & prescalar 256 or sys clk 4 MHz & prescalar 64 in fast pwm
	// freq = 245 Hz at sys clk 8 MHz & prescalar 64 or sys clk 1 MHz & prescalar 8 in phase correct
	u16 Precalar ;
	u16 OverflowTime;
	switch (Prescalar_shift)
	{
		case NO_PRESCALAR :
		Precalar =1;
		break;
		case _8_PRESCALAR :
		Precalar =8;
		break;
		case _64_PRESCALAR :
		Precalar =64;
		break;
		case _256_PRESCALAR :
		Precalar =256;
		break;
		case _1024_PRESCALAR :
		Precalar =1024;
		break;
		default:
		Precalar = 1;
	}
	
	if (n==TIMER0)
	{
		OverflowTime=TIME_COUNT*TIMER_TICK_TIME;

		if (Mode==FAST_PWM_MODE)
		{
			TCCR0A = ((1<<WGM00)|(1<<WGM01));
			CLR_BIT(TCCR0B,WGM02);
			frequency= SYSTEM_CLOCK / (Precalar * 256);
		}
		else if ( Mode ==PHASE_CORRECT_PWM_MODE)
		{
			SET_BIT(TCCR0B,WGM02);
			CLR_BIT (TCCR0A,WGM01);
			SET_BIT (TCCR0A,WGM00);
			frequency= SYSTEM_CLOCK / (Precalar * 510);
		}
		TCCR0A &= ~(3<<COM0A0 | 3<<COM0B0); 
		TCCR0B &= ~(7);                    
		TCCR0A|= (ModeOption<< COM0A0);
		TCCR0A|= (ModeOption<< COM0B0);
		TCCR0B |= Prescalar_shift;
		
	}
	else if (n==TIMER1)
	{
		OverflowTime=TIME_COUNT*TIMER_TICK_TIME;

		if (Mode==FAST_PWM_MODE)
		{
			SET_BIT (TCCR1A,WGM10);
			CLR_BIT (TCCR1A,WGM11);
			SET_BIT (TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);
			frequency= SYSTEM_CLOCK / (Precalar * 256);
		}
		else if ( Mode ==PHASE_CORRECT_PWM_MODE)
		{
			SET_BIT (TCCR1A,WGM10);
			CLR_BIT (TCCR1A,WGM11);
			CLR_BIT(TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);
			frequency= SYSTEM_CLOCK / (Precalar * 510);
		}
		TCCR1A &= ~(3<<COM1A0 | 3<<COM1B0);
		TCCR1B &= ~(7);
		TCCR1A|= (ModeOption<< COM1A0);
		TCCR1A|= ( ModeOption<< COM1B0);
		TCCR1B |= (Prescalar_shift);
	}
	else if (n==TIMER2)
	{
		OverflowTime=TIME_COUNT*TIMER_TICK_TIME;
		if (Mode==FAST_PWM_MODE)
		{
			TCCR2A= ((1<<WGM20)|(1<<WGM21));
			CLR_BIT (TCCR2B,WGM22);
			frequency= SYSTEM_CLOCK / (Precalar * 256);
		}
		else if ( Mode ==PHASE_CORRECT_PWM_MODE)
		{
			SET_BIT(TCCR2B,WGM22);
			CLR_BIT (TCCR2A,WGM21);
			SET_BIT (TCCR2A,WGM20);
			frequency= SYSTEM_CLOCK / (Precalar * 510);
		}
		TCCR2A &= ~(3<<COM2A0 | 3<<COM2B0);
		TCCR2B &= ~(7);
		TCCR2A|= (ModeOption<< COM2A0);
		TCCR2A|= (ModeOption<< COM2B0);
		TCCR2B|= Prescalar_shift+1;
	}
	
	TIMER_TICK_TIME = 1.0/(float)frequency;
}

void  MTIMERn_voidSetDutyCycle(u8 Duty, u8 n,u8 Channel)
{
	
	if (Duty > 255 )
	Duty = 255;
	DutyCycle= Duty;//*OVERFLOW)/100;
	if (n==TIMER0)
	{   switch(Channel)
		{
			case CHANNELA :
			OCR0A = DutyCycle;
			break;
			case CHANNELB :
			OCR0B = DutyCycle;
			break;
		}
	}
	if (n==TIMER1)
	{   switch(Channel)
		{
			case CHANNELA :
			OCR1AL = DutyCycle;
			OCR1AH = 0;
			break;
			case CHANNELB :
			OCR1BL = DutyCycle;
			OCR1BH = 0;
			break;
		}
	}
	if (n==TIMER2)
	{   switch(Channel)
		{
			case CHANNELA :
			OCR2A = DutyCycle;
			break;
			case CHANNELB :
			OCR2B = DutyCycle;
			break;
		}
	}
}
