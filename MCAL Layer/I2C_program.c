/*
 * I2C_program.c
 *
 * Created: 4/25/2021 11:20:35 PM
 *  Author: Laptop Market
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "I2C_interface.h"
#include "I2C_private.h"
#include "I2C_config.h"

void  MI2C_voidAvrIntialization(void)
{      
		TWAR = I2C_ADRESS<<1;
		TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	    while (!(GET_BIT(TWCR,TWINT)));	 
}

u32  MI2C_voidAvrState(u32 Timeout)
{
	u8 State ;
	while(Timeout--){
	while(!GET_BIT(TWCR,TWINT));
	State = TWSR & 0xF8;
	if (State==0x60 || State == 0x68)
		return I2C_READ;
	else if (State==0xA8 || State == 0xB0)
		return I2C_WRITE;
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	}
	if (Timeout == 0)
		return 255;
	return 255;
	//return 255;
	/*while(1)
	{
	State= (TWSR & 0xF8);
	if (State==0x60)
		return READ; 
	else if (State==0xA8) 
		return WRITE;
	else 
	{
		TWCR = (1<<TWINT);//|(1<<TWEN);
		return 255;
	}
	}*/
}

u8  MI2C_voidAvrSlaveWrite(char Data)
{   
	TWDR = Data;
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
    while (!(GET_BIT(TWCR,TWINT)));
	u8 State= (TWSR & 0xF8);
	if (State == 0xB8)
	{
		return I2C_WRITE_DONE;
	}
	else if (State==0xA0)
	{
		SET_BIT(TWCR,TWINT);
		return I2C_WRITE_STOP_CONDITION ;
	}
	else 
		return I2C_WRITE_ERROR;
}

char  MI2C_u8AvrSlaveRead(void)
{ 
	
	char Data ;
	TWCR |= (1<<TWINT)|(1<<TWEN)|(1<<TWEA); 
	while (!(GET_BIT(TWCR,TWINT)));
	u8 State= (TWSR & 0xF8);
	//SET_BIT(TWCR,TWEA);
	//Data =	TWDR ;
	//TWCR |= (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	if ( State == 0x80 || State == 0x88 || State == 0x90 || State == 0x98) 
		return TWDR ;
	else if (State==0xA0)
	{
		SET_BIT(TWCR,TWINT);
		return I2C_READ_STOP_CONDITION ;	
	}
	else
		return I2C_READ_ERROR;
}
