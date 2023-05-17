/*
 * lcd.c
 *
 *  Created on: Jan 9, 2023
 *      Author: User02
 */


#include "MDL_lcd.h"
#include "MDL_led.h"



//uint8_t num_of_players;
//char num_of_players_print[2];
//char mLs_of_players_print[7];
//
//LCD_Player Players[4];
//LCD_Player Players_prev[4];
//LCD_Game_States game_state;
//uint32_t winner;

LCD_Handler lcd_handler;


//updates game state based on button press
void MDL_LCD_Bttn_Pressed(bttns bttn){
	switch(lcd_handler.game_state){
		case WELCOME:
			if (bttn == START){
				lcd_handler.game_state=NUM_OF_PLAYERS;
				change_LCD_screenstate();
			}
			break;

		case NUM_OF_PLAYERS:

			if (bttn == PLUS){
				if(lcd_handler.num_of_players < 6) lcd_handler.num_of_players++;
				lcd_handler.game_state = NUM_OF_PLAYERS;
				change_LCD_screenstate();
			}
			else if(bttn == MINUS){
				if(lcd_handler.num_of_players > 2) lcd_handler.num_of_players--;
				lcd_handler.game_state = NUM_OF_PLAYERS;
				change_LCD_screenstate();
			}
			else if(bttn == START){

				LCD_Add_Player();
				lcd_handler.game_state = PLAYER1;
				change_LCD_screenstate();
			}
			break;

		case PLAYER1:
			if(bttn == TOCI){
				lcd_handler.game_state= PLAYER2;
				change_LCD_screenstate();
				MDL_leds_next_round();
			}
			break;

		case PLAYER2:
			if(bttn == TOCI){
				if(lcd_handler.num_of_players == 2){
					lcd_handler.game_state= PLAYER1;
					change_LCD_screenstate();
				} else {
					lcd_handler.game_state= PLAYER3;
					change_LCD_screenstate();
				}
				MDL_leds_next_round();
			}
			break;
		case PLAYER3:
			if(bttn == TOCI){
				if(lcd_handler.num_of_players ==3){
					lcd_handler.game_state= PLAYER1;
					change_LCD_screenstate();
				} else {
					lcd_handler.game_state= PLAYER4;
					change_LCD_screenstate();
				}
				MDL_leds_next_round();
			}
			break;

		case PLAYER4:
			if(bttn == TOCI){
				if(lcd_handler.num_of_players ==4){
					lcd_handler.game_state= PLAYER1;
					change_LCD_screenstate();
				} else {
					lcd_handler.game_state= PLAYER5;
					change_LCD_screenstate();
				}
				MDL_leds_next_round();
			}
			break;

		case PLAYER5:
			if(bttn == TOCI){
				if(lcd_handler.num_of_players ==5){
					lcd_handler.game_state= PLAYER1;
					change_LCD_screenstate();
				} else {
					lcd_handler.game_state= PLAYER6;
					change_LCD_screenstate();
				}
				MDL_leds_next_round();
			}
			break;

		case PLAYER6:
			if(bttn == TOCI){
				lcd_handler.game_state= PLAYER1;
				change_LCD_screenstate();
				MDL_leds_next_round();
			}
			break;


		default:
			break;
	}

}


//updates game state based on sensor hits
void MDL_LCD_Hit_Update(uint32_t mLs){
	switch(lcd_handler.game_state){
			case PLAYER1:
				lcd_handler.Players[0].mL += mLs;
				change_LCD_screenstate();

				if(lcd_handler.Players[0].mL >= 1000){
					lcd_handler.game_state = WIN;
					lcd_handler.winner = 1;
					change_LCD_screenstate();
				}

				break;

			case PLAYER2:
				lcd_handler.Players[1].mL += mLs;
				change_LCD_screenstate();

				if(lcd_handler.Players[1].mL >= 1000){
					lcd_handler.game_state = WIN;
					lcd_handler.winner = 2;
					change_LCD_screenstate();
				}

				break;

			case PLAYER3:
				lcd_handler.Players[2].mL += mLs;
				change_LCD_screenstate();

				if(lcd_handler.Players[2].mL >= 1000){
					lcd_handler.game_state = WIN;
					lcd_handler.winner = 3;
					change_LCD_screenstate();
				}

				break;

			case PLAYER4:
				lcd_handler.Players[3].mL += mLs;
				change_LCD_screenstate();

				if(lcd_handler.Players[3].mL >= 1000){
					lcd_handler.game_state = WIN;
					lcd_handler.winner = 4;
					change_LCD_screenstate();
				}

				break;
			case PLAYER5:
				lcd_handler.Players[4].mL += mLs;
				change_LCD_screenstate();

				if(lcd_handler.Players[4].mL >= 1000){
					lcd_handler.game_state = WIN;
					lcd_handler.winner = 5;
					change_LCD_screenstate();
				}

				break;

			case PLAYER6:
				lcd_handler.Players[5].mL += mLs;
				change_LCD_screenstate();

				if(lcd_handler.Players[5].mL >= 1000){
					lcd_handler.game_state = WIN;
					lcd_handler.winner = 6;
					change_LCD_screenstate();
				}

				break;

			default:
				break;
	}
}



