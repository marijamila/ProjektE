/*
 * MDL_led.h
 *
 *  Created on: Jan 9, 2023
 *      Author: Marija
 */

#include "main.h"

#define NUM_OF_LEDS 6

typedef enum LED_sentStatus {
	TRANSFER_FINISHED,
	TRANSFER_NOT_FINISHED,

} LED_sentStatus;

typedef enum LED_number {
	LED_1 = 0,
	LED_2 = 1,
	LED_3 = 2,
	LED_4 = 3,
	LED_5 = 4,
	LED_6 = 5
} LED_number;

typedef struct LED_handler {
	LED_sentStatus datasentflag;
	uint8_t led[NUM_OF_LEDS];
	uint8_t LED_Data[NUM_OF_LEDS][4];
	uint8_t pwmData[24 * NUM_OF_LEDS + 50];
} LED_handler;


void MDL_leds_init();
void MDL_leds_scored(uint8_t sensorNum);
void MDL_leds_next_round();
void MDL_leds_win();
void set_LED(uint8_t LEDnum, uint8_t Red, uint8_t Green, uint8_t Blue);
void send(void);
