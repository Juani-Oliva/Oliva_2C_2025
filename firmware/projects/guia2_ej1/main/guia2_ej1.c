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
/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
#include "switch.h"
#include "hc_sr04.h"
/*==================[macros and definitions]=================================*/
#define CONFIG_BLINK_PERIOD 1000
#define CONFIG_BLINK_PERIOD_TECLAS 500
#define CONFIG_BLINK_PERIOD_LED_3 500

/*==================[internal data definition]===============================*/
TaskHandle_t led1_task_handle = NULL;
TaskHandle_t led2_task_handle = NULL;
TaskHandle_t led3_task_handle = NULL;
/*==================[internal functions declaration]=========================*/
bool act_Med = false;
bool hold = false ;
int M; 
static void Teclas(void *pvParameter){
    uint8_t teclas;
    LedsInit();
	SwitchesInit();
    while(true){
        teclas  = SwitchesRead();
    	switch(teclas){
    		case SWITCH_1:
                act_Med = !act_Med ;
    		break;
    		case SWITCH_2:
    			hold = !hold; 
    		break;
    	}
        vTaskDelay(CONFIG_BLINK_PERIOD_TECLAS / portTICK_PERIOD_MS); //Si ninguno de los case se cumple o bien despues de cumplir alguno de ellos, se direcciona al DELAY

}}

static void Medir(void *pvParameter){
    while(true){
      if(act_Med == true)
        M = HcSr04ReadDistanceInCentimeters;  //funcion del ultrasonido que mide

    vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    
    }
}

static void Leds(void *pvParameter){
    while(true){
       if(act_Med == true)
       {
        if(M<10)
        LedsOffAll();
        else if(M<20)
            Led1ON/ElrestoApagado
        else if(M<30)
            Led3OFF/ Led1y2ON
        else
            TodosLedsOn
       }
       else 
       ApagarTodosLeds
    vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}
/*==================[external functions definition]==========================*/
void app_main(void){

    HcSr04Init(gpio_t echo, gpio_t trigger); //trigger : pulso cuando dispara el sonido //Echo pulso que recibe 
    LedsInit();
    xTaskCreate(&Led1Task, "LED_1", 512, NULL, 5, &led1_task_handle);
    xTaskCreate(&Led2Task, "LED_2", 512, NULL, 5, &led2_task_handle);
    xTaskCreate(&Led3Task, "LED_3", 512, NULL, 5, &led3_task_handle);

   
}