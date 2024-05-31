/**     @file communication.c
 *      @authors Ngoc Le (Mickey), Luke Hyndman
 *      @date 17th October 2023
 *      @brief communication module source file containing helper functions that communicate between 2 UCFKs
**/

#include "communication.h"
#include "ir_uart.h"



/*
    Transmits chosen option to opponents machine
*/
void send_option(game_option_t option) 
{
    ir_uart_putc(option_to_char(option));
}

/*
    Recieves opponents chosen option and writes it into a var using a pointer if it is valid
    Return true when valid option recieved, returns null while no option received
*/
bool receive_option(game_option_t* enemy_option_ptr)
{
    if (ir_uart_read_ready_p())
    {
        char c = ir_uart_getc();
        game_option_t option = char_to_option(c);
        if ((option == PAPER) || (option == SCISSORS) || (option == ROCK)) {
            *enemy_option_ptr = option;
            return 1;
        }
    }
    return 0;
}
