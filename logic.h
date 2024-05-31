/**     @file logic.c
 *      @authors Ngoc Le (Mickey), Luke Hyndman
 *      @date 17th October 2023
 *      @brief logic module header file
**/


#ifndef LOGIC_H
#define LOGIC_H

#define NUM_WINNING_COMBINATIONS 3

/*
    Enum of options players can choose
*/
typedef enum {
    OTHER = -1,
    PAPER,
    SCISSORS,
    ROCK,
} game_option_t;

/*
    Enum of possible outcomes of each game
*/
typedef enum {
    WIN,
    LOSE,
    DRAW
} outcome_t;



/*
    Helper Function takes game_option_t and returns associated char
*/
char option_to_char(game_option_t option);

/*
    Helper Function takes char c and returns associated game_option_t
*/
game_option_t char_to_option(char c);

/*
    Given player and enemy options, return an outcome_t enum for weather
    the player won, lost, or drew the game
*/
outcome_t get_outcome(game_option_t player_option, game_option_t enemy_option);

#endif // LOGIC_H