//initializes new game
void MDL_LCD_Init(){
	BSP_LCD_Init();			//tocnije nakon ovoga
	//MDL_leds_next_round();	//samo testni poziv

	BSP_LCD_LayerDefaultInit(LCD_BACKGROUND_LAYER, LCD_FRAME_BUFFER);
	BSP_LCD_LayerDefaultInit(LCD_FOREGROUND_LAYER, LCD_FRAME_BUFFER);
	BSP_LCD_SelectLayer(LCD_FOREGROUND_LAYER);
	BSP_LCD_DisplayOn();
	BSP_LCD_Clear(BGCOLOR);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

	lcd_handler.num_of_players=2;
	sprintf(lcd_handler.num_of_players_print, "%d", lcd_handler.num_of_players);

	lcd_handler.game_state=WELCOME;
	lcd_handler.winner = 0;
	change_LCD_screenstate();

}


//updates number of players based on player choice
void LCD_Add_Player(void){

	sprintf(lcd_handler.num_of_players_print, "%d", lcd_handler.num_of_players);

	for(uint32_t i=0; i<lcd_handler.num_of_players; i++){
		LCD_Player player = {i, 0};
		lcd_handler.Players[i]=player;
	}
}


//calls functions to change LCD screen based on game state
void change_LCD_screenstate(){

	switch (lcd_handler.game_state){
		case WELCOME:
			LCD_State_WELCOME();
			break;

		case NUM_OF_PLAYERS:
			LCD_State_NUM_OF_PLAYERS();
			break;

		case PLAYER1:
		case PLAYER2:
		case PLAYER3:
		case PLAYER4:
		case PLAYER5:
		case PLAYER6:
			LCD_State_PLAYERS();
			break;

		case WIN:
			LCD_State_WIN();
			break;

		default:
			break;

	}
}



//displays the WELCOME screen on the LCD
void LCD_State_WELCOME(void){
	BSP_LCD_SetFont(&Font20);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAtLine(5,(uint8_t *)"FERpong");
	BSP_LCD_DisplayStringAtLine(8,(uint8_t *)"pritisni start");
	BSP_LCD_DisplayStringAtLine(9,(uint8_t *)">");
}


//displays the NUM_OF_PLAYERS screen on the LCD
void LCD_State_NUM_OF_PLAYERS(void){
	sprintf(lcd_handler.num_of_players_print, "%d", lcd_handler.num_of_players);

	BSP_LCD_Clear(BGCOLOR);

	BSP_LCD_SetFont(&Font20);
	BSP_LCD_DisplayStringAtLine(2,(uint8_t *)"odabir igraca");


	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAtLine(5,(uint8_t *)lcd_handler.num_of_players_print);

	BSP_LCD_SetFont(&Font12);
	BSP_LCD_DisplayStringAtLine(17,(uint8_t *)"pritisni + za dodavanje igraca");
	BSP_LCD_DisplayStringAtLine(18,(uint8_t *)"pritisni - za uklanjanje igraca");
	BSP_LCD_DisplayStringAtLine(20,(uint8_t *)"max broj igraca je 6");

	BSP_LCD_SetFont(&Font16);
	BSP_LCD_DisplayStringAtLine(17,(uint8_t *)"pritisni start ");
	BSP_LCD_DisplayStringAtLine(18,(uint8_t *)"za pocetak igre");
}



