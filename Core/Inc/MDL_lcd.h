/*
 * lcd.h
 *
 *  Created on: 12. sij 2023.
 *      Author: User02
 */



#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f429i_discovery_lcd.h"
#include "stdio.h"

#define BGCOLOR LCD_COLOR_LIGHTCYAN

typedef enum LCD_Game_States{
	WELCOME,
	NUM_OF_PLAYERS,
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	PLAYER5,
	PLAYER6,
	WIN
}LCD_Game_States;


typedef struct LCD_Player{
	uint32_t redni_broj;
	uint32_t mL;
}LCD_Player;

typedef struct LCD_Handler{

	uint8_t num_of_players;
	char num_of_players_print[2];
	char mLs_of_players_print[7];

	LCD_Player Players[6];
	//LCD_Player Players_prev[4];
	LCD_Game_States game_state;
	uint32_t winner;

}LCD_Handler;


typedef enum bttns{
	START,
	PLUS,
	MINUS,
	TOCI
}bttns;

void LCD_Add_Player(void);
void MDL_LCD_Init(void);
void MDL_LCD_Hit_Update(uint32_t mLs);
void MDL_LCD_Bttn_Pressed(bttns bttn);

void LCD_State_WELCOME(void);
void LCD_State_NUM_OF_PLAYERS(void);
void LCD_State_WIN(void);
void LCD_State_PLAYERS(void);
void change_LCD_screenstate(void);




#endif /* INC_LCD_H_ */
