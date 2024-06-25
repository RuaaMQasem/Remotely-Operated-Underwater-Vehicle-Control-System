/*
 * GPIO_interface.h
 *
 * Created: 4/10/2021 11:47:09 AM
 *  Author: Laptop Market
 */ 


#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_


#define GPIO_PORTB		0
#define GPIO_PORTC		1
#define GPIO_PORTD		2


#define GPIO_INPUT			0
#define GPIO_OUTPUT			1
#define GPIO_INPUT_PULLUP	2

#define GPIO_LOW			0
#define GPIO_HIGH			1



void MGPIO_voidSetPinDirection(u8 Copy_u8PortNumber,u8 Copy_u8PinNumber, u8 Copy_u8Direction);
void MGPIO_voidSetPortDirection(u8 Copy_u8PortNumber, u8 Copy_u8Direction);
void MGPIO_voidSetPinValue(u8 Copy_u8PortNumber,u8 Copy_u8PinNumber, u8 Copy_u8Value);
void MGPIO_voidSetPortValue(u8 Copy_u8PortNumber,u8 Copy_u8Value);
void MGPIO_voidSetPin(u8 Copy_u8PortNumber,u8 Copy_u8PinNumber);
void MGPIO_voidClearPin(u8 Copy_u8PortNumber,u8 Copy_u8PinNumber);
u8 MGPIO_u8GetPinValue(u8 Copy_u8PortNumber,u8 Copy_u8PinNumber);





#endif /* GPIO_INTERFACE_H_ */
