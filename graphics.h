/**     @file graphics.c
 *      @authors Ngoc Le (Mickey), Luke Hyndman
 *      @date 17th October 2023
 *      @brief graphics module header file
**/


#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "logic.h"
#include <stdint.h>

#define TITLE_TEXT "Paper, Scissors, Rock"
#define WIN_TEXT "Round Won!"
#define LOSE_TEXT "Round Lost!"
#define DRAW_TEXT "Round Draw!"
#define WAIT_TEXT "Waiting for Response"
#define WIN_GAME_TEXT "You Win :)"
#define LOSE_GAME_TEXT "You Lose :("

/*
    Draws a given option char to the LEDMAT
*/
void draw_option(game_option_t option);

/*
    Draws the score on the LEDMAT
*/
void draw_score(uint8_t scores);

/*
    Scrolls given text across the screen until the navswitch is hit
*/
void scroll_text(char string[]);

#endif // GRAPHIC_H