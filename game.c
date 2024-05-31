/**     @file game.c
 *      @authors Ngoc Le (Mickey), Luke Hyndman
 *      @date 17th October 2023
 *      @brief UCFK paper scissors rock game
**/

// Provided API
#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "../fonts/font5x5_1.h"
#include "ledmat.h"
#include <string.h> 

// user modules
#include "logic.h"
#include "graphics.h"
#include "communication.h"

#define PACER_RATE 500
#define MESSAGE_RATE 25

int main (void)
{
    game_option_t my_option = PAPER;
    game_option_t enemy_option;

    outcome_t outcome;

    uint8_t my_score = 0;
    uint8_t enemy_score = 0;

    uint8_t round_finished = 0;         // Flag for if the current round has finished
    uint8_t enemy_option_received = 0;  // flag for if enemy option has been received

    system_init ();
    ir_uart_init();
    navswitch_init();
    pacer_init (PACER_RATE);
    tinygl_init (PACER_RATE);

    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    tinygl_font_set (&font5x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    // Show title screen
    scroll_text(TITLE_TEXT);
    
    while(1)
    {
        pacer_wait();
        navswitch_update();
        
        // Option scroll up
        if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
            if (my_option == ROCK) {
                my_option = PAPER;
            } else {
                my_option++;
            }

        // Option scroll down
        } else if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            if (my_option == PAPER) {
                my_option = ROCK;
            } else {
                my_option--;

            }
        
        // Round start
        } else if (navswitch_push_event_p(NAVSWITCH_PUSH)) { // user has chosen their option and it is being sent to the opponent
            send_option(my_option); // Only need to send my option once
            tinygl_text(WAIT_TEXT); // set wait text
            // Loop while round is in progress
            while (!round_finished)
            {
                pacer_wait();
                tinygl_update();

                // check if enemy option has been received
                if (enemy_option_received) {
                    tinygl_clear();
                    outcome = get_outcome(my_option, enemy_option);
                    if (outcome == WIN) {
                        scroll_text(WIN_TEXT);
                        my_score++;
                    } else if (outcome == LOSE) {
                        scroll_text(LOSE_TEXT);
                        enemy_score++;
                    } else {
                        scroll_text(DRAW_TEXT);
                    }
                    round_finished = 1;     // set round finished flag
                    enemy_option_received = 0;      // clear enemy option recevied flag
                
                // if not, try to receive
                } else {
                    enemy_option_received = receive_option(&enemy_option);
                }
            }
            round_finished = 0;     // clear round finished flag
        } 
        
        // Check for Game win (score = 5)
        if (my_score == 5) {
            scroll_text(WIN_GAME_TEXT);
            my_score = 0;
            enemy_score = 0;
            tinygl_clear();
        } else if (enemy_score == 5) {
            scroll_text(LOSE_GAME_TEXT);
            my_score = 0;
            enemy_score = 0;
            tinygl_clear();
        }

        // try to receive enemy option if it hasn't been received yet
        if (!enemy_option_received) {
            enemy_option_received = receive_option(&enemy_option);
        }
        
        draw_option(my_option);
        draw_score(my_score);    
        tinygl_update();
        
    }
}
