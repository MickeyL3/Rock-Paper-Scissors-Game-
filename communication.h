/**     @file communication.c
 *      @authors Ngoc Le (Mickey), Luke Hyndman
 *      @date 17th October 2023
 *      @brief communication module header file
**/

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdbool.h>
#include "logic.h"
/*
    Transmits chosen option to opponents machine
*/
void send_option(game_option_t option);

/*
    Recieves opponents chosen option and writes it into a var using a pointer if it is valid
    Return true when valid option recieved, returns null while no option received
*/
bool receive_option(game_option_t* enemy_option_ptr);

#endif // COMMUNICATION_H

