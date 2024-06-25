/*
 * I2C_interface.h
 *
 * Created: 4/25/2021 11:18:08 PM
 *  Author: Laptop Market
 */ 


#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

#define I2C_WRITE						0
#define I2C_READ						3
#define I2C_WRITE_STOP_CONDITION		1
#define I2C_READ_STOP_CONDITION			1
#define I2C_WRITE_ERROR					-1
#define I2C_READ_ERROR					-1
#define I2C_WRITE_DONE					2


void	MI2C_voidAvrIntialization	(void);
u32		MI2C_voidAvrState			(u32 Timeout);
u8		MI2C_voidAvrSlaveWrite		(char Data);
char	MI2C_u8AvrSlaveRead			(void);




#endif /* I2C_INTERFACE_H_ */
