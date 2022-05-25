/*
 * Timer.h
 *
 * Created: 5/4/2022 4:16:18 PM
 *  Author: DELL
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include "..\..\std_macros.h"

void timer1_init();
void timer0_init();
void timer1_INT_disable();
void timer1_INT_enable();

#endif /* TIMER_H_ */