//displays the WIN screen on the LCD
void LCD_State_WIN(void){
	BSP_LCD_Clear(LCD_COLOR_GREEN);
	char wintext[25];
	sprintf(wintext,"igrac %ld!", lcd_handler.winner);

	BSP_LCD_SetFont(&Font24);
	for(uint32_t i=0; i<10; i++){
		switch(lcd_handler.winner){
			case 1:
				BSP_LCD_Clear(LCD_COLOR_RED);
				break;
			case 2:
				BSP_LCD_Clear(LCD_COLOR_GREEN);
				break;
			case 3:
				BSP_LCD_Clear(LCD_COLOR_MAGENTA);
				break;
			case 4:
				BSP_LCD_Clear(LCD_COLOR_ORANGE);
				break;
			case 5:
				BSP_LCD_Clear(LCD_COLOR_BLUE);
				break;
			case 6:
				BSP_LCD_Clear(LCD_COLOR_YELLOW);
				break;
			default:
				break;

		}

		BSP_LCD_DisplayStringAt(0, 150,(uint8_t *)"pobjednik je", CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, 180,(uint8_t *)wintext, CENTER_MODE);
		HAL_Delay(500);
		BSP_LCD_Clear(LCD_COLOR_LIGHTCYAN);
		BSP_LCD_DisplayStringAt(0, 150,(uint8_t *)"pobjednik je", CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, 180,(uint8_t *)wintext, CENTER_MODE);
		HAL_Delay(500);
	}
	MDL_LCD_Init();
}



