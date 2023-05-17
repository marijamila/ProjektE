/*
 * MDL_led.c
 *
 *  Created on: Jan 9, 203
 *      Author: Marija
 */

#include <MDL_led.h>
#include "MDL_lcd.h"
#include "MDL_dispenser.h"
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"
#include "usart.h"
#include <stdlib.h>


void set_LED(uint8_t LEDnum, uint8_t Red, uint8_t Green, uint8_t Blue);
void send();

struct LED_handler ledHandler;


void MDL_leds_init() {
	ledHandler.datasentflag = TRANSFER_NOT_FINISHED;
	for(int i = 0; i < NUM_OF_LEDS; i++) {
		ledHandler.led[i] = i;
	}
}

void set_LED(uint8_t LEDnum, uint8_t Red, uint8_t Green, uint8_t Blue) {
	ledHandler.LED_Data[LEDnum][0] = LEDnum;
	ledHandler.LED_Data[LEDnum][1] = Red;
	ledHandler.LED_Data[LEDnum][2] = Green;
	ledHandler.LED_Data[LEDnum][3] = Blue;
}

void send(void) {



	uint32_t index = 0;
	uint32_t color;

	for (uint8_t i = 0; i < NUM_OF_LEDS; i++) {
		color = ((ledHandler.LED_Data[i][1] << 16) | (ledHandler.LED_Data[i][2] << 8) | (ledHandler.LED_Data[i][3]));

		for (uint8_t i = 24; i > 0; i--) {
			if (color & (1 << (i - 1)))
				ledHandler.pwmData[index] = 75; //19  //60  //150
			else
				ledHandler.pwmData[index] = 37; //9  //30 //75
			index++;
		}
	}

	for (uint8_t i = 0; i < 50; i++) {
		ledHandler.pwmData[index] = 0;
		index++;
	}

	HAL_UART_Transmit_DMA(&huart3, ledHandler.pwmData, 24 * NUM_OF_LEDS + 50); //sizeof(ledHandler.pwmData));

//	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_1, (uint32_t*) ledHandler.pwmData, index);
//	ledHandler.datasentflag = TRANSFER_NOT_FINISHED;
//	while (ledHandler.datasentflag == TRANSFER_NOT_FINISHED) {};

}

void MDL_leds_next_round(void) {

	for (uint8_t i = 0; i < NUM_OF_LEDS - 1; i++) {
		uint8_t n = i + rand() / (RAND_MAX / (NUM_OF_LEDS - i) + 1);
		uint8_t pom = ledHandler.led[n];
		ledHandler.led[n] = ledHandler.led[i];
		ledHandler.led[i] = pom;
	}

	set_LED(LED_1, 0, 0, 0);
	set_LED(LED_2, 0, 0, 0);
	set_LED(LED_3, 0, 0, 0);
	set_LED(LED_4, 0, 0, 0);
	set_LED(LED_5, 0, 0, 0);
	set_LED(LED_6, 0, 0, 0);
	send();
	HAL_Delay(600);

	set_LED(ledHandler.led[0], 0, 255, 0);
	set_LED(ledHandler.led[1], 0, 255, 0);
	set_LED(ledHandler.led[2], 0, 255, 0);
	set_LED(ledHandler.led[3], 0, 0, 255);
	set_LED(ledHandler.led[4], 0, 0, 255);
	set_LED(ledHandler.led[5], 0, 0, 255);
	send();

}

void MDL_leds_scored(uint8_t sensorNum) {
	uint8_t index;
	uint8_t points = 25;  // plava
	uint8_t color = 3;
	for (uint8_t i = 0; i < NUM_OF_LEDS; i++) {
		if (ledHandler.led[i] == sensorNum) index = i;
	}

	if (index == 0) {  // crvena
		color = 1;
		points = 100;
	}
	else if (index == 1 || index == 2) { //zelena
		color = 2;
		points = 50;
	}

	for (uint8_t j = 0; j < 3; j++) {
		set_LED(sensorNum, 0, 0, 0);
		send();
		HAL_Delay(100);
		if (color == 1)	set_LED(sensorNum, 255, 0, 0);
		else if (color == 2) set_LED(sensorNum, 0, 255, 0);
		else set_LED(sensorNum, 0, 0, 255);
		send();
		HAL_Delay(100);
	}

	MDL_LCD_Hit_Update(points);
	sumator(points);

}


void MDL_leds_win(void) {

	set_LED(LED_1, 0, 0, 0);
	set_LED(LED_2, 0, 0, 0);
	set_LED(LED_3, 0, 0, 0);
	set_LED(LED_4, 0, 0, 0);
	set_LED(LED_5, 0, 0, 0);
	set_LED(LED_6, 0, 0, 0);
	send();
	HAL_Delay(300);

	for (uint8_t i = 0; i < 4*NUM_OF_LEDS; i++) {

		set_LED(i % NUM_OF_LEDS, 102, 0, 255);
		set_LED((i + 1) % NUM_OF_LEDS, 0, 153, 255);
		set_LED((i + 2) % NUM_OF_LEDS, 101, 255, 68);
		set_LED((i + 3) % NUM_OF_LEDS, 255, 197, 20);
		set_LED((i + 4) % NUM_OF_LEDS, 255, 102, 0);
		set_LED((i + 5) % NUM_OF_LEDS, 153, 0, 51);
		send();
		HAL_Delay(100);
		set_LED(i % NUM_OF_LEDS, 142, 0, 142);  //ljubicasta
		set_LED((i + 1) % NUM_OF_LEDS, 0, 0, 255);  //plava
		set_LED((i + 2) % NUM_OF_LEDS, 0, 255, 40);  //zelena
		set_LED((i + 3) % NUM_OF_LEDS, 255, 255, 0);  //zuta
		set_LED((i + 4) % NUM_OF_LEDS, 255, 115, 15);  //narancasta
		set_LED((i + 5) % NUM_OF_LEDS, 255, 0, 0);  //crvena
		send();
		HAL_Delay(100);
	}

}



//void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
//	HAL_TIM_PWM_Stop_DMA(&htim4, TIM_CHANNEL_1);
//	ledHandler.datasentflag = TRANSFER_FINISHED;
//}
