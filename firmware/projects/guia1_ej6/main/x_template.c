/** @mainpage Proyecto 1 de Electrónica Programable:
 * Ejercicio 6.
 *
 * @section genDesc General Description
 * En este ejercicio se crea una función que recibe un dato de 32 bits,
 * la cantidad de dígitos de salida y dos vectores de estructuras del tipo gpioConf_t. 
 * Uno  de estos vectores es igual al definido en el ejercicio 5
 * y el otro vector mapea los puertos con el dígito del LCD a donde mostrar un dato.
 * La función debe mostrar por display el valor que recibe. Para ello se reutilizan
 * las funciones creadas en los puntos 4 y 5.

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
 * | 10/09/2025 | Document creation		                         |
 *
 * @author Juan Ignacio Oliva (juan.oliva@ingenieria.uner.edu.ar)
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
/**
 * @brief Enciende/apaga los GPIOs según el valor del dígito recibido
 * 
 * @param digito Número a mostrar
 * @param arreglo Arreglo de GPIOs configurado 
 */
void cambio_estado_gpio(uint8_t BCD, gpioConf_t * vector)
{ 
for ( int i=0; i<4 ; i++) 
{
	if( BCD & (1<<i))  //Mueve el 1 "i" veces hacia la izquierda y lo compara con el digito en binario
		GPIOOn(vector[i].pin);
	else 
		GPIOOff(vector[i].pin);
}
}
/**
 * @brief Convierte un numero a un arreglo BCD
 * 
 * @param data Numero a convertir.
 * @param digits Cantidad de dígitos del número.
 * @param bcd_number Arreglo cargado que es pasado por referencia.
 * 
 * @returns 0 si es sin error, o.c. código de error. Actualmente solo 0.
 */
int8_t convertToBcdArray(uint32_t data, uint8_t digits, uint8_t *bcd_number)
{
	for (uint8_t i = digits - 1; i >= 0 && data > 0; i--)
	{
		bcd_number[i] = data % 10; //Extrae digito decimal y lo almacena en la posicion i del arreglo
		data = data / 10; //Reduce el numero
	}

	return 0;
}
 /** 
 * @brief Muestra en display de 7 segmentos el numero ingresado
 * @param numero Numero.
 * @param digits Cantidad de dígitos del número.
 * @param arreglo_gpios Arreglo de GPIOS que representan el numero
 * @param puerto Arreglo de GPIOS que mapea los puertos para mostrar un digito determinado
 */
void mostrarNumeroEnPantalla(int32_t numero, uint8_t digits, gpioConf_t *arreglo_gpios, gpioConf_t *puerto)
{
	int8_t error;
	uint8_t digitos[digits] ;

	error = convertToBcdArray(numero, digits, digitos);

	for (uint8_t i = 0; i < 3; i++)
	{
		cambio_estado_gpio(digitos[i], arreglo_gpios);
		GPIOOn(puerto[i].pin);
		GPIOOff(puerto[i].pin);
	}
}
/*==================[external functions definition]==========================*/
void app_main(void){

	gpioConf_t vector_gpios[4] = {
		{GPIO_20, GPIO_OUTPUT},
		{GPIO_21, GPIO_OUTPUT},
		{GPIO_22, GPIO_OUTPUT},
		{GPIO_23, GPIO_OUTPUT}
	};
	gpioConf_t puerto[3] = {
		{GPIO_19, GPIO_OUTPUT},
		{GPIO_18, GPIO_OUTPUT},
		{GPIO_9, GPIO_OUTPUT}
	};

	for (uint8_t i = 0; i < 4; i++)
	{
		GPIOInit(vector_gpios[i].pin, vector_gpios[i].dir);
	}
	for (uint8_t i = 0; i < 3; i++)
	{
		GPIOInit(puerto[i].pin, puerto[i].dir);
	}
 
	mostrarNumeroEnPantalla(021, 3, vector_gpios, puerto);
}
/*==================[end of file]============================================*/