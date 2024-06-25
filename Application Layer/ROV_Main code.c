/*
 * ROV_Main code.c
 *
 * Created: 4/10/2021 11:42:34 AM
 * Author : Laptop Market
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/io.h>
#include "GPIO_interface.h"
#include "TIMER_interface.h"
#include "I2C_interface.h"
#include "ESC_interface.h"
#include "UART_interface.h"

#define F_CPU	8000000UL
#include <util/delay.h>

#define ROV_MOV_RIGHT				'R'
#define ROV_MOV_LEFT				'L'
#define ROV_MOV_FORWARD				'F'
#define ROV_MOV_BACKWORD			'B'
#define ROV_MOV_UP					'U'
#define ROV_MOV_DOWN				'D'
#define ROV_MOV_ROT_RIGHT			'X'
#define ROV_MOV_ROT_LEFT			'Y'
#define ROV_AUTO        			'A' 
#define NO_DATA_RECIEVED             0
#define DONE_RECIEVING               1
#define ERROR_IN_DATA                2


void Moveforward (char speed , esc* ptr_array );
void MoveBackward (char speed , esc* ptr_array );
void MoveUpward (char speed , esc* ptr_array );
void MoveDownward (char speed , esc* ptr_array );
void MoveRight (char speed , esc* ptr_array );
void Moveleft (char speed , esc* ptr_array );
void RotateRight (char speed , esc* ptr_array );
void RotateLeft (char speed , esc* ptr_array );
u8 ParseRecieved(char* speed, char* direction, char* array);
void MoveAutonomous (char* array , esc* ptr_array); 


int main(void){
	
	// timer test fast pwm
	 //DDRD |= (1<<6) | (1<<3) |(1<<5);
	// DDRB |= (1<<1) | (1<<2) | (1<<3);
	//DDRD |= (1<<6);
  //MTIMER_voidInit( FAST_PWM_MODE, TIMER0 , NON_INVERTING,_8_PRESCALAR);
	//duty cycle is a  percentage 0=>100
	//MTIMERn_voidSetDutyCycle(20 , TIMER0,CHANNELA);  
	//esc test fast pwm
	
	 esc ESC [6] ;
   ESC[0].port = GPIO_PORTD ;
   ESC[0].pin = 6 ;
   ESC[0].timer = TIMER0 ;
   ESC[0].channel = CHANNELA ;
   
 
   /////////////////////////////////////
   ESC[1].port = GPIO_PORTD ;
   ESC[1].pin = 5 ;
   ESC[1].timer = TIMER0 ;
   ESC[1].channel = CHANNELB ;
   //////////////////////////////////////
   ESC[2].port = GPIO_PORTB ;
   ESC[2].pin = 1 ;
   ESC[2].timer = TIMER1 ;
   ESC[2].channel = CHANNELA ;
   //////////////////////////////////////
   ESC[3].port = GPIO_PORTB ;
   ESC[3].pin = 2 ;
   ESC[3].timer = TIMER1 ;
   ESC[3].channel = CHANNELB ;
   //////////////////////////////////////
   ESC[4].port = GPIO_PORTB ;
   ESC[4].pin = 3 ;
   ESC[4].timer = TIMER2 ;
   ESC[4].channel = CHANNELA ;
   //////////////////////////////////////
   ESC[5].port = GPIO_PORTD ;
   ESC[5].pin = 3 ;
   ESC[5].timer = TIMER2 ;
   ESC[5].channel = CHANNELB ;
   
	for (int i =0 ; i < 6 ; i++)
	{   u8 delay = 0 ;
		if (i == 5)
		{
			delay = 1 ;
		}
		HESC_voidInit( ESC + i , delay );
		
	}
	//_delay_ms(5000);
	//HESC_voidSetMotorSpeed( 15 , ESC+5 );
	MoveUpward ( 15 , ESC );
	_delay_ms(3000);
	HESC_voidSetMotorSpeed( 0 , ESC+5 );
	while(1){
		
	}
	
	return 0;
}


/*
int main(void){
	// I2C PINS
	MGPIO_voidSetPinDirection(GPIO_PORTC , 4 , GPIO_OUTPUT); // SDA
	MGPIO_voidSetPinDirection(GPIO_PORTC , 5 , GPIO_OUTPUT); // SCL
    //MI2C_voidAvrIntialization	();
	//u8 State;
	//char ReadData;
	u8 counter = 0 ;
	//char ReadData[5]= {-1,-1,-1,-1,-1};
	MUART_voidUartIntialization(FULL_dUPLEX,ASYNCHRONOUS_MODE,UART_8BIT,0,1);

	//void MUART_voidReadString(arr, 12,15);
	char A = 'a';
	MUART_voidTransmitString("Hello Rovers\n");

	while(1){
				MUART_voidTransmitString("Hello Rovers\n");
				_delay_ms(1000);
				/*
		    State = MI2C_voidAvrState(255);
		    if(State == I2C_WRITE){
			    MI2C_voidAvrSlaveWrite(OCR0A);

		    }
		    else if (State == I2C_READ){
			   // ReadData[counter] = MI2C_u8AvrSlaveRead ();
			   ReadData=MI2C_u8AvrSlaveRead ();
		   // counter++;
		   }
		    
		    else if (State == I2C_READ_STOP_CONDITION){
			   // counter= 0;
			    // for (int i=0 ; i<5 ; i++)
				  //  { ReadData[i] = -1;}
			                                        }
	
	}
	
	return 0;
}

*/