//displays the PLAYERx screen on the LCD
void LCD_State_PLAYERS(void){
	BSP_LCD_Clear(BGCOLOR);
	switch(lcd_handler.num_of_players){
		case 2:
			switch(lcd_handler.game_state){
				case PLAYER1:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_RED);
					BSP_LCD_FillRect(0,0,BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize()/2);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;
				case PLAYER2:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
					BSP_LCD_FillRect(BSP_LCD_GetXSize()/2,0,BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize()/2);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;
				default:
					break;
			}
			BSP_LCD_SetFont(&Font20);
			BSP_LCD_DisplayStringAt(10, 10, (uint8_t *)"igrac 1", LEFT_MODE);
			BSP_LCD_DisplayStringAt(-10, 10, (uint8_t *)"igrac 2", RIGHT_MODE);

			BSP_LCD_SetFont(&Font24);

			sprintf(lcd_handler.mLs_of_players_print, "%ld mL", lcd_handler.Players[0].mL);
			BSP_LCD_DisplayStringAt(10, 60,(uint8_t *)lcd_handler.mLs_of_players_print,LEFT_MODE);

			sprintf(lcd_handler.mLs_of_players_print, "%ld mL", lcd_handler.Players[1].mL);
			BSP_LCD_DisplayStringAt(-10, 60,(uint8_t *)lcd_handler.mLs_of_players_print, RIGHT_MODE);

			BSP_LCD_SetFont(&Font16);
			BSP_LCD_DisplayStringAt(0, 280,(uint8_t *)"pritisni toci", CENTER_MODE);
			BSP_LCD_DisplayStringAt(0, 295,(uint8_t *)"za kraj bacanja", CENTER_MODE);

			break;

		case 3:
			switch(lcd_handler.game_state){
				case PLAYER1:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_RED);
					BSP_LCD_FillRect(0,0,BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize()/2-20);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;
				case PLAYER2:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
					BSP_LCD_FillRect(BSP_LCD_GetXSize()/2,0,BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize()/2-20);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;
				case PLAYER3:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_MAGENTA);
					BSP_LCD_FillRect(BSP_LCD_GetXSize()/2-60,BSP_LCD_GetYSize()/2-20,BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize()/2-25);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;
				default:
					break;

			}
			BSP_LCD_SetFont(&Font20);
			BSP_LCD_DisplayStringAt(10, 10, (uint8_t *)"igrac 1", LEFT_MODE);
			BSP_LCD_DisplayStringAt(-10, 10, (uint8_t *)"igrac 2", RIGHT_MODE);
			BSP_LCD_DisplayStringAt(0, 150, (uint8_t *)"igrac 3", CENTER_MODE);

			BSP_LCD_SetFont(&Font24);

			sprintf(lcd_handler.mLs_of_players_print, "%ld mL", lcd_handler.Players[0].mL);
			BSP_LCD_DisplayStringAt(10, 60,(uint8_t *)lcd_handler.mLs_of_players_print,LEFT_MODE);

			sprintf(lcd_handler.mLs_of_players_print, "%ld mL", lcd_handler.Players[1].mL);
			BSP_LCD_DisplayStringAt(-10, 60,(uint8_t *)lcd_handler.mLs_of_players_print, RIGHT_MODE);

			sprintf(lcd_handler.mLs_of_players_print, "%ld mL", lcd_handler.Players[2].mL);
			BSP_LCD_DisplayStringAt(0, 200,(uint8_t *)lcd_handler.mLs_of_players_print, CENTER_MODE);

			BSP_LCD_SetFont(&Font16);
			BSP_LCD_DisplayStringAt(0, 280,(uint8_t *)"pritisni toci", CENTER_MODE);
			BSP_LCD_DisplayStringAt(0, 295,(uint8_t *)"za kraj bacanja", CENTER_MODE);

			break;

		case 4:
			switch(lcd_handler.game_state){
				case PLAYER1:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_RED);
					BSP_LCD_FillRect(0,0,BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize()/2-20);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;
				case PLAYER2:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
					BSP_LCD_FillRect(BSP_LCD_GetXSize()/2,0,BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize()/2-20);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;
				case PLAYER3:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_MAGENTA);
					BSP_LCD_FillRect(0,BSP_LCD_GetYSize()/2-20,BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize()/2-20);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;
				case PLAYER4:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
					BSP_LCD_FillRect(BSP_LCD_GetXSize()/2,BSP_LCD_GetYSize()/2-20,BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize()/2-20);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;

				default:
					break;
			}

			BSP_LCD_SetFont(&Font20);
			BSP_LCD_DisplayStringAt(10, 10, (uint8_t *)"igrac 1", LEFT_MODE);
			BSP_LCD_DisplayStringAt(-10, 10, (uint8_t *)"igrac 2", RIGHT_MODE);
			BSP_LCD_DisplayStringAt(10, 150, (uint8_t *)"igrac 3", LEFT_MODE);
			BSP_LCD_DisplayStringAt(-10, 150, (uint8_t *)"igrac 4", RIGHT_MODE);

			BSP_LCD_SetFont(&Font24);

			sprintf(lcd_handler.mLs_of_players_print, "%ld mL", lcd_handler.Players[0].mL);
			BSP_LCD_DisplayStringAt(10, 60,(uint8_t *)lcd_handler.mLs_of_players_print,LEFT_MODE);

			sprintf(lcd_handler.mLs_of_players_print, "%ld mL", lcd_handler.Players[1].mL);
			BSP_LCD_DisplayStringAt(-10, 60,(uint8_t *)lcd_handler.mLs_of_players_print, RIGHT_MODE);

			sprintf(lcd_handler.mLs_of_players_print, "%ld mL", lcd_handler.Players[2].mL);
			BSP_LCD_DisplayStringAt(10, 200,(uint8_t *)lcd_handler.mLs_of_players_print, LEFT_MODE);

			sprintf(lcd_handler.mLs_of_players_print, "%ld mL", lcd_handler.Players[3].mL);
			BSP_LCD_DisplayStringAt(-10, 200,(uint8_t *)lcd_handler.mLs_of_players_print, RIGHT_MODE);

			BSP_LCD_SetFont(&Font16);
			BSP_LCD_DisplayStringAt(0, 280,(uint8_t *)"pritisni toci", CENTER_MODE);
			BSP_LCD_DisplayStringAt(0, 295,(uint8_t *)"za kraj bacanja", CENTER_MODE);

			break;

		case 5:
			switch(lcd_handler.game_state){
				case PLAYER1:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_RED);
					BSP_LCD_FillRect(0,0,120, 80);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;
				case PLAYER2:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
					BSP_LCD_FillRect(120,0,120, 80);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;
				case PLAYER3:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_MAGENTA);
					BSP_LCD_FillRect(0,80+10,120, 80);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;
				case PLAYER4:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
					BSP_LCD_FillRect(120,80+10,120, 80);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;
				case PLAYER5:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
					BSP_LCD_FillRect(60,160+20,120, 80);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;

				default:
					break;
			}


			BSP_LCD_SetFont(&Font16);
			BSP_LCD_DisplayStringAt(10, 10, (uint8_t *)"igrac 1", LEFT_MODE);
			BSP_LCD_DisplayStringAt(-10, 10, (uint8_t *)"igrac 2", RIGHT_MODE);
			BSP_LCD_DisplayStringAt(10, 100, (uint8_t *)"igrac 3", LEFT_MODE);
			BSP_LCD_DisplayStringAt(-10, 100, (uint8_t *)"igrac 4", RIGHT_MODE);
			BSP_LCD_DisplayStringAt(0, 190, (uint8_t *)"igrac 5", CENTER_MODE);
			BSP_LCD_SetFont(&Font24);

			for(uint32_t i =1; i<= lcd_handler.num_of_players-1; i=i+2){
				sprintf(lcd_handler.mLs_of_players_print, "%ld mL", lcd_handler.Players[i-1].mL);
				BSP_LCD_DisplayStringAt(10, 10+90*(i-1)/2+35,(uint8_t *)lcd_handler.mLs_of_players_print,LEFT_MODE);
			}

			for(uint32_t i = 2; i<= lcd_handler.num_of_players-1; i=i+2){
				sprintf(lcd_handler.mLs_of_players_print, "%ld mL", lcd_handler.Players[i-1].mL);
				BSP_LCD_DisplayStringAt(-10, 10+90*(i-2)/2+35,(uint8_t *)lcd_handler.mLs_of_players_print,RIGHT_MODE);
			}

			sprintf(lcd_handler.mLs_of_players_print, "%ld mL", lcd_handler.Players[4].mL);
			BSP_LCD_DisplayStringAt(0, 10+90*(6-2)/2+35,(uint8_t *)lcd_handler.mLs_of_players_print,CENTER_MODE);

			BSP_LCD_SetFont(&Font16);
			BSP_LCD_DisplayStringAt(0, 280,(uint8_t *)"pritisni toci", CENTER_MODE);
			BSP_LCD_DisplayStringAt(0, 295,(uint8_t *)"za kraj bacanja", CENTER_MODE);

		break;

		case 6:
			switch(lcd_handler.game_state){
				case PLAYER1:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_RED);
					BSP_LCD_FillRect(0,0,120, 80);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;
				case PLAYER2:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
					BSP_LCD_FillRect(120,0,120, 80);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;
				case PLAYER3:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_MAGENTA);
					BSP_LCD_FillRect(0,80+10,120, 80);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;
				case PLAYER4:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
					BSP_LCD_FillRect(120,80+10,120, 80);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;
				case PLAYER5:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
					BSP_LCD_FillRect(0,160+20,120, 80);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;
				case PLAYER6:
					BSP_LCD_Clear(BGCOLOR);
					BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
					BSP_LCD_FillRect(120,160+20,120, 80);
					BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
					break;

				default:
					break;
			}

			BSP_LCD_SetFont(&Font16);
			BSP_LCD_DisplayStringAt(10, 10, (uint8_t *)"igrac 1", LEFT_MODE);
			BSP_LCD_DisplayStringAt(-10, 10, (uint8_t *)"igrac 2", RIGHT_MODE);
			BSP_LCD_DisplayStringAt(10, 100, (uint8_t *)"igrac 3", LEFT_MODE);
			BSP_LCD_DisplayStringAt(-10, 100, (uint8_t *)"igrac 4", RIGHT_MODE);
			BSP_LCD_DisplayStringAt(10, 190, (uint8_t *)"igrac 5", LEFT_MODE);
			BSP_LCD_DisplayStringAt(-10, 190, (uint8_t *)"igrac 6", RIGHT_MODE);

			BSP_LCD_SetFont(&Font24);

			for(uint32_t i =1; i<= lcd_handler.num_of_players; i=i+2){
				sprintf(lcd_handler.mLs_of_players_print, "%ld mL", lcd_handler.Players[i-1].mL);
				BSP_LCD_DisplayStringAt(10, 10+90*(i-1)/2+35,(uint8_t *)lcd_handler.mLs_of_players_print,LEFT_MODE);
			}

			for(uint32_t i = 2; i<= lcd_handler.num_of_players; i=i+2){
				sprintf(lcd_handler.mLs_of_players_print, "%ld mL", lcd_handler.Players[i-1].mL);
				BSP_LCD_DisplayStringAt(-10, 10+90*(i-2)/2+35,(uint8_t *)lcd_handler.mLs_of_players_print,RIGHT_MODE);
			}


			BSP_LCD_SetFont(&Font16);
			BSP_LCD_DisplayStringAt(0, 280,(uint8_t *)"pritisni toci", CENTER_MODE);
			BSP_LCD_DisplayStringAt(0, 295,(uint8_t *)"za kraj bacanja", CENTER_MODE);

			break;
	default:
		break;
	}
}


