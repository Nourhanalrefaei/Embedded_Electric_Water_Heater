/*
 * Electric_Water_Heater.c
 *
 * Created: 5/22/2022 8:27:09 PM
 * Author : DELL
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "std_macros.h"
#include "System/Sys.h"


/*----------------------------------------------------------------------------*-
ON/OFF_Button_ISR : To switch between ON and OFF States.
-*----------------------------------------------------------------------------*/

ISR(INT2_vect){
	if(Curr_state==OFF){
		Curr_state = ON;
		desired_temp = EEPROM_read(0x0000);
	}
	else if (Curr_state==ON || Curr_state==SETTING){
		Curr_state = OFF;
	}
}

/*----------------------------------------------------------------------------*-
TIMER0_ISR (A) : It triggers the ISR every 100ms. So, it makes the temperature
measure flag equals one to enable the ADC to do the work.
-*----------------------------------------------------------------------------*/

ISR(TIMER0_COMP_vect){
	set_counter_timer0++;
	if(set_counter_timer0%3==0)
	{
		temp_measure_f = 1;
		set_counter_timer0=0;
	}
	
}

/*----------------------------------------------------------------------------*-
TIMER1_ISR (B) : It triggers the ISR every 1 second. So, it toggles the
toggle flag for the Seven Segment. and counts to keep it in
ON_STATE if nothing is pressed during in ON or SETTING modes for 5 secs.
-*----------------------------------------------------------------------------*/

ISR(TIMER1_COMPA_vect){
	if ((Curr_state==SETTING) || (Curr_state==ON)){
		setting_counter++;
		if(setting_counter % 2 == 0){
			toggle_f ^= 1;
			avg_flag=1;
		}
		if (setting_counter ==10){
			
			// Write the new desired temperature in EEPROM
			Curr_state = ON;
		}
	}
}

/*----------------------------------------------------------------------------*-
Main_Function : It's where the program chooses which function will be executed
depending on the variable (Curr_state) that changes with ISRs.
-*----------------------------------------------------------------------------*/


int main(void){
	
	sys_init();
	
	while(1){
		switch (Curr_state){
			case ON:{
				ON_state();
				break;
			}
			case OFF:{
				OFF_state();
				break;
			}
			case SETTING:{
				SET_state();
				break;
			}
		}
	}
}