/*
int main(void)
{    esc ESC [6] ;
   //                 ESC[0] - > PIN 12        ESC[1] - > PIN 11                   
  //                  ESC[2] - > PIN 15        ESC[3] - > PIN 16 

 // vertical          ESC[4] - > PIN 17        ESC[5] - > PIN 05
   ESC[0].port = GPIO_PORTD ;
   ESC[0].pin = 6 ;
   ESC[0].timer = TIMER0 ;
   ESC[0].channel = CHANNELA ;
/////////////////////////////////////
   ESC[1].port = GPIO_PORTD ;
   ESC[1].pin = 5 ;
   ESC[1].timer = TIMER0 ;
   ESC[1].channel = CHANNELB ;
//////////////////////////////////////   
   ESC[2].port = GPIO_PORTB ;
   ESC[2].pin = 1 ;
   ESC[2].timer = TIMER1 ;
   ESC[2].channel = CHANNELA ;
//////////////////////////////////////
   ESC[3].port = GPIO_PORTB ;
   ESC[3].pin = 2 ;
   ESC[3].timer = TIMER1 ;
   ESC[3].channel = CHANNELB ; 
//////////////////////////////////////
   ESC[4].port = GPIO_PORTB ;
   ESC[4].pin = 3 ;
   ESC[4].timer = TIMER2 ;
   ESC[4].channel = CHANNELA ;
//////////////////////////////////////
   ESC[5].port = GPIO_PORTD ;
   ESC[5].pin = 3 ;
   ESC[5].timer = TIMER2 ;
   ESC[5].channel = CHANNELB ;
///////////////////////////////////////////////////////////////////////////////////////////////////
// I2C PINS
MGPIO_voidSetPinDirection(GPIO_PORTC , 4 , GPIO_OUTPUT); // SDA
MGPIO_voidSetPinDirection(GPIO_PORTC , 5 , GPIO_OUTPUT); // SCL
///////////////////////////////////////////////////////////////////////////////////////////////////
	for (int i =0 ; i < 6 ; i++)
	{   u8 delay = 0 ;
		if (i == 5)
		{
			delay = 1 ;
		}
		HESC_voidInit( ESC + i , delay );
		
	}
    MI2C_voidAvrIntialization	();
///////////////////////////////////////////////////////////////////////////////////////////////////
	u8 counter = 0 ;
	u8 State;
	char Direction ;	
	char speed ;
	char ReadData[5]= {-102,-102,-102,-102,-102};
	u8 ParseState =3 ;
///////////////////////////////////////////////////////////////////////////////////////////////////

	while (1) 
    {   
	    State = MI2C_voidAvrState(255);
		if(State == I2C_WRITE){
			MI2C_voidAvrSlaveWrite(OCR0A);
			MI2C_voidAvrSlaveWrite(OCR0B);
			MI2C_voidAvrSlaveWrite(OCR1AL);
			MI2C_voidAvrSlaveWrite(OCR1BL);
			MI2C_voidAvrSlaveWrite(OCR2A);
			MI2C_voidAvrSlaveWrite(OCR2B);
			}
			else if (State == I2C_READ){
				ReadData[counter] = MI2C_u8AvrSlaveRead ();
				counter++;}
				
			else if (State == I2C_READ_STOP_CONDITION){
				counter= 0;
			    ParseState=ParseRecieved(&speed, &Direction, ReadData );
				if (ParseState == ERROR_IN_DATA)	
				{ for (int i=0 ; i<5 ; i++)
					{ ReadData[i] = -102;} 
					}                                    }
				else if (ParseState == DONE_RECIEVING)
				{
					switch (Direction)
					{
						case ROV_MOV_FORWARD :
						Moveforward ( speed , ESC );
						break ;
						case ROV_MOV_BACKWORD :
						MoveBackward ( speed , ESC );
						break ;
						case ROV_MOV_RIGHT :
						MoveRight ( speed , ESC );
						break ;
						case ROV_MOV_LEFT :
						Moveleft ( speed , ESC );
						break ;
						case ROV_MOV_ROT_RIGHT :
						RotateRight ( speed , ESC  );
						break ;
						case ROV_MOV_ROT_LEFT :
						RotateLeft ( speed , ESC  );
						break ;
						case ROV_MOV_UP :
						MoveUpward ( speed , ESC );
						break ;
						case ROV_MOV_DOWN :
						MoveDownward ( speed , ESC );
						break ;	
						case ROV_AUTO : 
						MoveAutonomous (ReadData , ESC);
					}
					for (int i=0 ; i<5 ; i++)
					{ ReadData[i] = -102;}				
					}

			else if (State == 255)
			{
            Moveforward (0 , ESC);	
						
			}
	
		}   
				}
				

 */
