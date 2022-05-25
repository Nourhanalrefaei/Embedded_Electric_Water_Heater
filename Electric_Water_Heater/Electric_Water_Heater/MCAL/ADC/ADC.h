/*
 * ADC.h
 *
 * Created: 3/4/2022 8:20:38 AM
 *  Author: DELL
 */ 


#ifndef ADC_H_
#define ADC_H_


#include <avr/io.h>
#include "..\..\std_macros.h"

void ADC_init(void);
uint16_t ADC_read(void);


#endif /* ADC_H_ */