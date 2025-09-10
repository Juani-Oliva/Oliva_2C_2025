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
/*==================[macros and definitions]=================================*/

/*==================[internal data definition]===============================*/

/*==================[internal functions declaration]=========================*/
int8_t  convertToBcdArray (uint32_t data, uint8_t digits, uint8_t * bcd_number)
{
 for (int i = digits - 1; i >= 0; i--) {
        bcd_number[i] = data % 10;   // extrae dígito decimal
        data /= 10;               // reduce el número
    }
return 0 ; 
}


/*==================[external functions definition]==========================*/
void app_main(void){
	uint32_t numero = 573 ;
	uint8_t digitos_salida = 3; 
	uint8_t arreglo[numero]; 

convertToBcdArray(numero,digitos_salida,arreglo);


}
/*==================[end of file]============================================*/