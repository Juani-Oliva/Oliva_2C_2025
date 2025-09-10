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
 * |   Display      |   EDU-ESP	|
 * |:--------------:|:-------------:|
 * | 	Vcc 	    |	5V      	|
 * | 	BCD1		| 	GPIO_20		|
 * | 	BCD2	 	| 	GPIO_21		|
 * | 	BCD3	 	| 	GPIO_22		|
 * | 	BCD4	 	| 	GPIO_23		|
 * | 	SEL1	 	| 	GPIO_19		|
 * | 	SEL2	 	| 	GPIO_18		|
 * | 	SEL3	 	| 	GPIO_9		|
 * | 	Gnd 	    | 	GND     	|
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
typedef struct
{
	gpio_t pin;			/*!< GPIO pin number */
	io_t dir;			/*!< GPIO direction '0' IN;  '1' OUT*/
} gpioConf_t;
/*==================[internal functions declaration]=========================*/
void mostrarDigito(uint8_t digito, gpioConf_t *arreglo)
{
	for (uint8_t i = 0; i < 4; i++)
	{
		if (digito & 1 << i)
		{
			GPIOOn(arreglo[i].pin);
		}
		else
		{	
			GPIOOff(arreglo[i].pin);
		}
		
	}
}
int8_t convertToBcdArray(uint32_t data, uint8_t digits, uint8_t *bcd_number)
{
	for (uint8_t i = digits - 1; i >= 0 && data > 0; i--)
	{
		bcd_number[i] = data % 10;
		data = data / 10;
	}

	return 0;
}
void mostrarNumeroEnPantalla(int32_t numero, uint8_t digits, gpioConf_t *segmentos, gpioConf_t *grupo)
{
	int8_t error;
	uint8_t digitos[digits] ;

	error = convertToBcdArray(numero, digits, digitos);

	for (uint8_t i = 0; i < 3; i++)
	{
		mostrarDigito(digitos[i], segmentos);
		GPIOOn(grupo[i].pin);
		GPIOOff(grupo[i].pin);
	}
	

}
/*==================[external functions definition]==========================*/
void app_main(void){

	gpioConf_t vector[4] = {
		{GPIO_20, GPIO_OUTPUT},
		{GPIO_21, GPIO_OUTPUT},
		{GPIO_22, GPIO_OUTPUT},
		{GPIO_23, GPIO_OUTPUT}
	};
	gpioConf_t grupo[3] = {
		{GPIO_19, GPIO_OUTPUT},
		{GPIO_18, GPIO_OUTPUT},
		{GPIO_9, GPIO_OUTPUT}
	};

	for (uint8_t i = 0; i < 4; i++)
	{
		GPIOInit(vector[i].pin, vector[i].dir);
	}
	for (uint8_t i = 0; i < 3; i++)
	{
		GPIOInit(grupo[i].pin, grupo[i].dir);
	}

	//mostrarDigito(7, vector);	
	mostrarNumeroEnPantalla(021, 3, vector, grupo);
}
/*==================[end of file]============================================*/