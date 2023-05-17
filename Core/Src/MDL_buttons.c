/*
 * MDL_buttons.c
 *
 *  Created on: Jan 5, 2023
 *      Author: Marko Srpak
 */

#include "main.h"
#include "FERpong.h"
#include "MDL_led.h"


struct MDL_buttons_handler buttons_handler;


void MDL_buttons_init(){
	//init GPIO gatea
	for(int i = 0; i < NUM_OF_BUTTONS; i++){
		buttons_handler.buttons[i].gpio = GPIOE;
		buttons_handler.buttons[i].pressed_ago = 0;
	}
	//init GPIO pinova
	buttons_handler.buttons[0].gpio_pin = GPIO_PIN_3;
	buttons_handler.buttons[1].gpio_pin = GPIO_PIN_2;
	buttons_handler.buttons[2].gpio_pin = GPIO_PIN_4;
	buttons_handler.buttons[3].gpio_pin = GPIO_PIN_6;

	buttons_handler.buttons[0].button_type = START;
	buttons_handler.buttons[1].button_type = MINUS;
	buttons_handler.buttons[2].button_type = PLUS;
	buttons_handler.buttons[3].button_type = TOCI;

}

void BUTTON_CHECK(int i){

	buttons_handler.buttons[i].button_state = HAL_GPIO_ReadPin(buttons_handler.buttons[i].gpio, buttons_handler.buttons[i].gpio_pin);

	if(buttons_handler.buttons[i].prev_button_state == GPIO_PIN_SET && buttons_handler.buttons[i].button_state == GPIO_PIN_RESET){
		//detected falling edge
		buttons_handler.buttons[i].pressed_ago = 0;
	}
	if(buttons_handler.buttons[i].prev_button_state == GPIO_PIN_RESET && buttons_handler.buttons[i].button_state == GPIO_PIN_SET){
		//detected rising edge
		if(buttons_handler.buttons[i].pressed_ago == BUTTON_HALT_TIME){
			MDL_LCD_Bttn_Pressed(buttons_handler.buttons[i].button_type);
			if(buttons_handler.buttons[i].button_type == TOCI){
				MDL_leds_next_round();
				//TociPressed();
			//	Dispenser(200);
			}
		}
		buttons_handler.buttons[i].pressed_ago = 0;

	}
	if(buttons_handler.buttons[i].pressed_ago < BUTTON_HALT_TIME){
		buttons_handler.buttons[i].pressed_ago++;
	}
	buttons_handler.buttons[i].prev_button_state = buttons_handler.buttons[i].button_state;
}


void MDL_Buttons_Handler(){
	for(int i = 0; i < NUM_OF_BUTTONS; i++){
		BUTTON_CHECK(i);
	}
}