u8 ParseRecieved(char* speed, char* direction, char* array )
{  
	for (int i = 0 ; i < 5 ; i++)
	{  if (array[i]==-102)
		{ if (i==0)
			return NO_DATA_RECIEVED;
			else 
			return DONE_RECIEVING;}
	  if (array[0] == ROV_AUTO) 
			 {  
				 if (array[i]==-102)
				 return ERROR_IN_DATA;
			 }
       else if (i%2==0)
	  {  
		   if (array[i] == ROV_MOV_FORWARD||array[i] ==ROV_MOV_BACKWORD||array[i] ==ROV_MOV_RIGHT||array[i] ==ROV_MOV_LEFT||
		  array[i] ==ROV_MOV_UP||array[i] ==ROV_MOV_DOWN ||array[i] == ROV_MOV_ROT_RIGHT||array[i] == ROV_MOV_ROT_LEFT)
		  {*direction =array[i]; }

		  else 
		  {return ERROR_IN_DATA;}
	  }
	  else 
	  { if (array[i] <= 100 && array[i] >= 0 )
	   {*speed = array[i];}
		  else
		  {return ERROR_IN_DATA;}		   
	  }
	}
		  if (array[0] == ROV_AUTO) 
		  {  *direction =array[0];}
	return DONE_RECIEVING;
}

void Moveforward (char speed , esc* ptr_array )
{    
	  if (speed < 0)
	{
		speed = -1* speed ;
	}	
	for (int i =0 ; i < 4 ; i++)
	{
	HESC_voidSetMotorSpeed(speed , ptr_array + i );	
	//ptr_array[i].feedback_speed = speed ;
	}
    
}
void MoveBackward (char speed , esc* ptr_array )
{   if (speed > 0)
	{
	speed = -1* speed ; 		
	}
	for (int i =0 ; i < 4 ; i++)
	{
		HESC_voidSetMotorSpeed(speed , ptr_array + i );
		//ptr_array[i].feedback_speed = speed ;
	}

}
void MoveUpward (char speed , esc* ptr_array )
{
	if (speed < 0)
	{
		speed = -1* speed ;
	}
	for (int i =4 ; i < 6 ; i++)
	{
		HESC_voidSetMotorSpeed(speed , ptr_array + i );
		//ptr_array[i].feedback_speed = speed ;
	}

}
void MoveDownward (char speed , esc* ptr_array )
{   if (speed > 0)
	{
		speed = -1* speed ;
	}
	for (int i =4 ; i < 6 ; i++)
	{
		HESC_voidSetMotorSpeed(speed , ptr_array + i );
		//ptr_array[i].feedback_speed = speed ;
	}

}
void MoveRight (char speed , esc* ptr_array )
{   if (speed > 0)
	{  	
		speed = -1* speed ;
	}
   	for (u8 i = 0 ; i<6 ; i++)
   	{      if (i == 1 || i==2)
	   	{HESC_voidSetMotorSpeed(speed , ptr_array + i );
		 // ptr_array[i].feedback_speed = speed ;
		  }
	   	else if (i==0||i==3)
	   	{HESC_voidSetMotorSpeed(speed * -1 , ptr_array + i);
	   	//ptr_array[i].feedback_speed = speed * -1 ;
		   }

   	}

}
void Moveleft (char speed , esc* ptr_array )
{ if (speed > 0)
	{
		speed = -1* speed ;
	}

   for (u8 i = 0 ; i<6 ; i++)
	   	{      if (i == 1 || i==2)
		   	{HESC_voidSetMotorSpeed(speed * -1, ptr_array + i );
		   //	ptr_array[i].feedback_speed = speed * -1;
			    }
		   	else if (i==0||i==3)
		   	{HESC_voidSetMotorSpeed(speed  , ptr_array + i);
		   	//ptr_array[i].feedback_speed = speed  ;
			   }

	   	}
	
}
	

