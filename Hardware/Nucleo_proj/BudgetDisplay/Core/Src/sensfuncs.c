/**
******************************************************************************
@brief sensfuncs, functions for Sensor shield project
@file sensfuncs.c
@author Oliver Gortzak
@version 1.0
@date 10-December-2020
@brief Functions and structures for sensor shield project
******************************************************************************
*/

#include "sensfuncs.h"
#include "main.h"
#include "adc.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"
#include "usart.h"
#include "String.h"

// start bytes for screen comm
#define RS   (uint8_t) 0x5F
#define SYNC (uint8_t) 0x1F

// screencom transmission buffer
uint8_t data[3];

// screen content buffer
char str[4][21] = {"This is very fun.", "Very funny", "HAHAHHAHAHAHAHAHA", "NO!"};

/**
@brief send one command to the screen,

@param start mark the mode in which to transmit

@param dat is the command to be sent

@return void
*/

void screentrans(uint8_t start, uint8_t dat){

	data[0] = start;
	data[1] = dat & 0xF;
	data[2] = dat >> 4;

	HAL_GPIO_WritePin(Disp_CS_GPIO_Port, Disp_CS_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);

	HAL_SPI_Transmit(&hspi2, data, 3, 10);

	HAL_GPIO_WritePin(Disp_CS_GPIO_Port, Disp_CS_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
}

/**
@brief clears the screen

@param none

@return void
*/

void screenclear(void){
	screentrans(SYNC, 0x01); // clear command
}

/**
@brief screeninit, initializes screen settings

@param none

@return void
*/

void screeninit(void){

	HAL_GPIO_WritePin(Disp_Reset_GPIO_Port, Disp_Reset_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(Disp_Reset_GPIO_Port, Disp_Reset_Pin, GPIO_PIN_SET);
	HAL_Delay(1);

	int i;
	uint8_t in[] = {0x3A, 0x09, 0x06, 0x1E, 0x39, 0x1B, 0x6E, 0x56, 0x7F, 0x3A, 0x1F, 0x31, 0x38, 0x0F/*0x0C, 0x01*/}; // goes over init example from data-sheet

	for(i = 0; i < sizeof(in); i++){
		screentrans(SYNC, in[i]);
	}
}

/**
@brief screenbuffer, reads strings stx and writes to screen through SPI2

@param none

@return void
*/

void screenupdate(void){
	int i,j;
	screenclear();
	for(i = 0; i < 4; i++){
		screentrans(SYNC, 0x80 + i*0x20);
		for(j = 0; j < 21 && str[i][j] != 0; j++){
			screentrans(RS, (uint8_t) str[i][j]);
		}
	}
}

/**
@brief screenbuffer, reads strings stx and writes to screen through SPI2

@param none

@return void
*/

void screenshift(void){
	while(1){
		screentrans(SYNC, 0x18);
		HAL_Delay(500);
	}
}

/**
@brief fontmod,  updates strx based on sensordata for each row

@param RTC_TimeTypeDef tim, the time to be displayed

@return void
*/

void buffer(char* inp){
	// updates time in first row
}

/**
@brief pwmod,  sets PWM cycle to simulate screen brightness

@param uint8_t mod, the value to set the cycle to, should be between 0 and 255

@return void
*/

void pwmod(uint8_t mod){
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, mod);
}