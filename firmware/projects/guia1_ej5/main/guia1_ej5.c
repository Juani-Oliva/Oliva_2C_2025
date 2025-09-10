/*! @mainpage Template
 *
 * @section genDesc General Description
 *
 * This section describes how the program works.
 *
 * <a href="https://drive.google.com/...">Operation Example</a>
 *
 * @section hardConn Hardware Connection
 *
 * |    Peripheral  |   ESP32   	|
 * |:--------------:|:--------------|
 * | 	PIN_X	 	| 	GPIO_X		|
 *
 *
 * @section changelog Changelog
 *
 * |   Date	    | Description                                    |
 * |:----------:|:-----------------------------------------------|
 * | 12/09/2023 | Document creation		                         |
 *
 * @author Albano Peñalva (albano.penalva@uner.edu.ar)
 *
 */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include "gpio_mcu.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data definition]===============================*/

/*==================[internal functions declaration]=========================*/
typedef struct
{
	gpio_t pin;			/*!< GPIO pin number */
	io_t dir;			/*!< GPIO direction '0' IN;  '1' OUT*/
} gpioConf_t;

void cambio_estado(uint8_t BCD, gpioConf_t * vector)
{ 
for ( int i=0; i<4 ; i++) 
{
	if( BCD & (1<<i))  //corro el 1 hacia la izquierda para que se compare con el numero binario siguiente
		GPIOOn(vector[i].pin);
	else 
		GPIOOff(vector[i].pin);
}
}

/*==================[external functions definition]==========================*/
void app_main(void){
	gpioConf_t arregloGPIO[4] = 
	{
		{GPIO_20,GPIO_OUTPUT},{GPIO_21,GPIO_OUTPUT},{GPIO_22,GPIO_OUTPUT},{GPIO_23,GPIO_OUTPUT}
	};

	for (int i = 0 ; i < 4 ; i++) {
		GPIOInit(arregloGPIO[i].pin,arregloGPIO[i].dir); 
	}
	cambio_estado(5,arregloGPIO);
	
}
/*==================[end of file]============================================*/