void RotateRight (char speed , esc* ptr_array )
{ if (speed > 0)
	{
		speed = -1* speed ;
	}
   for (u8 i = 0 ; i<6 ; i++)
   {      if (i == 0 || i==2)
	   {HESC_voidSetMotorSpeed(speed * -1, ptr_array + i );
	  // ptr_array[i].feedback_speed = speed * -1; 
	  }
	   else if (i==1||i==3)
	   {HESC_voidSetMotorSpeed(speed  , ptr_array + i);
	  // ptr_array[i].feedback_speed = speed  ;
	   }

   }	
}
 void RotateLeft (char speed , esc* ptr_array )
{ if (speed > 0)
	{
		speed = -1* speed ;
	}
   for (u8 i = 0 ; i<6 ; i++)
   {      if (i == 1 || i==3)
	   {HESC_voidSetMotorSpeed(speed * -1, ptr_array + i );
	  // ptr_array[i].feedback_speed = speed * -1; 
	  }
	   else if (i==0||i==2)
	   {HESC_voidSetMotorSpeed(speed  , ptr_array + i);
	   //ptr_array[i].feedback_speed = speed  ;
	   }	
}
   } 
	void MoveAutonomous (char* array , esc* ptr_array)
	{
	for (int i =0 ; i < 4 ; i++)
	{ 
           HESC_voidSetMotorSpeed( *(array+i+1 ), ptr_array + i );
	}
	}
		/*
		else if (State == I2C_READ){
			    check =  MI2C_u8AvrSlaveRead (); 
		        if (counter == 0 && (check == ROV_MOV_FORWARD||check ==ROV_MOV_BACKWORD||check ==ROV_MOV_RIGHT||check ==ROV_MOV_LEFT|| 
				check ==ROV_MOV_UP||check ==ROV_MOV_DOWN ||check == ROV_MOV_ROT_RIGHT||check == ROV_MOV_ROT_LEFT) )
		        {
					counter ++;
			        Mode= MI2C_u8AvrSlaveRead ();
		        }
		        else if (counter == 1 && (check <= 100 && check >= 0 ))
		        {
					speed = MI2C_u8AvrSlaveRead ();
					switch (Mode) 
					{
						case ROV_MOV_FORWARD :
							Moveforward ( speed , ESC );
							break ;
						case ROV_MOV_BACKWORD :
							MoveBackward ( speed , ESC );
							break ;
						case ROV_MOV_RIGHT :
							MoveRight ( speed , ESC );
							break ;
						case ROV_MOV_LEFT :
							Moveleft ( speed , ESC );
							break ;
						case ROV_MOV_ROT_RIGHT :
							RotateRight ( speed , ESC  );
							break ;
						case ROV_MOV_ROT_LEFT :
							RotateLeft ( speed , ESC  );
							break ;
						case ROV_MOV_UP :
							MoveUpward ( speed , ESC );
							break ;
						case ROV_MOV_DOWN :
							MoveDownward ( speed , ESC );
							break ;
						
					}
					counter = 0;
		        }	
		}
		else if (State == 255)
		{
		
		}
		*/
