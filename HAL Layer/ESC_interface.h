/*
 * ESC_interface.h
 *
 * Created: 4/10/2021 11:58:50 AM
 *  Author: Laptop Market
 */ 


#ifndef ESC_INTERFACE_H_
#define ESC_INTERFACE_H_


typedef struct
{   u8 channel ;
	u8 timer ;
	u8 port ;
	u8 pin ;
//	u8 feedback_speed ;
}esc;



void HESC_voidInit(esc * ptr_esc , u8 Delay );
void HESC_voidSetMotorSpeed(char speed , esc * ptr_esc );

#endif /* ESC_INTERFACE_H_ */
