/**     @file logic.c
 *      @authors Ngoc Le (Mickey), Luke Hyndman
 *      @date 17th October 2023
 *      @brief logic module source file containing game_option and outcome enums, 
 *             char and option conversions, and outcome logic functions.
**/

#include "logic.h"

// 2D array to store winning combinations of player and enemy choices
static game_option_t winning_combinations[NUM_WINNING_COMBINATIONS][2] = {
    {PAPER, ROCK},  // Paper beats Rock
    {SCISSORS, PAPER},  // Scissors beats Paper
    {ROCK, SCISSORS}   // Rock beats Scissors
};

/*
    Helper Function takes game_option_t and returns associated char
*/
char option_to_char(game_option_t option)
{
    if (option == PAPER) {
        return 'P';
    } else if (option == SCISSORS) {
        return 'S';
    } else {
        return 'R';
    }
}

/*
    Helper Function takes char c and returns associated game_option_t
*/
game_option_t char_to_option(char c)
{
    if (c == 'P') {
        return PAPER;
    } else if (c == 'S') {
        return SCISSORS;
    } else if (c == 'R'){
        return ROCK;
    } else {
        return OTHER;
    }
    
}

/*
    Given player and enemy options, return an outcome_t enum for weather
    the player won, lost, or drew the game
*/
outcome_t get_outcome(game_option_t player_option, game_option_t enemy_option)
{
    for (int i = 0; i < NUM_WINNING_COMBINATIONS; i++) {
        if ((player_option == winning_combinations[i][0]) && (enemy_option == winning_combinations[i][1])) {
            return WIN;
        }
    }

    if (player_option == enemy_option) {
        return DRAW;
    } else {
        return LOSE;
    }
}